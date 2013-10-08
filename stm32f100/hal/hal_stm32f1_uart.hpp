#pragma once

#include <uart.hpp>
#include <stm32f10x_usart.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <misc.h>
#include <hal/stm32fx/usart_conf.hpp>


namespace stm32f1 {

namespace  uart {

	using namespace stm32fx::uart;

	template <class Policy = ::uart::PolicyNotifyOnChar<'\n'>>
	class Stm32f1_Uart : public ::uart::UartWithPolicy<Policy>
	{
	public:

		// steps to init an uart :
		//	- enable the uart clock
		//	- enable clock for used IO pins
		//	- init the GPIO struct
		//	- init the uart
		//	- configure the alternate function pin
		//	- configure the uart interrupt line
		//	- nvic init
		// enable the complete uart peripheral
		Stm32f1_Uart(unsigned int id, void (*callback)(const std::string&, ::uart::Uart&), ::uart::Configuration config = ::uart::Configuration::_9600_8_N_1()) :
							::uart::UartWithPolicy<Policy>(callback)
		{
			// here perform the initialisation
			USART_InitTypeDef		USART_InitStruct; // this is for the USART2 initilization
			NVIC_InitTypeDef		NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

			// function used to enable the uart clock
			void 		(*pfvRCC_APBxPeriphClockCmd)(uint32_t, FunctionalState);
			uint32_t	  RCC_APBxPeriph_USARTx;

			// peripheral clock for the pins used by the uart
			//void 		(*pfvRCC_AHBxPeriphClockCmd)(uint32_t, FunctionalState);
			//uint32_t	  RCC_AHBxPeriph_GPIOx;

			// the gpio used
			GPIO_TypeDef* 	GPIOx;
			uint32_t		GPIO_Pin_Rx, GPIO_Pin_Tx;			// the selected pin


			  /* enable APB1 peripheral clock for USART2
			   * note that only USART1 and USART6 are connected to APB2
			   * the other USARTs are connected to APB1
			   */
			   switch (id)
			   {
					case 1: 	pfvRCC_APBxPeriphClockCmd 	= RCC_APB2PeriphClockCmd;
								RCC_APBxPeriph_USARTx 		= RCC_APB2Periph_USART1;
								_USARTx						= USART1;			
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_9;
								GPIO_Pin_Rx					= GPIO_Pin_10;

								NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;

								break;

					case 2:		pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
								RCC_APBxPeriph_USARTx		= RCC_APB1Periph_USART2;
								_USARTx						= USART2;
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_2;
								GPIO_Pin_Rx					= GPIO_Pin_3;

								NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;

								break;

					case 3: 	pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
								RCC_APBxPeriph_USARTx		= RCC_APB1Periph_USART3;
								_USARTx						= USART3;
								GPIOx						= GPIOB;
								GPIO_Pin_Tx					= GPIO_Pin_10;
								GPIO_Pin_Rx					= GPIO_Pin_11;

								NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;

								break;

					default:	pfvRCC_APBxPeriphClockCmd	= nullptr;
								RCC_APBxPeriph_USARTx		= -1;
								_USARTx						= nullptr;
								GPIOx						= nullptr;
								GPIO_Pin_Tx					= -1;
								GPIO_Pin_Rx					= -1;
			}
			pfvRCC_APBxPeriphClockCmd(RCC_APBxPeriph_USARTx, ENABLE);

			GPIO_InitTypeDef GPIO_InitStructure;
			
			/* TX Pin */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOx, &GPIO_InitStructure);

			/* RX Pin */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOx, &GPIO_InitStructure);



			/* Now the USART_InitStruct is used to define the
			* properties of USART1
			*/
			USART_InitStruct.USART_BaudRate = conf_2_baudrate(config.baudRate);       // the baudrate is set to the value we passed into this init function
			USART_InitStruct.USART_WordLength = conf_2_WordLength(config.WordLength);// we want the data frame size to be 8 bits (standard)
			USART_InitStruct.USART_StopBits = conf_2_StopBits(config.StopBits);   // we want 1 stop bit (standard)
			USART_InitStruct.USART_Parity = conf_2_Parity(config.Parity);    // we don't want a parity bit (standard)
			USART_InitStruct.USART_HardwareFlowControl = conf_2_HardwareFlowControl(config.HardwareFlowControl); // we don't want flow control (standard)
			USART_InitStruct.USART_Mode = conf_2_Mode(config.Mode); // we want to enable the transmitter and the receiver
			USART_Init(_USARTx, &USART_InitStruct);          // again all the properties are passed to the USART_Init function which takes care of all the bit setting

			  				
    		USART_ITConfig(_USARTx, USART_IT_RXNE, ENABLE);

			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART2 interrupts
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     // this sets the subpriority inside the group
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      // the USART2 interrupts are globally enabled
			NVIC_Init(&NVIC_InitStructure);              // the properties are passed to the NVIC_Init function which takes care of the low level stuff

			// finally this enables the complete USART1 peripheral
			USART_Cmd(_USARTx, ENABLE);
		}

		virtual void send(const types::buffer& buf)
		{
			for (auto c : buf)
			{
		            while ((_USARTx->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
		            _USARTx->DR = (c & (uint16_t) 0x01FF);
        	}

		}

		virtual void send(const unsigned char* buf, unsigned int length)
		{
			for (unsigned int i = 0; i < length; i++)
			{
		            while ((_USARTx->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
		            _USARTx->DR = (buf[i] & (uint16_t) 0x01FF);
        	}
		}

	private:

		Stm32f1_Uart() {}

		USART_TypeDef* _USARTx;
	};

	#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQ_Handler()										\
										{																\
										    ::uart::get_instance(UsartX).accumulator(USART##UsartX ->DR);		\
										}

	USART_IRQ_CALLBACK(1)
	USART_IRQ_CALLBACK(2)
	USART_IRQ_CALLBACK(3)

	static ::uart::Uart* gpUart_1 = nullptr;
	static ::uart::Uart* gpUart_2 = nullptr;
	static ::uart::Uart* gpUart_3 = nullptr;

	static ::uart::Uart* gpUart_NULL = nullptr;

	} /* namespace uart  */

} /* namespace stm32f4  */


namespace uart
{
	unsigned int	num_instance()
	{
		return 3;
	}

	template <class Policy>
	void init_instance(unsigned int id, void (*callback)(const std::string&, uart::Uart&), Configuration config = Configuration::_9600_8_N_1())
	{
		switch (id)
		{
			case 1: ::stm32f1::uart::gpUart_1 = new stm32f1::uart::Stm32f1_Uart<Policy>(1, callback, config); break;
			case 2: ::stm32f1::uart::gpUart_2 = new stm32f1::uart::Stm32f1_Uart<Policy>(2, callback, config); break;
			case 3: ::stm32f1::uart::gpUart_3 = new stm32f1::uart::Stm32f1_Uart<Policy>(3, callback, config); break;
		}	
	}

	Uart& get_instance(unsigned int id)
	{
		switch (id)
		{
			case 1: return *::stm32f1::uart::gpUart_1;
			case 2: return *::stm32f1::uart::gpUart_2;
			case 3: return *::stm32f1::uart::gpUart_3;
		}
		return *::stm32f1::uart::gpUart_NULL;
	}
}

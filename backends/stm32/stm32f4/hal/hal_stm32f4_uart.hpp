#pragma once

#include <uart.hpp>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <misc.h>
#include <hal/gpio.hpp>
#include <hal/stm32fx/usart_conf.hpp>
#include <string.h>


namespace stm32f4 {

namespace  uart {

	using namespace stm32fx::uart;

	template <class Policy = ::uart::PolicyNotifyOnChar<'\n'>>
	class Stm32f4_Uart : public ::uart::UartWithPolicy<Policy>
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
		Stm32f4_Uart(unsigned int id, ::uart::Uart::uart_callback callback, ::uart::Configuration config = ::uart::Configuration::_9600_8_N_1()) :
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
			uint32_t		GPIO_Pin;			// the selected pin
			uint8_t			GPIO_AF;
			uint16_t		GPIO_Pin_Source1; 	// used for alternate function 
			uint16_t		GPIO_Pin_Source2; 	// used for alternate function 



			  /* enable APB1 peripheral clock for USART2
			   * note that only USART1 and USART6 are connected to APB2
			   * the other USARTs are connected to APB1
			   */
			   switch (id)
			   {
					case 1: 	pfvRCC_APBxPeriphClockCmd 	= RCC_APB2PeriphClockCmd;
								RCC_APBxPeriph_USARTx 		= RCC_APB2Periph_USART1;
								_USARTx						= USART1;
								GPIO_AF						= GPIO_AF_USART1;
								GPIOx						= GPIOB;
								GPIO_Pin					= GPIO_Pin_6 | GPIO_Pin_7;
								GPIO_Pin_Source1			= GPIO_PinSource6;
								GPIO_Pin_Source2			= GPIO_PinSource7;

								NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;

								break;

					case 2:		pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
								RCC_APBxPeriph_USARTx		= RCC_APB1Periph_USART2;
								_USARTx						= USART2;
								GPIO_AF						= GPIO_AF_USART2;
								GPIOx						= GPIOA;
								GPIO_Pin					= GPIO_Pin_2 | GPIO_Pin_3;
								GPIO_Pin_Source1			= GPIO_PinSource2;
								GPIO_Pin_Source2			= GPIO_PinSource3;

								NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;

								break;

					case 3: 	pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
								RCC_APBxPeriph_USARTx		= RCC_APB1Periph_USART3;
								_USARTx						= USART3;
								GPIO_AF						= GPIO_AF_USART3;
								GPIOx						= GPIOB;
								GPIO_Pin					= GPIO_Pin_10 | GPIO_Pin_11;
								GPIO_Pin_Source1			= GPIO_PinSource10;
								GPIO_Pin_Source2			= GPIO_PinSource11;

								NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;

								break;

					case 4: 	pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
								RCC_APBxPeriph_USARTx		= RCC_APB1Periph_UART4;
								_USARTx						= UART4;
								GPIO_AF						= GPIO_AF_UART4;
								GPIOx						= GPIOA;
								GPIO_Pin					= GPIO_Pin_0 | GPIO_Pin_1;
								GPIO_Pin_Source1			= GPIO_PinSource0;
								GPIO_Pin_Source2			= GPIO_PinSource1;

								NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;

								break;

					case 5: 	pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
								RCC_APBxPeriph_USARTx		= RCC_APB1Periph_UART4;
								_USARTx						= UART5;
								GPIO_AF						= GPIO_AF_UART5;
								GPIOx						= GPIOA;
								GPIO_Pin					= GPIO_Pin_8 | GPIO_Pin_9;
								GPIO_Pin_Source1			= GPIO_PinSource8;
								GPIO_Pin_Source2			= GPIO_PinSource9;

								NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;

								break;

					case 6: 	pfvRCC_APBxPeriphClockCmd	= RCC_APB2PeriphClockCmd;
								RCC_APBxPeriph_USARTx		= RCC_APB2Periph_USART6;
								_USARTx						= USART6;
								GPIO_AF						= GPIO_AF_USART6;
								GPIOx						= GPIOB;
								GPIO_Pin					= GPIO_Pin_0 | GPIO_Pin_1;
								GPIO_Pin_Source1			= GPIO_PinSource0;
								GPIO_Pin_Source2			= GPIO_PinSource1;

								NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;

								break;



					default:	pfvRCC_APBxPeriphClockCmd	= nullptr;
								RCC_APBxPeriph_USARTx		= -1;
								_USARTx						= nullptr;
								GPIO_AF						= -1;
								GPIOx						= nullptr;
								GPIO_Pin					= -1;
								GPIO_Pin_Source1			= -1;
								GPIO_Pin_Source2			= -1;
			}
			pfvRCC_APBxPeriphClockCmd(RCC_APBxPeriph_USARTx, ENABLE);

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

			::stm32f4::gpio::configure_pin(GPIOx, GPIO_Pin, GPIO_PuPd_UP);
  			GPIO_PinAFConfig(GPIOx, GPIO_Pin_Source1, GPIO_AF); //
  			GPIO_PinAFConfig(GPIOx, GPIO_Pin_Source2, GPIO_AF);
			  				
    		USART_ITConfig(_USARTx, USART_IT_RXNE, ENABLE);

			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART2 interrupts
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     // this sets the subpriority inside the group
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      // the USART2 interrupts are globally enabled
			NVIC_Init(&NVIC_InitStructure);              // the properties are passed to the NVIC_Init function which takes care of the low level stuff

			// finally this enables the complete USART1 peripheral
			USART_Cmd(_USARTx, ENABLE);
		}

		virtual void send(const char* const str)
		{
			send((const unsigned char*)str, strlen(str));
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

		Stm32f4_Uart() {}

		USART_TypeDef* _USARTx;
	};

	#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQn()										\
										{																\
										    ::uart::get_instance(UsartX).accumulator(USART##UsartX ->DR);		\
										}

	#define UART_IRQ_CALLBACK(UartX)	void UART##UartX##_IRQn()										\
										{																\
										    ::uart::get_instance(UartX).accumulator(UART##UartX ->DR);		\
										}


	USART_IRQ_CALLBACK(1)
	USART_IRQ_CALLBACK(2)
	USART_IRQ_CALLBACK(3)
	UART_IRQ_CALLBACK(4)
	UART_IRQ_CALLBACK(5)
	USART_IRQ_CALLBACK(6)


	static ::uart::Uart* gpUart_1 = nullptr;
	static ::uart::Uart* gpUart_2 = nullptr;
	static ::uart::Uart* gpUart_3 = nullptr;
	static ::uart::Uart* gpUart_4 = nullptr;
	static ::uart::Uart* gpUart_5 = nullptr;
	static ::uart::Uart* gpUart_6 = nullptr;


	static ::uart::Uart* gpUart_NULL = nullptr;

	} /* namespace uart  */

} /* namespace stm32f4  */


namespace uart
{
	unsigned int	num_instance()
	{
		return 6;
	}

	template <class Policy>
	void init_instance(unsigned int id,  ::uart::Uart::uart_callback callback, Configuration config = Configuration::_9600_8_N_1())
	{
		switch (id)
		{
			case 1: ::stm32f4::uart::gpUart_1 = new stm32f4::uart::Stm32f4_Uart<Policy>(1, callback, config); break;
			case 2: ::stm32f4::uart::gpUart_2 = new stm32f4::uart::Stm32f4_Uart<Policy>(2, callback, config); break;
			case 3: ::stm32f4::uart::gpUart_3 = new stm32f4::uart::Stm32f4_Uart<Policy>(3, callback, config); break;
			case 4: ::stm32f4::uart::gpUart_4 = new stm32f4::uart::Stm32f4_Uart<Policy>(4, callback, config); break;
			case 5: ::stm32f4::uart::gpUart_5 = new stm32f4::uart::Stm32f4_Uart<Policy>(5, callback, config); break;
			case 6: ::stm32f4::uart::gpUart_6 = new stm32f4::uart::Stm32f4_Uart<Policy>(6, callback, config); break;
		}	
	}

	Uart& get_instance(unsigned int id)
	{
		switch (id)
		{
			case 1: return *::stm32f4::uart::gpUart_1;
			case 2: return *::stm32f4::uart::gpUart_2;
			case 3: return *::stm32f4::uart::gpUart_3;
			case 4: return *::stm32f4::uart::gpUart_4;
			case 5: return *::stm32f4::uart::gpUart_5;
			case 6: return *::stm32f4::uart::gpUart_6;
		}
		return *::stm32f4::uart::gpUart_NULL;
	}
}

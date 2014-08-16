#include "hal_stm32.hpp"

#include <usart_conf.hpp>
#include <UartInterface.hpp>
#include <hal_stm32_uart.hpp>

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


namespace stm32 {

	namespace  uart {

		static ::uart::UartInterface*		gpUarts[STM32_UART_MAX_COUNT];

		Uart::Uart(unsigned int id, ::uart::UartInterface::uart_callback_T callback, ::uart::Configuration config)
		{

			//assert params
			assert(id > 0);
			assert(id <= sizeof(gpUarts)/sizeof(::uart::UartInterface*));

			// here perform the initialisation
			USART_InitTypeDef		USART_InitStruct; // this is for the USART2 initilization
			NVIC_InitTypeDef		NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

			//save callback
			_callback = callback;

			// the gpio used
			GPIO_TypeDef* 	GPIOx;
			uint32_t		GPIO_Pin_Rx, GPIO_Pin_Tx;			// the selected pin
			uint16_t		GPIO_PinSource_Tx;
			uint16_t		GPIO_PinSource_Rx;
			uint8_t			GPIO_AF_Tx;
			uint8_t			GPIO_AF_Rx;
			uint8_t			GPIO_AF;

			gpUarts[id - 1] = this;

			  /* enable APB1 peripheral clock for USART2
			   * note that only USART1 and USART6 are connected to APB2
			   * the other USARTs are connected to APB1
			   */
			   switch (id)
			   {
					case 1: 	
								_USARTx						= USART1;							
#ifdef STM32F0XX
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_9;
								GPIO_Pin_Rx					= GPIO_Pin_10;	
								GPIO_PinSource_Tx			= GPIO_PinSource9;
								GPIO_PinSource_Rx			= GPIO_PinSource10;
								GPIO_AF_Tx					= GPIO_AF_1;
								GPIO_AF_Rx					= GPIO_AF_1;
								
								//GPIO
								RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
								//USART
								RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
#elif STM32F1XX
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_9;
								GPIO_Pin_Rx					= GPIO_Pin_10;
								
								//GPIO
								RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
								//USART
								RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
#elif STM32F4XX
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_9;
								GPIO_Pin_Rx					= GPIO_Pin_10;
								GPIO_PinSource_Tx			= GPIO_PinSource9;
								GPIO_PinSource_Rx			= GPIO_PinSource10;
								GPIO_AF						= GPIO_AF_USART1;
								
								//GPIO
								RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
								//USART
								RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
#endif //STM32F0XX
								
								NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;					

								break;
							
					case 2: 	
								_USARTx						= USART2;							
#ifdef STM32F0XX
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_2;
								GPIO_Pin_Rx					= GPIO_Pin_3;	
								GPIO_PinSource_Tx			= GPIO_PinSource2;
								GPIO_PinSource_Rx			= GPIO_PinSource3;
								GPIO_AF_Tx					= GPIO_AF_1;
								GPIO_AF_Rx					= GPIO_AF_1;

								//GPIO
								RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
								//USART
								RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
#elif STM32F1XX
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_2;
								GPIO_Pin_Rx					= GPIO_Pin_3;
								
								//GPIO
								RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
								//USART
								RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
#elif STM32F4XX
								GPIOx						= GPIOA;
								GPIO_Pin_Tx					= GPIO_Pin_2;
								GPIO_Pin_Rx					= GPIO_Pin_3;
								GPIO_PinSource_Tx			= GPIO_PinSource2;
								GPIO_PinSource_Rx			= GPIO_PinSource3;
								GPIO_AF						= GPIO_AF_USART2;

								//GPIO
								RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
								//USART
								RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
#endif //STM32F0XX
								NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
								
								break;

					default:	fprintf(stderr, "Unimplemented uart %i !\n", id);
								abort();
								break;
			} //switch uart id

			GPIO_InitTypeDef GPIO_InitStructure;
			
			/* TX Pin */
			GPIO_StructInit(&GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
#ifdef STM32F0XX
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
#elif STM32F1XX
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#elif STM32F4XX
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
#endif //STM32F0XX

			GPIO_Init(GPIOx, &GPIO_InitStructure);

			/* RX Pin */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
#ifdef STM32F0XX
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
#elif STM32F1XX
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#elif STM32F4XX
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
#endif //STM32F0XX
			GPIO_Init(GPIOx, &GPIO_InitStructure);

#ifdef STM32F0XX
			/* ALternate configuration for TX Pin */
			GPIO_PinAFConfig(GPIOx, GPIO_PinSource_Tx, GPIO_AF_Tx);
			/* ALternate configuration for RX Pin */
			GPIO_PinAFConfig(GPIOx, GPIO_PinSource_Rx, GPIO_AF_Rx);
#elif STM32F4XX
			GPIO_PinAFConfig(GPIOx, GPIO_PinSource_Tx, GPIO_AF);
  			GPIO_PinAFConfig(GPIOx, GPIO_PinSource_Rx, GPIO_AF);
#endif //STM32F0XX
			
			USART_InitStruct.USART_BaudRate = ::stm32fx::uart::conf_2_baudrate(config.baudRate);       // the baudrate is set to the value we passed into this init function
			USART_InitStruct.USART_WordLength = ::stm32fx::uart::conf_2_WordLength(config.WordLength);// we want the data frame size to be 8 bits (standard)
			USART_InitStruct.USART_StopBits = ::stm32fx::uart::conf_2_StopBits(config.StopBits);   // we want 1 stop bit (standard)
			USART_InitStruct.USART_Parity = ::stm32fx::uart::conf_2_Parity(config.Parity);    // we don't want a parity bit (standard)
			USART_InitStruct.USART_HardwareFlowControl = ::stm32fx::uart::conf_2_HardwareFlowControl(config.HardwareFlowControl); // we don't want flow control (standard)
			USART_InitStruct.USART_Mode = ::stm32fx::uart::conf_2_Mode(config.Mode); // we want to enable the transmitter and the receiver
			USART_Init(_USARTx, &USART_InitStruct);          // again all the properties are passed to the USART_Init function which takes care of all the bit setting
			
			USART_ITConfig(_USARTx, USART_IT_RXNE, ENABLE);

#ifdef STM32F0XX
			NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
#elif STM32F1XX
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
#endif //STM32F0XX
			
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			USART_Cmd(_USARTx, ENABLE);
			
		}

		void Uart::Configure()
		{
			return;
		}

		void Uart::send(const char* const str)
		{
			send((const unsigned char*)str, strlen(str));
		}

		void Uart::send(const types::buffer& buf)
		{
			for (auto c : buf)
			{
#ifdef STM32F0XX
					while ((_USARTx->ISR & USART_FLAG_TC) == (uint16_t) RESET) {}
					_USARTx->TDR = (c & (uint16_t) 0x01FF);
#elif (STM32F1XX || STM32F4XX)
					while ((_USARTx->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
					_USARTx->DR = (c & (uint16_t) 0x01FF);
#endif //STM32F0XX
			}

		}

		void Uart::send(const unsigned char* buf, unsigned int length)
		{
			for (unsigned int i = 0; i < length; i++)
			{
#ifdef STM32F0XX
					while ((_USARTx->ISR & USART_FLAG_TC) == (uint16_t) RESET) {}
					_USARTx->TDR = (buf[i] & (uint16_t) 0x01FF);
#elif (STM32F1XX || STM32F4XX)
					while ((_USARTx->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
					_USARTx->DR = (buf[i] & (uint16_t) 0x01FF);
#endif //STM32F0XX
			}
		}

#ifdef STM32F0XX
		#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQHandler()									\
											{																	\
												gpUarts[UsartX - 1]->_callback(USART##UsartX ->RDR);					\
											}
#elif (STM32F1XX || STM32F4XX)
		#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQHandler()									\
											{																	\
												gpUarts[UsartX - 1]->_callback(USART##UsartX ->DR);					\
											}
#endif //STM32F0XX
		extern "C"
		{

			USART_IRQ_CALLBACK(1)
			USART_IRQ_CALLBACK(2)

		}

	} /* namespace uart  */

} /* namespace stm32f0xx  */


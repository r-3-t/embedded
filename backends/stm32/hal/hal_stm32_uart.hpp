#pragma once

#ifdef STM32F0XX
#include <stm32f0xx_usart.h>
#elif STM32F1XX
#include <stm32f10x_usart.h>
#elif STM32F4XX
#include <stm32f4xx_usart.h>
#endif //STM32F0XX

#include <UartInterface.hpp>

namespace stm32 {

	namespace  uart {

		class Uart : public ::uart::UartInterface
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

			/**
			 * \param id an integer argument for USARTid (id from 1 to STM32F1XX_UART_MAX_COUNT).
			 * \param callback function callback to call when a character has received.
			 * \param config configuration of the UART (default : 9600 8 N 1)
			 */
			Uart(unsigned int id, ::uart::UartInterface::uart_callback_T callback, ::uart::Configuration config = ::uart::Configuration::_9600_8_N_1());

			/**
			 * \param send a C string
			 */
			virtual void send(const char* const str);

			/**
			 * \param send a buffer
			 */
			virtual void send(const types::buffer& buf);

			/**
			 * \param send a buffer
			 */
			virtual void send(const unsigned char* buf, unsigned int length);

			virtual void Configure();

		private:

			USART_TypeDef* _USARTx;
		};


	} /* namespace uart  */

} /* namespace stm32f0xx  */


namespace uart
{
	typedef ::stm32::uart::Uart ConcreteUart;
} //namespace uart

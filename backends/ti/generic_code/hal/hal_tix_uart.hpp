#pragma once

#include <hal/usart_conf.hpp>
#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>
#include <UartInterface.hpp>

namespace tix
{

	namespace uart
	{

		class Uart: public ::uart::UartInterface
		{
		public:

			Uart(unsigned int id, ::uart::UartInterface::uart_callback callback,
					::uart::Configuration config = ::uart::Configuration::_9600_8_N_1());

			virtual void send(const char* const str);
			virtual void send(const types::buffer& buf);
			virtual void send(const unsigned char* buf, unsigned int length);

		private:

			unsigned long _UART_Base;
		};

	} /* namespace uart  */

} /* namespace tix  */

namespace uart
{
	typedef ::tix::uart::Uart					ConcreteUart;
}

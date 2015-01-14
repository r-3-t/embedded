#pragma once

#include <usart_conf.hpp>
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

			Uart(unsigned int id, ::uart::UartInterface::uart_callback_T callback,
					::uart::Configuration config = ::uart::Configuration::_9600_8_N_1());

			virtual void send(const char* const str);
			virtual void send(types::buffer& buf);
			virtual void send(const unsigned char* buf, unsigned int length);
			virtual void set_callback(::uart::UartInterface::uart_callback_T callback);

			unsigned char		 	receive();
			unsigned long 			UART_Base;
			void		 			Configure();

		private:

			unsigned int			_id;
			::uart::Configuration	_config;
			bool					_configured;
		};

	} /* namespace uart  */

} /* namespace tix  */

namespace uart
{
	typedef ::tix::uart::Uart					ConcreteUart;
}

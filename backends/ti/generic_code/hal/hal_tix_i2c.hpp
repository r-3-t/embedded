#pragma once

#include <hal/usart_conf.hpp>
#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>
#include <I2cInterface.hpp>

namespace tix
{

	namespace i2c
	{
		
		class I2c: public ::i2c::I2cInterface
		{
		public:

			I2c(unsigned int id, ::i2c::I2cInterface::i2c_callback callback,
					::i2c::Configuration config = ::i2c::Configuration::_Master());

			virtual void send(const char car);
			virtual void send(const types::buffer& buf);
			virtual void setSlaveAddress(const unsigned char Address, ::i2c::MasterOperation_T MasterOperation = ::i2c::MasterWriteToSlave);

			unsigned char		 	receive();
			unsigned long 			I2C_Base;
			::i2c::Configuration	config;

		private:
			void		 			Configure();

			unsigned int			_id;
			bool					_configured;
		};

	} /* namespace i2c  */

} /* namespace tix  */

namespace i2c
{
	typedef ::tix::i2c::I2c					ConcreteI2c;
}

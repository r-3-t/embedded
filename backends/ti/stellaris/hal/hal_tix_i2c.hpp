#pragma once

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

			I2c(unsigned int id, ::i2c::I2cInterface::i2c_receive_callback receive_callback,
					::i2c::Configuration config = ::i2c::Configuration::_Master(),
					::i2c::I2cInterface::i2c_on_master_request_callback on_master_request_callback = (i2c_on_master_request_callback)0);

			virtual void send(const char car);
			virtual void send(types::buffer& buf);
			virtual void setSlaveAddress(const unsigned char Address);
			virtual void waitBusy();
			virtual void request();
			virtual void request(int BytesCount);

			unsigned char		 	receive();
			unsigned long 			I2C_Base;
			::i2c::Configuration	config;
			bool					requestEnabled;

		private:
			void		 			Configure();

			unsigned int			_id;
			bool					_configured;
			uint8_t					_slave_address;
		};

	} /* namespace i2c  */

} /* namespace tix  */

namespace i2c
{
	typedef ::tix::i2c::I2c					ConcreteI2c;
}

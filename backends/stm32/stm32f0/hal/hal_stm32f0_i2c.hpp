#pragma once

#include <I2cInterface.hpp>

namespace stm32f0xx
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
			virtual void send(const types::buffer& buf);
			virtual void setSlaveAddress(const uint8_t slave_address);
			virtual void request(int BytesCount);
			virtual void waitBusy();

			unsigned char		 	receive();
			::i2c::Configuration	config;
			I2C_TypeDef*			_I2C;

		private:
			void		 			Configure();
			void					enable();

			unsigned int			_id;
			bool					_configured;
			unsigned char			_slave_address;
		};

	} /* namespace i2c  */

} /* namespace stm32f0xx  */

namespace i2c
{
	typedef ::stm32f0xx::i2c::I2c					ConcreteI2c;
}

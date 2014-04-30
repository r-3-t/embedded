#include "arduino_wire.hpp"
#include <I2cInterface.hpp>

::i2c::ConcreteI2c I2cMaster(DEFAULT_I2C_NUMBER, &master_receive_callback);

namespace arduino
{
	namespace wire
	{

		void ArduinoWire::beginTransmission(unsigned char SlaveAddress)
		{
			  ::spi::beginTransmission(DEFAULT_I2C_NUMBER);
			return;
		}

		uint8_t ArduinoSPI::transfer(uint8_t val)
		{
			return ::spi::get_instance(DEFAULT_SPI_NUMBER).send(val);
		}

	} //namespace spi

} //namespace arduino

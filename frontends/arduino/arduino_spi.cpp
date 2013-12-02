#include "arduino_spi.hpp"
#include <SpiInterface.hpp>


namespace arduino
{
	namespace spi
	{

		void ArduinoSPI::begin()
		{
			  ::spi::init_instance(DEFAULT_SPI_NUMBER);
			return;
		}

		uint8_t ArduinoSPI::transfer(uint8_t val)
		{
			return ::spi::get_instance(DEFAULT_SPI_NUMBER).send(val);
		}

	} //namespace spi

} //namespace arduino

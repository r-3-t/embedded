#include "arduino_spi.hpp"
#include <SpiInterface.hpp>

::spi::ConcreteSpi			Spi1(1, 0,::spi::Configuration::_default_master());


namespace arduino
{
	namespace spi
	{

		ArduinoSPI SPI;

		void ArduinoSPI::begin()
		{
			return;
		}

		uint8_t ArduinoSPI::transfer(uint8_t val)
		{
			Spi1.send(val);
		}

	} //namespace spi

} //namespace arduino

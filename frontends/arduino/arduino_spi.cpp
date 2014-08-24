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

		void ArduinoSPI::end()
		{
			return;
		}

		uint8_t ArduinoSPI::transfer(uint8_t val)
		{
			return Spi1.send(val);
		}

		void ArduinoSPI::setBitOrder(uint8_t order)
		{
			//TODO: setBitOrder
			return;
		}

		void ArduinoSPI::setClockDivider(uint8_t diverder)
		{
			//TODO: setClockDivider
			return;
		}

		void ArduinoSPI::setDataMode(uint8_t mode)
		{
			//TODO: setDataMode
			return;
		}

	} //namespace spi

} //namespace arduino

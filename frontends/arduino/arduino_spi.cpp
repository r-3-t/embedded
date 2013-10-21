#include "arduino_spi.hpp"
#include <spi.hpp>


namespace arduino
{
	namespace spi
	{

		void ArduinoSPI::begin()
		{
			  ::spi::init_instance(DEFAULT_SPI_NUMBER,     { ::spi::Configuration::_2Lines_FullDuplex,
															  ::spi::Configuration::Master,
															  ::spi::Configuration::Low,
															  ::spi::Configuration::_1_Edge,
															  ::spi::Configuration::Soft,
															  ::spi::Configuration::_4,
															  ::spi::Configuration::MSB,
															  8
										});
			return;
		}

		uint8_t ArduinoSPI::transfer(uint8_t val)
		{
			return ::spi::get_instance(DEFAULT_SPI_NUMBER).send(val);
		}

	} //namespace spi

} //namespace arduino

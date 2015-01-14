#include "arduino_spi.hpp"
#include <SpiInterface.hpp>

#include <stdio.h>
#include <stdlib.h>

::spi::ConcreteSpi SPIs[] =
{
#if (ARDUINO_SPI_COUNT>0)
::spi::ConcreteSpi(1, 0,::spi::Configuration::_default_master()),
#endif
#if (ARDUINO_SPI_COUNT>1)
::spi::ConcreteSpi(2, 0,::spi::Configuration::_default_master()),
#endif
#if (ARDUINO_SPI_COUNT>2)
::spi::ConcreteSpi(3, 0,::spi::Configuration::_default_master()),
#endif
};

#ifndef SPI_ARDUINO_PRIORITY
#warning "SPI_ARDUINO_PRIORITY is not defined, use priority 0."
#define SPI_ARDUINO_PRIORITY 0
#endif //SPI_ARDUINO_PRIORITY

#ifndef ARDUINO_SPI_COUNT
#warning "ARDUINO_SPI_COUNT is not defined, reserve 1 SPI for arduino."
#define ARDUINO_SPI_COUNT 1
#endif //SPI_ARDUINO_PRIORITY

//default to SPI SLOT FREE
unsigned char SPIs_reserved[ARDUINO_SPI_COUNT];

namespace arduino
{
	namespace spi
	{

		ArduinoSPI SPI(SPI_ARDUINO_PRIORITY);

		ArduinoSPI::ArduinoSPI(unsigned int Priority)
		{
			unsigned int slot = Priority;

			while (slot < (sizeof(SPIs)/sizeof(::spi::ConcreteSpi)))
			{
				if (SPIs_reserved[slot] == SPI_SLOT_FREE)
				{
					//allocate this slot
					this->_internalSPIid = slot;

					SPIs_reserved[slot] = SPI_SLOT_RESERVED;

					break;
				}
				slot++;
			}


			//allow multi SPI usage
			if (slot >= (sizeof(SPIs)/sizeof(::spi::ConcreteSpi)))
			{
				fprintf(stderr, "Failed to initialize ArduinoSPI, not enough space !");
				abort();
			}

		}

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
			return SPIs[this->_internalSPIid].send(val);
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

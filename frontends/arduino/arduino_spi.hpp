#pragma once

#include <SpiInterface.hpp>

//TODO: must be placed in mapping file
#define DEFAULT_SPI_NUMBER							1

#define SPI_SLOT_RESERVED							1
#define SPI_SLOT_FREE								0

namespace arduino
{
	namespace spi
	{

	typedef enum
	{
		MSBFIRST,
		LSBFIRST
	} BIT_ORDER_T;

	typedef enum
	{
		SPI_MODE0,
		SPI_MODE1
	} MODE_T;

	class ArduinoSPI
	{
	public:

		ArduinoSPI(unsigned int Priority);

		void begin();
		void end();

		uint8_t transfer(uint8_t val);
		void setBitOrder(uint8_t order);
		void setClockDivider(uint8_t diverder);
		void setDataMode(uint8_t mode);

	private:
		unsigned int _internalSPIid;

	}; //class SPI

	typedef ArduinoSPI HardwareSPI;
	extern ArduinoSPI SPI;


	} //namespace spi

} //namespace arduino

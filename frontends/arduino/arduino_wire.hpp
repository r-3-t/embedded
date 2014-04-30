#pragma once

#include <I2cInterface.hpp>

//TODO: must be placed in mapping file
#define DEFAULT_I2C_NUMBER							1

namespace arduino
{
	namespace wire
	{

	class ArduinoWire
	{
	public:

		void beginTransmission(unsigned char SlaveAddress);

		void write(uint8_t val);

		void endTransmission();

	}; //class Wire

	typedef ArduinoWire HardwareWire;

	} //namespace wire

} //namespace arduino

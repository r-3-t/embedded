#pragma once

#include <I2cInterface.hpp>

//TODO: must be placed in mapping file
#define DEFAULT_I2C_NUMBER							1

namespace arduino
{
	namespace wire
	{

	void arduino_master_receive_callback(const uint8_t c);

	void arduino_slave_receive_callback(const uint8_t c);

	void arduino_on_master_request_callback();

	class ArduinoWire
	{
	public:

		ArduinoWire();

		void begin();
		void begin(unsigned char SlaveAddress);
		void beginTransmission(unsigned char SlaveAddress);

		int write(uint8_t data);
		int write(const uint8_t* pData, int Size);
		int write(unsigned char* pString);

		int endTransmission();
		int endTransmission(bool holdBus);

		int requestFrom(unsigned char slave_address, int size);
		int requestFrom(unsigned char slave_address, int size, bool holdBus);
		int available();
		uint8_t read();

		::types::buffer i2c_send_buffer;
		::types::fifo i2c_receive_buffer;

	private:
		unsigned char SlaveAddress;



	}; //class Wire

	typedef ArduinoWire HardwareWire;
	extern ArduinoWire Wire;

	} //namespace wire

} //namespace arduino

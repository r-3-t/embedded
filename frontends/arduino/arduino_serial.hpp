#pragma once

#include <types.hpp>

#include "Print.hpp"

//TODO: must be placed in mapping file
#define DEFAULT_I2C_NUMBER							1

namespace arduino
{
	namespace serial
	{

		void uart_callback (const uint8_t c);
		class ArduinoSerial: public ::arduino::print::Print
		{
		public:

			ArduinoSerial();

			void begin(int Speed);
			void write(const char c);
			int write(const char* pc);
			size_t write(const unsigned char* pc, unsigned int size);

			int available();
			int read();

			::types::fifo uart_receive_fifo;

		private:

		}; //class Serial

		typedef ArduinoSerial HardwareSerial;
		//typedef ArduinoSerial Print;
		extern ArduinoSerial Serial;

	} //namespace serial

} //namespace arduino

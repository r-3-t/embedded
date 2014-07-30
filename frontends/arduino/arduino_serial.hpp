#pragma once

#include <types.hpp>

//TODO: must be placed in mapping file
#define DEFAULT_I2C_NUMBER							1

namespace arduino
{
	namespace serial
	{

		typedef enum
		{
			DEC,
			HEX,
			OCT,
			BIN
		} ArduinoFormat_T;

		void uart_callback (const uint8_t c);
		class ArduinoSerial
		{
		public:

			ArduinoSerial();

			void begin(int Speed);
			void write(const char c);
			void print(const char* pString);
			void print(const char c);
			void print(const int c, ArduinoFormat_T format);
			void print(double d, int size);
			void println(const char c, ArduinoFormat_T format);
			void println(const char* pString);
			void println();

			int available();
			unsigned char read();

			::types::fifo uart_receive_fifo;

		private:

		}; //class Serial

		typedef ArduinoSerial HardwareSerial;
		extern ArduinoSerial Serial;

	} //namespace serial

} //namespace arduino

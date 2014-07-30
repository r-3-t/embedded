#include "arduino_serial.hpp"
#include <UartInterface.hpp>

#define ARDUINO_DEFAULT_SERIAL									1

#include <stdio.h>
#include <stdlib.h>


::uart::ConcreteUart UartCommand(ARDUINO_DEFAULT_SERIAL, &::arduino::serial::uart_callback);

namespace arduino
{
	namespace serial
	{

		ArduinoSerial Serial;

		void uart_callback (const uint8_t c)
		{
			Serial.uart_receive_fifo.push_back(c);
			return;
		}

		ArduinoSerial::ArduinoSerial()
		{
			return;
		}

		void ArduinoSerial::begin(int Speed)
		{
			UartCommand.Configure();
			this->uart_receive_fifo.clear();
			return;
		}

		void ArduinoSerial::write(const char c)
		{
			UartCommand.send((const unsigned char*)&c, sizeof(c));
		}

		void ArduinoSerial::print(const char* pString)
		{
			while (*pString)
			{
				UartCommand.send((const unsigned char*)&(pString[0]), sizeof(pString[0]));
				pString++;
			}
		}

		void ArduinoSerial::print(const char c)
		{
			UartCommand.send((const unsigned char*)&c, sizeof(c));
		}


		void ArduinoSerial::print(const int c, ArduinoFormat_T format)
		{
			char Buffer[32];
			memset(Buffer, 0, sizeof(Buffer));

			if (format == DEC)
			{
				sprintf(Buffer, "%i", c);
			}
			else if (format == HEX)
			{
				sprintf(Buffer, "%x", c);
			}
			else
			{
				sprintf(Buffer, "%x", c);
			}
			this->print(Buffer);

		}

		void ArduinoSerial::print(double d, int size)
		{
			char Buffer[16];
			memset(Buffer, 0, sizeof(Buffer));

			sprintf(Buffer, "%05f", d);

			this->print(Buffer);

		}

		void ArduinoSerial::println(const char c, ArduinoFormat_T format)
		{
			this->print(c, format);
			this->println();
		}

		void ArduinoSerial::println(const char* pString)
		{
			this->print(pString);
			this->println();
		}

		void ArduinoSerial::println()
		{
			this->print("\r\n");
		}

		int ArduinoSerial::available()
		{
			return this->uart_receive_fifo.size();
		}


		unsigned char ArduinoSerial::read()
		{
			uint8_t c;
			c = this->uart_receive_fifo.front();
			this->uart_receive_fifo.pop_front();
			return c;
		}


	} //namespace serial

} //namespace arduino

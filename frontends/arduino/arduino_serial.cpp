#include "arduino_serial.hpp"
#include <UartInterface.hpp>

#define ARDUINO_DEFAULT_SERIAL									1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

		int ArduinoSerial::write(const char* pString)
		{
			int i;

			i = 0;
			while (*pString)
			{
				this->write((const unsigned char*)&(pString[0]), sizeof(pString[0]));
				pString++;
				i++;
			}

			return i;
		}

		size_t ArduinoSerial::write(const unsigned char* pc, unsigned int size)
		{
			UartCommand.send((const unsigned char*)pc, size);
			return size;
		}


		int ArduinoSerial::available()
		{
			return this->uart_receive_fifo.size();
		}


		int ArduinoSerial::read()
		{
			uint8_t c;
			c = this->uart_receive_fifo.front();
			this->uart_receive_fifo.pop_front();
			return (int)c;
		}


	} //namespace serial

} //namespace arduino

#include "arduino_serial.hpp"
#include <UartInterface.hpp>

#define ARDUINO_DEFAULT_SERIAL									1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MONITOR_MEMORY_USAGE
#include <Stats.hpp>
Stats			ArduinoUartReceiveStats;
#endif //MONITOR_MEMORY_USAGE

#ifndef SERIAL_CIRCULAR_BUFFERS_SIZE
#define SERIAL_CIRCULAR_BUFFERS_SIZE							64
#endif //I2C_CIRCULAR_BUFFERS_SIZE

unsigned char uart_receive_buffer[SERIAL_CIRCULAR_BUFFERS_SIZE];

::uart::ConcreteUart ArduinoUart(ARDUINO_DEFAULT_SERIAL, &::arduino::serial::uart_callback);

namespace arduino
{
	namespace serial
	{

		ArduinoSerial Serial;

		void uart_callback (const uint8_t c)
		{
			int size;
			if (cbuff_enqueue(&Serial.uart_receive_fifo, (unsigned char*)&c, sizeof(c)) != 0)
			{
				abort();
			}
			size = Serial.uart_receive_fifo.cnt;
#ifdef MONITOR_MEMORY_USAGE
			ArduinoUartReceiveStats.log_memory_usage(size);
#endif //MONITOR_MEMORY_USAGE

			return;
		}

		ArduinoSerial::ArduinoSerial()
		{
			cbuff_init(&Serial.uart_receive_fifo, uart_receive_buffer, sizeof(uart_receive_buffer));
			return;
		}

		void ArduinoSerial::begin(int Speed)
		{
			ArduinoUart.Configure();
			cbuff_reset(&Serial.uart_receive_fifo);
			return;
		}

		void ArduinoSerial::write(const char c)
		{
			ArduinoUart.send((const unsigned char*)&c, sizeof(c));
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
			ArduinoUart.send((const unsigned char*)pc, size);
			return size;
		}


		int ArduinoSerial::available()
		{
			return this->uart_receive_fifo.cnt;
		}


		int ArduinoSerial::read()
		{

			uint8_t c;
			while (cbuff_dequeue1_to_register(&this->uart_receive_fifo, (unsigned char*)&c) == -1);
			return (c & 0xff);
		}

		void ArduinoSerial::set_callback(::uart::UartInterface::uart_callback_T callback)
		{
			ArduinoUart.set_callback(callback);
		}


	} //namespace serial

} //namespace arduino

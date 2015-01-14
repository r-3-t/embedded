#include "arduino_wire.hpp"
#include <I2cInterface.hpp>

#include <stdlib.h>

#ifdef MONITOR_MEMORY_USAGE
#include <Stats.hpp>
Stats			ArduinoWireReceiveStats;
Stats			ArduinoWireSendStats;
#endif //MONITOR_MEMORY_USAGE

#define ARDUINO_DEFAULT_I2C									1

#ifndef I2C_CIRCULAR_BUFFERS_SIZE
#define I2C_CIRCULAR_BUFFERS_SIZE							64
#endif //I2C_CIRCULAR_BUFFERS_SIZE

unsigned char i2c_receive_buffer[I2C_CIRCULAR_BUFFERS_SIZE];
unsigned char i2c_send_buffer[I2C_CIRCULAR_BUFFERS_SIZE];

//TODO: allow creation of an I2C slave
::i2c::ConcreteI2c DefaultMasterI2c(ARDUINO_DEFAULT_I2C, &::arduino::wire::arduino_master_receive_callback);

namespace arduino
{
	namespace wire
	{

		ArduinoWire Wire;

		void arduino_master_receive_callback(const uint8_t c)
		{
			int size;
			if (cbuff_enqueue(&Wire.i2c_receive_fifo, (unsigned char*)&c, sizeof(c)) != 0)
			{
				abort();
			}
			size = Wire.i2c_receive_fifo.cnt;
#ifdef MONITOR_MEMORY_USAGE
			ArduinoWireReceiveStats.log_memory_usage(size);
#endif //MONITOR_MEMORY_USAGE
			return;
		}

		void arduino_slave_receive_callback(const uint8_t c)
		{
			return;
		}

		void arduino_on_master_request_callback()
		{
			return;
		}

		ArduinoWire::ArduinoWire()
		{
			cbuff_init(&this->i2c_receive_fifo, i2c_receive_buffer, sizeof(i2c_receive_buffer));
			cbuff_init(&this->i2c_send_fifo, i2c_send_buffer, sizeof(i2c_send_buffer));
			return;
		}

		void ArduinoWire::begin()
		{
			cbuff_reset(&this->i2c_receive_fifo);
			cbuff_reset(&this->i2c_send_fifo);;
			return;
		}

		void ArduinoWire::begin(unsigned char SlaveAddress)
		{
			this->SlaveAddress = SlaveAddress;
			return;
		}

		void ArduinoWire::beginTransmission(unsigned char SlaveAddress)
		{
			DefaultMasterI2c.setSlaveAddress(SlaveAddress);
			return;
		}

		int ArduinoWire::write(uint8_t data)
		{
			if (cbuff_enqueue(&this->i2c_send_fifo, (unsigned char*)&data, sizeof(data)) != 0)
			{
				abort();
			}
#ifdef MONITOR_MEMORY_USAGE
			ArduinoWireSendStats.log_memory_usage(this->i2c_send_fifo.cnt);
#endif //MONITOR_MEMORY_USAGE
			return sizeof(data);
		}

		int ArduinoWire::write(const uint8_t* pData, int Size)
		{
			int i;

			for (i = 0; i < Size; i++)
			{
				if (cbuff_enqueue(&this->i2c_send_fifo, (unsigned char*)&pData[i], sizeof(pData[i])) != 0)
				{
					abort();
				}
#ifdef MONITOR_MEMORY_USAGE
				ArduinoWireSendStats.log_memory_usage(this->i2c_send_fifo.cnt);
#endif //MONITOR_MEMORY_USAGE
			}

			return Size;
		}

		int ArduinoWire::write(unsigned char* pString)
		{
			int i;

			i = 0;
			while (pString[i] != 0)
			{
				if (cbuff_enqueue(&this->i2c_send_fifo, (unsigned char*)&pString[i], sizeof(pString[i])) != 0)
				{
					abort();
				}
				i++;
#ifdef MONITOR_MEMORY_USAGE
				ArduinoWireSendStats.log_memory_usage(this->i2c_send_fifo.cnt);
#endif //MONITOR_MEMORY_USAGE
			}

			return i;
		}

		int ArduinoWire::endTransmission()
		{
			DefaultMasterI2c.send(this->i2c_send_fifo);
			cbuff_reset(&this->i2c_receive_fifo);
			cbuff_reset(&this->i2c_send_fifo);
			return 0;
		}

		int ArduinoWire::endTransmission(bool holdBus)
		{
			return this->endTransmission();
		}

		int ArduinoWire::available()
		{
			return this->i2c_receive_fifo.cnt;
		}

		uint8_t ArduinoWire::read()
		{
			uint8_t c;
			while (cbuff_dequeue1_to_register(&this->i2c_receive_fifo, (unsigned char*)&c) == -1);
			return (c & 0xff);
		}

		int ArduinoWire::requestFrom(unsigned char slave_address, int size)
		{
			DefaultMasterI2c.setSlaveAddress(slave_address);
			DefaultMasterI2c.request(size);
			DefaultMasterI2c.waitBusy();
			return this->available();
		}

		int ArduinoWire::requestFrom(unsigned char slave_address, int size, bool holdBus)
		{
			this->requestFrom(slave_address, size);
		}

	} //namespace i2c

} //namespace arduino

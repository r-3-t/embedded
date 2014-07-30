#include "arduino_wire.hpp"
#include <I2cInterface.hpp>

#define ARDUINO_DEFAULT_I2C									1

//TODO: allow creation of an I2C slave
::i2c::ConcreteI2c DefaultMasterI2c(ARDUINO_DEFAULT_I2C, &::arduino::wire::arduino_master_receive_callback);

namespace arduino
{
	namespace wire
	{

		ArduinoWire Wire;

		void arduino_master_receive_callback(const uint8_t c)
		{
			Wire.i2c_receive_buffer.push_back(c);
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
			return;
		}

		void ArduinoWire::begin()
		{
			this->i2c_send_buffer.clear();
			this->i2c_receive_buffer.clear();
			return;
		}

		void ArduinoWire::begin(unsigned char SlaveAddress)
		{
			this->SlaveAddress = SlaveAddress;
			return;
		}

		void ArduinoWire::beginTransmission(unsigned char SlaveAddress)
		{
			DefaultMasterI2c.setSlaveAddress(SlaveAddress, ::i2c::MasterWriteToSlave);
			return;
		}

		int ArduinoWire::write(uint8_t data)
		{
			this->i2c_send_buffer.push_back(data);
			return sizeof(data);
		}

		int ArduinoWire::write(const uint8_t* pData, int Size)
		{
			int i;

			for (i = 0; i < Size; i++)
			{
				this->i2c_send_buffer.push_back(pData[i]);
			}

			return Size;
		}

		int ArduinoWire::write(unsigned char* pString)
		{
			int i;

			i = 0;
			while (pString[i] != 0)
			{
				this->i2c_send_buffer.push_back(pString[i++]);
			}

			return i;
		}

		int ArduinoWire::endTransmission()
		{
			DefaultMasterI2c.send(this->i2c_send_buffer);
			this->i2c_receive_buffer.clear();
			this->i2c_send_buffer.clear();
			return 0;
		}

		int ArduinoWire::endTransmission(bool holdBus)
		{
			return this->endTransmission();
		}

		int ArduinoWire::available()
		{
			return this->i2c_receive_buffer.size();
		}

		uint8_t ArduinoWire::read()
		{
			uint8_t c;
			c = this->i2c_receive_buffer.front();
			this->i2c_receive_buffer.pop_front();
			return c;
		}

		int ArduinoWire::requestFrom(unsigned char slave_address, int size)
		{
			DefaultMasterI2c.setSlaveAddress(slave_address, ::i2c::MasterReadFromSlave);
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

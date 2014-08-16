#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>
#include <I2cInterface.hpp>
#include <gpio.h>
#include <i2c.h>
#include <interrupt.h>
#include <hw_ints.h>
#include <stdio.h>
#include <stdlib.h>

#define TIXX_I2C_MAX_COUNT								3

namespace tix
{

	namespace i2c
	{

		static ::tix::i2c::I2c*				gpI2cs[TIXX_I2C_MAX_COUNT];

#define I2C_IRQ_CALLBACK(I2cX) void I2C##I2cX##_IRQHandler()											\
		{																								\
			unsigned long status;																		\
			unsigned long flags;																		\
			if (gpI2cs[I2cX]->config.Mode == ::i2c::Configuration::Master)									\
			{																							\
				status = I2CMasterIntStatusEx(gpI2cs[I2cX]->I2C_Base, false);								\
				flags = I2CMasterErr(gpI2cs[I2cX]->I2C_Base);												\
				if (gpI2cs[I2cX]->requestEnabled)															\
				{																						\
					gpI2cs[I2cX]->_receive_callback(gpI2cs[I2cX]->receive());									\
				}																						\
				I2CMasterIntClear(gpI2cs[I2cX]->I2C_Base);													\
			}																							\
			else																						\
			{																							\
				status = I2CSlaveIntStatusEx(gpI2cs[I2cX]->I2C_Base, false);								\
				flags = I2CSlaveStatus(gpI2cs[I2cX]->I2C_Base);											\
				if ( (flags & I2C_SLAVE_ACT_RREQ) == I2C_SLAVE_ACT_RREQ)								\
				{																						\
					gpI2cs[I2cX]->_receive_callback(gpI2cs[I2cX]->receive());									\
				}																						\
				else if ( (flags & I2C_SLAVE_ACT_TREQ) == I2C_SLAVE_ACT_TREQ)							\
				{																						\
					gpI2cs[I2cX]->_on_master_request_callback();											\
				}																						\
				I2CSlaveIntClear(gpI2cs[I2cX]->I2C_Base);													\
			}																							\
		}

		extern "C"
		{

				I2C_IRQ_CALLBACK(0)
				I2C_IRQ_CALLBACK(1)
				I2C_IRQ_CALLBACK(2)

		}

		I2c::I2c(unsigned int id, ::i2c::I2cInterface::i2c_receive_callback receive_callback, ::i2c::Configuration config, ::i2c::I2cInterface::i2c_on_master_request_callback on_master_request_callback)
		{
			_id = id;
			_receive_callback = receive_callback;
			_on_master_request_callback = on_master_request_callback;
			this->config = config;
			_configured = false;
			this->requestEnabled = false;
			this->_slave_address = 0xFF;

			gpI2cs[id - 1] = this;
		}

		void I2c::Configure()
		{

			//GPIO configuration for I2C use
			unsigned long SclPinConfig;
			unsigned long SdaPinConfig;

			//clocks associated to I2C
			unsigned long I2cPeripheral;
			unsigned long GPIOPeripheral;

			// the gpio used
			unsigned long GPIO_Port;
			unsigned char GPIO_Pin_Scl;			// the selected pin
			unsigned char GPIO_Pin_Sda;			// the selected pin

			switch (_id)
			{
			case 1:
				if (this->config.Mode == ::i2c::Configuration::Master)
				{
					I2C_Base = I2C0_MASTER_BASE;
				}
				else
				{
					I2C_Base = I2C0_SLAVE_BASE;
				}

				I2cPeripheral = SYSCTL_PERIPH_I2C0;
				GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
				SclPinConfig = GPIO_PB2_I2C0SCL;
				SdaPinConfig = GPIO_PB3_I2C0SDA;
				GPIO_Port = GPIO_PORTB_BASE;
				GPIO_Pin_Scl = GPIO_PIN_2;
				GPIO_Pin_Sda = GPIO_PIN_3;
				// Register interrupt handler
				I2CIntRegister(I2C0_MASTER_BASE, I2C0_IRQHandler);
				break;
			case 2:
				if (this->config.Mode == ::i2c::Configuration::Master)
				{
					I2C_Base = I2C1_MASTER_BASE;
				}
				else
				{
					I2C_Base = I2C1_SLAVE_BASE;
				}

				I2cPeripheral = SYSCTL_PERIPH_I2C1;
				GPIOPeripheral = SYSCTL_PERIPH_GPIOA;
				SclPinConfig = GPIO_PA6_I2C1SCL;
				SdaPinConfig = GPIO_PA7_I2C1SDA;
				GPIO_Port = GPIO_PORTA_BASE;
				GPIO_Pin_Scl = GPIO_PIN_6;
				GPIO_Pin_Sda = GPIO_PIN_7;
				// Register interrupt handler
				I2CIntRegister(I2C1_MASTER_BASE, I2C1_IRQHandler);
				break;
			case 3:
				if (this->config.Mode == ::i2c::Configuration::Master)
				{
					I2C_Base = I2C2_MASTER_BASE;
				}
				else
				{
					I2C_Base = I2C2_SLAVE_BASE;
				}

				I2cPeripheral = SYSCTL_PERIPH_I2C2;
				GPIOPeripheral = SYSCTL_PERIPH_GPIOE;
				SclPinConfig = GPIO_PE4_I2C2SCL;
				SdaPinConfig = GPIO_PE5_I2C2SDA;
				GPIO_Port = GPIO_PORTE_BASE;
				GPIO_Pin_Scl = GPIO_PIN_4;
				GPIO_Pin_Sda = GPIO_PIN_5;
				UARTIntRegister(I2C2_MASTER_BASE, I2C2_IRQHandler);
				break;
			default:
				return;
				break;
			} //end switch


			//
			// Enable the peripherals
			//
			SysCtlPeripheralEnable(GPIOPeripheral);
			SysCtlPeripheralEnable(I2cPeripheral);


			//
			// Set GPIO for I2C pins.
			//
			GPIOPinConfigure(SclPinConfig);
			GPIOPinConfigure(SdaPinConfig);

			GPIOPinTypeI2C(GPIO_Port, GPIO_Pin_Sda);
			GPIOPinTypeI2CSCL(GPIO_Port, GPIO_Pin_Scl);

			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				// Enable interrupt on RX event
				I2CMasterIntEnableEx(I2C_Base, I2C_MASTER_INT_DATA);

				// Enable and Initialize Master module and Master Clock using 100kbps
				I2CMasterInitExpClk(I2C_Base, SysCtlClockGet(), 0);
			}
			else
			{
				// Enable interrupt on RX event
				I2CSlaveIntEnableEx(I2C_Base, I2C_SLAVE_INT_DATA);
				
				// Enable and Initialize Slave
				I2CSlaveInit(I2C_Base, 0x42 /* TODO: to pass to arg */);
			}
			
		
			_configured = true;
		}

		void I2c::send(const char c)
		{
			if (_configured == false)
			{
				this->Configure();
			}

			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				this->waitBusy();

				I2CMasterSlaveAddrSet(this->I2C_Base, this->_slave_address, false /*write to slave*/);

				this->requestEnabled = false;
				I2CMasterDataPut(I2C_Base, c & 0xFF);
				I2CMasterControl(I2C_Base, I2C_MASTER_CMD_SINGLE_SEND);

				//wait controller to be ready
				this->waitBusy();
				if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
				{
					goto cleanup;
				}
			}
			else
			{
				I2CSlaveDataPut(I2C_Base, c & 0xFF);
			}

			return;

cleanup:
			fprintf(stderr, "Failed in I2C transaction on send !");
			abort();
			return;

		}


		void I2c::send(const types::buffer& buf)
		{
			unsigned int i;
			char c;

			if (_configured == false)
			{
				this->Configure();
			}

			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				this->requestEnabled = false;

				//if no data
				if (buf.size() == 0)
				{
					return;
				}

				//if buf has only one data
				if (buf.size() == 1)
				{
					this->send(buf[0]);
					return;
				}

				this->waitBusy();

				I2CMasterSlaveAddrSet(this->I2C_Base, this->_slave_address, false /*write to slave*/);

				//send first byte
				c = buf[0];
				I2CMasterDataPut(I2C_Base, c & 0xFF);
				I2CMasterControl(I2C_Base, I2C_MASTER_CMD_BURST_SEND_START);

				//wait controller to be ready
				this->waitBusy();
				if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
				{
					goto cleanup;
				}

				for (i = 1; i < buf.size() - 1; i++)
				{
					//send bytes
					c = buf[i];
					I2CMasterDataPut(I2C_Base, c & 0xFF);
					I2CMasterControl(I2C_Base, I2C_MASTER_CMD_BURST_SEND_CONT);

					//wait controller to be ready
					this->waitBusy();
					if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
					{
						goto cleanup;
					}

				}

				//send last byte
				c = buf[buf.size() - 1];
				I2CMasterDataPut(I2C_Base, c & 0xFF);
				I2CMasterControl(I2C_Base, I2C_MASTER_CMD_BURST_SEND_FINISH);

				//wait controller to be ready
				this->waitBusy();
				if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
				{
					goto cleanup;
				}
			}

			return;

cleanup:
			fprintf(stderr, "Failed in I2C transaction on send !");
			abort();
			return;
		}



		unsigned char I2c::receive()
		{
			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				return (unsigned char) (I2CMasterDataGet(I2C_Base) & 0xFF);
			}
			else
			{
				return (unsigned char) (I2CSlaveDataGet(I2C_Base) & 0xFF);
			}
			
		}

		void I2c::request()
		{
			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				this->requestEnabled = true;

				I2CMasterSlaveAddrSet(this->I2C_Base, this->_slave_address, true /*read from slave*/);

				I2CMasterControl(I2C_Base, I2C_MASTER_CMD_SINGLE_RECEIVE);

				//wait controller to be ready
				this->waitBusy();
				if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
				{
					goto cleanup;
				}
			}

			return;

cleanup:
			fprintf(stderr, "Failed in I2C transaction on request !");
			abort();
			return;

		}

		void I2c::request(int BytesCount)
		{
			int request_count;

			this->waitBusy();

			if (BytesCount == 1)
			{
				this->request();
				return;
			}

			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				I2CMasterSlaveAddrSet(this->I2C_Base, this->_slave_address, true /*read from slave*/);

				this->requestEnabled = true;

				//send first request
				I2CMasterControl(I2C_Base, I2C_MASTER_CMD_BURST_RECEIVE_START);

				//wait controller to be ready
				this->waitBusy();
				if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
				{
					goto cleanup;
				}


				request_count = 0;
				while (request_count < (BytesCount - 2))
				{
					//continue receiving
					I2CMasterControl(I2C_Base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

					//wait controller to be ready
					this->waitBusy();
					if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
					{
						goto cleanup;
					}

					request_count++;
				}

				//finish receiving
				I2CMasterControl(I2C_Base, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

				this->waitBusy();
				if (I2CMasterErr(I2C_Base) != I2C_MASTER_ERR_NONE)
				{
					goto cleanup;
				}
			}

			return;

cleanup:
			fprintf(stderr, "Failed in I2C transaction on request !");
			abort();
			return;


		}

		void I2c::setSlaveAddress(const unsigned char Address)
		{
			if (_configured == false)
			{
				this->Configure();
			}
			
			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				this->_slave_address = Address;
			}
			else
			{
				I2CSlaveAddressSet(this->I2C_Base, 0, Address);
			}
			
		}
		
		void I2c::waitBusy()
		{
			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				while (I2CMasterBusy(this->I2C_Base) == true);
			}


		}


	} /* namespace i2c  */

} /* namespace tix  */


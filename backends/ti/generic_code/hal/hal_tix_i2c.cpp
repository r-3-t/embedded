#include <hal/usart_conf.hpp>
#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>
#include <I2cInterface.hpp>
#include <hal/I2c.hpp>
#include <gpio.h>
#include <i2c.h>

#define TIXX_I2C_MAX_COUNT								3

namespace tix
{

	namespace i2c
	{

		static ::tix::i2c::I2c*				gpI2cs[TIXX_I2C_MAX_COUNT];

		/*
		#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQHandler()																\
											{																								\
												unsigned long status;																		\
												status = UARTIntStatus(gpI2cs[UsartX]->UART_Base, false);								\
												if ((status & UART_INT_RX) == UART_INT_RX)													\
												{																							\
													gpI2cs[UsartX]->_callback(gpI2cs[UsartX]->receive());							\
												}																							\
												status = UARTIntStatus(gpI2cs[UsartX]->UART_Base, true);								\
												UARTIntClear(gpI2cs[UsartX]->UART_Base, status);										\
											}

		extern "C"
		{

			USART_IRQ_CALLBACK(0)
			USART_IRQ_CALLBACK(1)
			USART_IRQ_CALLBACK(2)

		}*/
		
		void I2C0IRQHandler()																
		{																								
			unsigned long status;
			
			if (gpI2cs[0]->config.Mode == ::i2c::Configuration::Master)
			{
				status = I2CMasterIntStatusEx(gpI2cs[0]->I2C_Base, false);
				if ((status & I2C_MASTER_INT_DATA) == I2C_MASTER_INT_DATA)													
				{																							
					gpI2cs[0]->_callback(gpI2cs[0]->receive());							
				}
				I2CMasterIntClearEx(gpI2cs[0]->I2C_Base, I2C_MASTER_INT_DATA);
			}
			else
			{
				status = I2CSlaveIntStatusEx(gpI2cs[0]->I2C_Base, false);
				if ((status & I2C_SLAVE_INT_DATA) == I2C_SLAVE_INT_DATA)													
				{																							
					gpI2cs[0]->_callback(gpI2cs[0]->receive());							
				}
				I2CSlaveIntClearEx(gpI2cs[0]->I2C_Base, I2C_SLAVE_INT_DATA);
			}
			
		}
		
		void I2C1IRQHandler()																
		{																								
			unsigned long status;
			
			if (gpI2cs[1]->config.Mode == ::i2c::Configuration::Master)
			{
				status = I2CMasterIntStatusEx(gpI2cs[1]->I2C_Base, false);
				if ((status & I2C_MASTER_INT_DATA) == I2C_MASTER_INT_DATA)													
				{																							
					gpI2cs[1]->_callback(gpI2cs[1]->receive());							
				}
				I2CMasterIntClearEx(gpI2cs[1]->I2C_Base, I2C_MASTER_INT_DATA);
			}
			else
			{
				status = I2CSlaveIntStatusEx(gpI2cs[1]->I2C_Base, false);
				if ((status & I2C_SLAVE_INT_DATA) == I2C_SLAVE_INT_DATA)													
				{																							
					gpI2cs[1]->_callback(gpI2cs[1]->receive());							
				}
				I2CSlaveIntClearEx(gpI2cs[1]->I2C_Base, I2C_SLAVE_INT_DATA);
			}
			
		}

		I2c::I2c(unsigned int id, ::i2c::I2cInterface::i2c_callback callback, ::i2c::Configuration config)
		{
			_id = id;
			_callback = callback;
			config = config;
			_configured = false;

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
				I2CIntRegister(I2C_Base, I2C0IRQHandler);
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
				I2CIntRegister(I2C_Base, I2C1IRQHandler);
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
				//UARTIntRegister(UART_Base, USART0_IRQHandler);
				break;
			default:
				return;
				break;
			} //end switch


			//
			// Enable the peripherals
			//
			SysCtlPeripheralEnable(I2cPeripheral);
			SysCtlPeripheralEnable(GPIOPeripheral);


			//
			// Set GPIO for I2C pins.
			//
			GPIOPinConfigure(SclPinConfig);
			GPIOPinConfigure(SdaPinConfig);


			GPIOPinTypeI2C(GPIO_Port, GPIO_Pin_Scl | GPIO_Pin_Sda);


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
				
				I2CSlaveIntEnable(I2C_Base);
				
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
				I2CMasterDataPut(I2C_Base, c & 0xFF);
				I2CMasterControl(I2C_Base, I2C_MASTER_CMD_SINGLE_SEND);
			}
			else
			{
				I2CSlaveDataPut(I2C_Base, c & 0xFF);
			}

		}


		void I2c::send(const types::buffer& buf)
		{
			for (auto c : buf)
			{
				this->send(c);

			}

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

		void I2c::setSlaveAddress(const unsigned char Address, ::i2c::MasterOperation_T MasterOperation)
		{
			if (_configured == false)
			{
				this->Configure();
			}
			
			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				if (MasterOperation == ::i2c::MasterWriteToSlave)
				{
					I2CMasterSlaveAddrSet(this->I2C_Base, Address, false /*write to slave*/);
				}
				else
				{
					I2CMasterSlaveAddrSet(this->I2C_Base, Address, true /*read from slave*/);
				}
			}
			else
			{
				I2CSlaveAddressSet(this->I2C_Base, 0, Address);
			}
			
		}
		

	} /* namespace i2c  */

} /* namespace tix  */


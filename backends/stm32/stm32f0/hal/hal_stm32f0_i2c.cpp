#include <stm32f0xx_i2c.h>
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_misc.h>

#include <I2cInterface.hpp>
#include <hal_stm32f0_i2c.hpp>

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TIXX_I2C_MAX_COUNT								3

namespace stm32f0xx
{

	namespace i2c
	{

		static ::stm32f0xx::i2c::I2c*				gpI2cs[TIXX_I2C_MAX_COUNT];

#define I2C_IRQ_CALLBACK(I2cX) void I2C##I2cX##_IRQHandler()											\
		{																								\
			if (gpI2cs[I2cX-1]->config.Mode == ::i2c::Configuration::Master)								\
			{																							\
				/*master receive data from slave*/														\
				if (I2C_GetITStatus(gpI2cs[I2cX-1]->_I2C, I2C_IT_RXNE) == SET)							\
				{																						\
					gpI2cs[I2cX-1]->_receive_callback(gpI2cs[I2cX-1]->receive());							\
				}																						\
			}																							\
			else																						\
			{																							\
				/*slave received data from master*/														\
				if (I2C_GetITStatus(gpI2cs[I2cX-1]->_I2C, I2C_IT_RXNE) == SET)							\
				{																						\
					gpI2cs[I2cX-1]->_receive_callback(gpI2cs[I2cX-1]->receive());							\
				}																						\
				/*master request data*/																	\
				if (I2C_GetITStatus(gpI2cs[I2cX-1]->_I2C, I2C_IT_TXIS) == SET)							\
				{																						\
					gpI2cs[I2cX-1]->_on_master_request_callback();										\
				}																						\
				/*master send address and match this slave*/											\
				if (I2C_GetITStatus(gpI2cs[I2cX-1]->_I2C, I2C_IT_ADDR) == SET)							\
				{																						\
					/*reset last byte sent in transmit register*/										\
					gpI2cs[I2cX-1]->_I2C->ISR = I2C_ISR_TXE;												\
					I2C_ClearITPendingBit(gpI2cs[I2cX-1]->_I2C, I2C_IT_ADDR);								\
				}																						\
			}																							\
			return;																						\
		}

		extern "C"
		{
				I2C_IRQ_CALLBACK(1)
				I2C_IRQ_CALLBACK(2)
		}



		I2c::I2c(unsigned int id, ::i2c::I2cInterface::i2c_receive_callback receive_callback, ::i2c::Configuration config, ::i2c::I2cInterface::i2c_on_master_request_callback on_master_request_callback)
		{
			this->_id = id;
			this->_receive_callback = receive_callback;
			this->_on_master_request_callback = on_master_request_callback;
			this->config = config;
			this->_configured = false;
			this->_slave_address = 0xFF;

			gpI2cs[id - 1] = this;
		}


		void I2c::Configure()
		{
			GPIO_InitTypeDef  	GPIO_InitStructure;

			uint32_t 			RCC_AHBxPeriph_GPIOx;
			GPIO_TypeDef* 		SCL_GPIOx;
			GPIO_TypeDef*		SDA_GPIOx;
			uint32_t			GPIO_Pin_SCL, GPIO_Pin_SDA;
			uint16_t			GPIO_PinSource_SCL, GPIO_PinSource_SDA;
			uint32_t	  		RCC_APBxPeriph_I2Cx;
			uint8_t				GPIO_AF_SCL, GPIO_AF_SDA;
			NVIC_InitTypeDef	NVIC_InitStructure;

			_configured = true;

			switch (_id)
			{
			case 1:
				SCL_GPIOx = GPIOB;
				SDA_GPIOx = GPIOB;
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOB;
				GPIO_Pin_SCL = GPIO_Pin_6;
				GPIO_Pin_SDA = GPIO_Pin_7;
				RCC_APBxPeriph_I2Cx = RCC_APB1Periph_I2C1;
				GPIO_PinSource_SCL = GPIO_PinSource6;
				GPIO_PinSource_SDA = GPIO_PinSource7;
				GPIO_AF_SCL = GPIO_AF_1;
				GPIO_AF_SDA = GPIO_AF_1;
				this->_I2C = I2C1;
				NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;

				break;
			case 2:
				SCL_GPIOx = GPIOB;
				SDA_GPIOx = GPIOB;
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOB;
				GPIO_Pin_SCL = GPIO_Pin_10;
				GPIO_Pin_SDA = GPIO_Pin_11;
				RCC_APBxPeriph_I2Cx = RCC_APB1Periph_I2C2;
				GPIO_PinSource_SCL = GPIO_PinSource10;
				GPIO_PinSource_SDA = GPIO_PinSource11;
				GPIO_AF_SCL = GPIO_AF_1;
				GPIO_AF_SDA = GPIO_AF_1;
				this->_I2C = I2C2;
				NVIC_InitStructure.NVIC_IRQChannel = I2C2_IRQn;

				break;
			default:
				return;
				break;
			} //end switch

			/* Configure the I2C clock source. The clock is derived from the HSI */
			RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);

			RCC_AHBPeriphClockCmd(RCC_AHBxPeriph_GPIOx, ENABLE);

			RCC_APB1PeriphClockCmd(RCC_APBxPeriph_I2Cx, ENABLE);

			GPIO_PinAFConfig(SCL_GPIOx, GPIO_PinSource_SCL, GPIO_AF_SCL);

			GPIO_PinAFConfig(SDA_GPIOx, GPIO_PinSource_SDA, GPIO_AF_SDA);

			/* configure GPIOS */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SCL;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(SCL_GPIOx, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SDA;
			GPIO_Init(SDA_GPIOx, &GPIO_InitStructure);

			NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

			NVIC_Init(&NVIC_InitStructure);


		}

		void I2c::send(const char c)
		{
			if (_configured == false)
			{
				return;
			}

			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				this->waitBusy();

				/* Configure slave address, nbytes, reload and generate start */
				I2C_TransferHandling(this->_I2C, this->_slave_address << 1, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);

				/* Wait until TXIS flag is set */
				while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_TXIS) == RESET);

				/* Send data */
				I2C_SendData(this->_I2C, (uint8_t)c);

				/* Wait until STOP flag is set */
				//while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_STOPF) == RESET);
				this->waitBusy();

			}
			else
			{
				/* Wait until TXIS flag is set */
				while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_TXIS) == RESET);

				/* Send data */
				I2C_SendData(this->_I2C, (uint8_t)c);
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
				return;
			}

			if (this->config.Mode == ::i2c::Configuration::Master)
			{
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

				//send first byte
				c = buf[0];

				this->waitBusy();

				/* Configure slave address, nbytes, reload and generate start */
				I2C_TransferHandling(this->_I2C, this->_slave_address << 1, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);

				/* Wait until TXIS flag is set */
				while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_TXIS) == RESET);

				/* Send data */
				I2C_SendData(this->_I2C, (uint8_t)c);

				//wait transfer reload complete
				while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_TCR) == RESET);

				/* Configure slave address, nbytes, reload and generate start */
				I2C_TransferHandling(this->_I2C, this->_slave_address << 1, (buf.size() - 1), I2C_AutoEnd_Mode, I2C_No_StartStop);

				for (i = 1; i < buf.size(); i++)
				{
					//send bytes
					c = buf[i];

					/* Wait until TXIS flag is set */
					while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_TXIS) == RESET);

					/* Send data */
					I2C_SendData(this->_I2C, (uint8_t)c);

				}

				/* Wait until STOP flag is set */
				//while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_STOPF) == RESET);
				this->waitBusy();

			}

			return;

cleanup:
			fprintf(stderr, "Failed in I2C transaction on send !");
			abort();
			return;
		}



		unsigned char I2c::receive()
		{
			if (_configured == false)
			{
				return 0xFF;
			}
			return (unsigned char)(I2C_ReceiveData(this->_I2C)& 0xFF);
		}

		void I2c::request(int BytesCount)
		{

			//TODO: Fix BytesCount > 255

			if (_configured == false)
			{
				return;
			}

			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				this->waitBusy();

				/* Configure slave address, nbytes, reload and generate start */
				I2C_TransferHandling(this->_I2C, this->_slave_address << 1, BytesCount, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

			}

			return;

cleanup:
			fprintf(stderr, "Failed in I2C transaction on request !");
			abort();
			return;


		}

		void I2c::setSlaveAddress(const uint8_t slave_address)
		{
			I2C_InitTypeDef  	I2C_InitStructure;

			//prevent reconfiguration
			if (this->_slave_address == slave_address)
			{
				return;
			}

			if ( (this->config.Mode == ::i2c::Configuration::Master) && (_configured == true))
			{
				return;
			}

			if (_configured == false)
			{
				this->Configure();
			}
			
			this->_slave_address = slave_address;

			/* configure I2C controller */
			I2C_StructInit(&I2C_InitStructure);

			I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
			I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
			I2C_InitStructure.I2C_DigitalFilter = 0x00;
			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				I2C_InitStructure.I2C_OwnAddress1 = 0x00;
			}
			else
			{
				I2C_InitStructure.I2C_OwnAddress1 = this->_slave_address << 1;
			}
			I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
			I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
			//I2C_InitStructure.I2C_Timing = 0x00210507;
			I2C_InitStructure.I2C_Timing = 0x20210507;
			
			I2C_Init(this->_I2C, &I2C_InitStructure);

			this->enable();

		}

		void I2c::enable()
		{
			I2C_ITConfig(this->_I2C, I2C_IT_RXI, ENABLE);

			if (this->config.Mode == ::i2c::Configuration::Slave)
			{
				I2C_ITConfig(this->_I2C, I2C_IT_TXI, ENABLE);
				I2C_ITConfig(this->_I2C, I2C_IT_ADDRI, ENABLE);

			}

			I2C_Cmd(this->_I2C, ENABLE);
		}
		
		void I2c::waitBusy()
		{
			if (this->config.Mode == ::i2c::Configuration::Master)
			{
				/* Wait until BUSY flag is set */
				while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_BUSY) == SET);
			}
			else
			{
				/* Wait until TCIS flag is set */
				while(I2C_GetFlagStatus(this->_I2C, I2C_FLAG_TXIS) == RESET);
			}

		}


	} /* namespace i2c  */

} /* namespace stm32f0xx  */


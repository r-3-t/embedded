#pragma once

#include <spi.hpp>
#include <hal/gpio.hpp>
#include <stm32f10x_spi.h>
#include <hal/stm32fx/spi_conf.hpp>


namespace spi
{
	unsigned int	num_instance();

	void init_instance(unsigned int id, Configuration config /*= Configuration::_default()*/);

	Spi& get_instance(unsigned int id);

}


namespace stm32f1xx {

namespace  spi {

	using namespace stm32fx::spi;

	class Stm32f1xx_Spi : public ::spi::Spi
	{
	public:
		Stm32f1xx_Spi(unsigned int id, ::spi::Configuration config = ::spi::Configuration::_default()) :
							::spi::Spi(id)
		{
			//GPIO_InitTypeDef GPIO_InitStruct;
			SPI_InitTypeDef SPI_InitStruct;

			void 		(*pfvRCC_APBxPeriphClockCmd)(uint32_t, FunctionalState);
			uint32_t	  RCC_APBxPeriph_SPIx;



			// the gpio used
			GPIO_TypeDef* 	GPIOx;
			uint32_t		GPIO_Pin_NSS;			// the selected pin
			uint32_t		GPIO_Pin_SCK;			// the selected pin
			uint32_t		GPIO_Pin_MISO;			// the selected pin
			uint32_t		GPIO_Pin_MOSI;			// the selected pin

			switch (id)
			{
				case 1:
							_SPIx						= SPI1;
							GPIOx						= GPIOA;
							GPIO_Pin_NSS				= GPIO_Pin_4;
							GPIO_Pin_SCK				= GPIO_Pin_5;
							GPIO_Pin_MISO				= GPIO_Pin_6;
							GPIO_Pin_MOSI				= GPIO_Pin_7;

							pfvRCC_APBxPeriphClockCmd	= RCC_APB2PeriphClockCmd;
							RCC_APBxPeriph_SPIx			= RCC_APB2Periph_SPI1;
							break;

				case 2:
							_SPIx						= SPI2;
							GPIOx						= GPIOB;
							GPIO_Pin_NSS				= GPIO_Pin_12;
							GPIO_Pin_SCK				= GPIO_Pin_13;
							GPIO_Pin_MISO				= GPIO_Pin_14;
							GPIO_Pin_MOSI				= GPIO_Pin_15;

							pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
							RCC_APBxPeriph_SPIx			= RCC_APB1Periph_SPI2;
							break;

				default:
							_SPIx						= nullptr;
							GPIOx						= nullptr;
							GPIO_Pin_NSS				= -1;
							GPIO_Pin_SCK				= -1;
							GPIO_Pin_MISO				= -1;
							GPIO_Pin_MOSI				= -1;

							pfvRCC_APBxPeriphClockCmd	= nullptr;
							RCC_APBxPeriph_SPIx			= -1;
							break;
			}

			/* configure pins used by SPIx
			 * PA5 = SCK
			 * PA6 = MISO
			 * PA7 = MOSI
			 */
			if (conf_2_mode(config.mode) == SPI_Mode_Master)
			{
				//master
				::gpio::configure_pin(GPIOx, GPIO_Pin_SCK, GPIO_Mode_AF_PP);
				::gpio::configure_pin(GPIOx, GPIO_Pin_MOSI, GPIO_Mode_AF_PP);
				::gpio::configure_pin(GPIOx, GPIO_Pin_MISO, GPIO_Mode_IN_FLOATING);
				if (conf_2_SlaveSelectManagement(config.slaveSelectManagement) == SPI_NSS_Hard)
				{
					//nss hard
					::gpio::configure_pin(GPIOx, GPIO_Pin_NSS, GPIO_Mode_AF_PP);
				}

			}
			else
			{
				//slave
				::gpio::configure_pin(GPIOx, GPIO_Pin_SCK, GPIO_Mode_IN_FLOATING);
				::gpio::configure_pin(GPIOx, GPIO_Pin_MOSI, GPIO_Mode_IN_FLOATING);
				::gpio::configure_pin(GPIOx, GPIO_Pin_MISO, GPIO_Mode_AF_PP);
				if (conf_2_SlaveSelectManagement(config.slaveSelectManagement) == SPI_NSS_Hard)
				{
					//nss hard
					::gpio::configure_pin(GPIOx, GPIO_Pin_NSS, GPIO_Mode_IN_FLOATING);
				}

			}

			// enable peripheral clock
			pfvRCC_APBxPeriphClockCmd(RCC_APBxPeriph_SPIx, ENABLE);
			

			/* configure SPI1 in Mode 0 
			 * CPOL = 0 --> clock is low when idle
			 * CPHA = 0 --> data is sampled at the first edge
			 */
			SPI_InitStruct.SPI_Direction			= conf_2_direction(config.direction); // set to full duplex mode, seperate MOSI and MISO lines
			SPI_InitStruct.SPI_Mode					= conf_2_mode(config.mode);     // transmit in master mode, NSS pin has to be always high
			SPI_InitStruct.SPI_DataSize 			= SPI_DataSize_8b; // one packet of data is 8 bits wide
			SPI_InitStruct.SPI_CPOL 				= conf_2_ClockPolarity(config.clockPolarity);        // clock is low when idle
			SPI_InitStruct.SPI_CPHA 				= conf_2_ClockPhase(config.clockPhase);      // data sampled at first edge
			SPI_InitStruct.SPI_NSS 					= conf_2_SlaveSelectManagement(config.slaveSelectManagement); // set the NSS management to internal and pull internal NSS high
			SPI_InitStruct.SPI_BaudRatePrescaler 	= conf_2_BaudRatePrescaler(config.baudRatePrescaler); // SPI frequency is APB2 frequency / 4
			SPI_InitStruct.SPI_FirstBit 			= conf_2_FirstBitTransmission(config.firstBitTransmission);// data is transmitted MSB first
			SPI_InitStruct.SPI_CRCPolynomial		= config.CRCPolynomial;
			SPI_I2S_DeInit(_SPIx);
			SPI_Init(_SPIx, &SPI_InitStruct); 
			
			SPI_Cmd(_SPIx, ENABLE); // enable SPI1

		}

		virtual uint8_t send(uint8_t data)
		{
			SPI_I2S_SendData (_SPIx, data);

			/*!< Wait until the transmit buffer is empty */
  			while (SPI_I2S_GetFlagStatus (_SPIx, SPI_I2S_FLAG_TXE) == RESET);

  			while( (_SPIx->SR & SPI_I2S_FLAG_RXNE) == RESET); // wait until receive complete

  			while( _SPIx->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore

  			return _SPIx->DR;
		}

		virtual uint8_t recv()
		{
			/*!< Wait until a data is received */
			while (SPI_I2S_GetFlagStatus(_SPIx, SPI_I2S_FLAG_RXNE) == RESET);
			
			/*!< Get the received data */
			uint8_t c = SPI_I2S_ReceiveData(_SPIx);

			// wait until SPI is not busy anymore
			while( SPI1->SR & SPI_I2S_FLAG_BSY ); 

			return c;
		}

		virtual void register_callback(void (*callback)(::spi::Spi&))
		{
			_callback = callback;

			unsigned int	IRQn;

			switch (_id)
			{
			case 1:	IRQn = SPI1_IRQn;
					break;

			case 2:	IRQn = SPI2_IRQn;
					break;

			default:
					IRQn = (unsigned int)-1;
			}

			SPI_I2S_ITConfig(_SPIx, SPI_I2S_IT_RXNE, ENABLE);
			NVIC_InitTypeDef    NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)
			NVIC_InitStructure.NVIC_IRQChannel = IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART2 interrupts
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     // this sets the subpriority inside the group
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      // the USART2 interrupts are globally enabled
			NVIC_Init(&NVIC_InitStructure);              // the properties are passed to the NVIC_Init function which takes care of the low level stuff
		}
		private:
			SPI_TypeDef* _SPIx;
	};


	static ::spi::Spi* gpSpi_1 = nullptr;
	static ::spi::Spi* gpSpi_2 = nullptr;


	#define SPI_IRQ_CALLBACK(SpiX)	void SPI##SpiX##_IRQ_Handler()									\
									{																\
										if (SPI_I2S_GetITStatus(SPI##SpiX, SPI_I2S_IT_RXNE) == SET)	\
										{															\
											::spi::Spi* spi = gpSpi_##SpiX;							\
									    	spi->_callback(*spi);									\
										}															\
									}


	SPI_IRQ_CALLBACK(1)
	SPI_IRQ_CALLBACK(2)

	static ::spi::Spi* gpSpi_NULL = nullptr;

	} /* namespace spi  */

} /* namespace stm32f1xx  */

namespace spi
{
	unsigned int	num_instance()
	{
		return 2;
	}

	void init_instance(unsigned int id, Configuration config /*= Configuration::_default()*/)
	{
		switch (id)
		{
			case 1: ::stm32f1xx::spi::gpSpi_1 = new stm32f1xx::spi::Stm32f1xx_Spi(1, config); break;
			case 2: ::stm32f1xx::spi::gpSpi_2 = new stm32f1xx::spi::Stm32f1xx_Spi(2, config); break;
		}
	}

	Spi& get_instance(unsigned int id)
	{
		switch (id)
		{
			case 1: return *::stm32f1xx::spi::gpSpi_1;
			case 2: return *::stm32f1xx::spi::gpSpi_2;
		}
		return *::stm32f1xx::spi::gpSpi_NULL;
	}
}

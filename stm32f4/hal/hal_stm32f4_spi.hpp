#pragma once

#include <spi.hpp>
#include <stm32f4xx_spi.h>



/* 
* Spi2: 
* Miso - pb14 
* Mosi - pb15 
* Sck - pb13 
* Nss - pb12 
* 
* Spi1: 
* Nss - pa4 
* Sck - pa5 
* Mosi - pa7 
* Miso - pa6 
* 
*/ 



namespace stm32f4
{

namespace spi
{

namespace {
	namespace sp = ::spi;
	inline static uint16_t conf_2_direction(sp::Configuration::Direction_t direction)
	{
		switch (direction)
		{
			case sp::Configuration::_2Lines_FullDuplex	:	return SPI_Direction_2Lines_FullDuplex; break;
			case sp::Configuration::_2Lines_RxOnly	:		return SPI_Direction_2Lines_RxOnly;		break;
			case sp::Configuration::_1Line_Rx	:			return SPI_Direction_1Line_Rx;			break;
			case sp::Configuration::_1Line_Tx	:			return SPI_Direction_1Line_Tx;			break;
		}

		return (uint16_t)-1;
	}

	inline static uint16_t	conf_2_mode(sp::Configuration::Mode_t mode)
	{
		switch (mode)
		{
			case sp::Configuration::Master:		return SPI_Mode_Master;
			case sp::Configuration::Slave:		return SPI_Mode_Slave;
		}

		return (uint16_t)-1;
	}

	// inline uint16_t	conf_2_DataSize(spi::Configuration::DataSize_t DataSize)
	// {
	// 	switch (DataSize)
	// 	{
	// 		case spi::Configuration::_8b:	return SPI_DataSize_8b;
	// 		case spi::Configuration::_16b:	return SPI_DataSize_16b;
	// 	}

	// 	return (uint16_t)-1;
	// }
	
	inline static uint16_t	conf_2_ClockPolarity(sp::Configuration::ClockPolarity_t clockPolarity)
	{
		switch (clockPolarity)
		{
			case sp::Configuration::Low:	return SPI_CPOL_Low;
			case sp::Configuration::High:	return SPI_CPOL_High;
		}

		return (uint16_t)-1;	
	}
	
	inline static uint16_t	conf_2_ClockPhase(sp::Configuration::ClockPhase_t clockPhase)
	{
		switch (clockPhase)
		{
			case sp::Configuration::_1_Edge:	return SPI_CPHA_1Edge;
			case sp::Configuration::_2_Edge:	return SPI_CPHA_2Edge;
		}

		return (uint16_t)-1;		
	}
	
	inline static uint16_t	conf_2_SlaveSelectManagement(sp::Configuration::SlaveSelectManagement_t slaveSelectManagement)
	{
		switch (slaveSelectManagement)
		{
			case sp::Configuration::Soft:		return SPI_NSS_Soft;
			case sp::Configuration::Hard:		return SPI_NSS_Hard;
		}	

		return (uint16_t)-1;	
	}
	
	inline static uint16_t	conf_2_BaudRatePrescaler(sp::Configuration::BaudRatePrescaler_t baudRatePrescaler)
	{
		switch (baudRatePrescaler)
		{
			case sp::Configuration::_2:			return SPI_BaudRatePrescaler_2;
			case sp::Configuration::_4:			return SPI_BaudRatePrescaler_4;
			case sp::Configuration::_8:			return SPI_BaudRatePrescaler_8;
			case sp::Configuration::_16:		return SPI_BaudRatePrescaler_16;
			case sp::Configuration::_32:		return SPI_BaudRatePrescaler_32;
			case sp::Configuration::_64:		return SPI_BaudRatePrescaler_64;
			case sp::Configuration::_128:		return SPI_BaudRatePrescaler_128;
			case sp::Configuration::_256:		return SPI_BaudRatePrescaler_256;
		}	

		return (uint16_t)-1;	
	}
	
	inline static uint16_t	conf_2_FirstBitTransmission(sp::Configuration::FirstBitTransmission_t firstBitTransmission)
	{
		switch (firstBitTransmission)
		{
			case sp::Configuration::MSB:		return SPI_FirstBit_MSB;
			case sp::Configuration::LSB:		return SPI_FirstBit_LSB;
		}	

		return (uint16_t)-1;	
	}
} // end namespace

	class Stm32f4_Spi : public ::spi::Spi
	{
	public:
		Stm32f4_Spi(unsigned int id, ::spi::Configuration config = ::spi::Configuration::_default()) :
							::spi::Spi(id)
		{
			//GPIO_InitTypeDef GPIO_InitStruct;
			SPI_InitTypeDef SPI_InitStruct;

			void 		(*pfvRCC_APBxPeriphClockCmd)(uint32_t, FunctionalState);
			uint32_t	  RCC_APBxPeriph_SPIx;



			// the gpio used
			GPIO_TypeDef* 	GPIOx;
			uint32_t		GPIO_Pin;			// the selected pin
			uint8_t			GPIO_AF;
			uint16_t		GPIO_Pin_Source1; 	// used for alternate function 
			uint16_t		GPIO_Pin_Source2; 	// used for alternate function 
			uint16_t		GPIO_Pin_Source3; 	// used for alternate function	

			switch (id)
			{
				case 1:
							_SPIx						= SPI1;
							GPIO_AF 					= GPIO_AF_SPI1;

							GPIOx						= GPIOA;
							GPIO_Pin					= GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
							GPIO_Pin_Source1			= GPIO_PinSource5;
							GPIO_Pin_Source2			= GPIO_PinSource6;
							GPIO_Pin_Source3			= GPIO_PinSource7;

							pfvRCC_APBxPeriphClockCmd	= RCC_APB2PeriphClockCmd;
							RCC_APBxPeriph_SPIx			= RCC_APB2Periph_SPI1;
							break;

				case 2:
							_SPIx						= SPI2;
							GPIO_AF 					= GPIO_AF_SPI2;

							GPIOx						= GPIOB;
							GPIO_Pin					= GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
							GPIO_Pin_Source1			= GPIO_PinSource13;
							GPIO_Pin_Source2			= GPIO_PinSource14;
							GPIO_Pin_Source3			= GPIO_PinSource15;

							pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
							RCC_APBxPeriph_SPIx			= RCC_APB1Periph_SPI2;
							break;

				case 3:
							_SPIx						= SPI3;
							GPIO_AF 					= GPIO_AF_SPI3;

							GPIOx						= GPIOA;
							GPIO_Pin					= GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
							GPIO_Pin_Source1			= GPIO_PinSource5;
							GPIO_Pin_Source2			= GPIO_PinSource6;
							GPIO_Pin_Source3			= GPIO_PinSource7;

							pfvRCC_APBxPeriphClockCmd	= RCC_APB1PeriphClockCmd;
							RCC_APBxPeriph_SPIx			= RCC_APB1Periph_SPI3;
							break;

				default:
							_SPIx						= nullptr;
							GPIO_AF 					= -1;
							GPIOx						= nullptr;
							GPIO_Pin					= -1;
							GPIO_Pin_Source1			= -1;
							GPIO_Pin_Source2			= -1;
							GPIO_Pin_Source3			= -1;

							pfvRCC_APBxPeriphClockCmd	= nullptr;
							RCC_APBxPeriph_SPIx			= -1;
							break;
			}

			/* configure pins used by SPIx
			 * PA5 = SCK
			 * PA6 = MISO
			 * PA7 = MOSI
			 */
			::stm32f4::gpio::configure_pin(GPIOx, GPIO_Pin, GPIO_PuPd_DOWN);
  			GPIO_PinAFConfig(GPIOx, GPIO_Pin_Source1, GPIO_AF); //
  			GPIO_PinAFConfig(GPIOx, GPIO_Pin_Source2, GPIO_AF);
  			GPIO_PinAFConfig(GPIOx, GPIO_Pin_Source3, GPIO_AF);
			
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

			case 3:	IRQn = SPI3_IRQn;
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
	static ::spi::Spi* gpSpi_3 = nullptr;


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
	SPI_IRQ_CALLBACK(3)

	static ::spi::Spi* gpSpi_NULL = nullptr;

	} /* namespace spi  */

} /* namespace stm32f4  */


namespace spi
{
	unsigned int	num_instance()
	{
		return 3;
	}

	void init_instance(unsigned int id, Configuration config /*= Configuration::_default()*/)
	{
		switch (id)
		{
			case 1: ::stm32f4::spi::gpSpi_1 = new stm32f4::spi::Stm32f4_Spi(1, config); break;
			case 2: ::stm32f4::spi::gpSpi_2 = new stm32f4::spi::Stm32f4_Spi(2, config); break;
			case 3: ::stm32f4::spi::gpSpi_3 = new stm32f4::spi::Stm32f4_Spi(3, config); break;
		}	
	}

	Spi& get_instance(unsigned int id)
	{
		switch (id)
		{
			case 1: return *::stm32f4::spi::gpSpi_1;
			case 2: return *::stm32f4::spi::gpSpi_2;
			case 3: return *::stm32f4::spi::gpSpi_3;
		}
		return *::stm32f4::spi::gpSpi_NULL;
	}
}




#include <stm32f0xx_spi.h>
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_misc.h>

#include <spi_conf.hpp>
#include <SpiInterface.hpp>

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STM32F0XX_SPI_MAX_COUNT								5

namespace stm32f0xx {

	namespace  spi {

		static ::spi::SpiInterface*		gpSpis[STM32F0XX_SPI_MAX_COUNT];

		Spi::Spi(unsigned int id, ::spi::SpiInterface::spi_callback_T callback, ::spi::Configuration config)
		{

			//assert params
			assert(id > 0);
			assert(id <= sizeof(gpSpis)/sizeof(::spi::SpiInterface*));

			// here perform the initialisation

			SPI_InitTypeDef			SPI_InitType;
			NVIC_InitTypeDef		NVIC_InitType; // this is used to configure the NVIC (nested vector interrupt controller)

			//save callback
			_callback = callback;

			// function used to enable the spi clock
			void 					(*pfvRCC_SPI_PeriphClockCmd)(uint32_t, FunctionalState);
			void 					(*pfvRCC_UART_PeriphClockCmd)(uint32_t, FunctionalState);
			GPIO_TypeDef*			GPIOId;
			uint32_t				RCC_Periph_SPIx;
			IRQn_Type				IRQn;


			// the gpio used
			GPIO_InitTypeDef 		GPIO_SPI;
			uint32_t	  			RCC_Periph_GPIOx;
			uint32_t				GPIO_Pin_Mosi, GPIO_Pin_Miso, GPIO_Pin_Sck, GPIO_Pin_Nss;			// the selected pin
			uint32_t				GPIO_PinSource_Mosi, GPIO_PinSource_Miso, GPIO_PinSource_Sck, GPIO_PinSource_Nss;			// the selected pin
			uint8_t					Gpio_AlternateFunction_Mosi,Gpio_AlternateFunction_Miso,Gpio_AlternateFunction_Sck,Gpio_AlternateFunction_Nss;

			//memset
			SPI_StructInit(&SPI_InitType);;
			GPIO_StructInit(&GPIO_SPI);


			gpSpis[id - 1] = this;

			switch (id)
			{
				case 1: 	
					_SPIId = SPI1;
					GPIOId = GPIOA;
					pfvRCC_SPI_PeriphClockCmd = RCC_APB2PeriphClockCmd; //SPI1
					RCC_Periph_SPIx = RCC_APB2Periph_SPI1;
					
					pfvRCC_UART_PeriphClockCmd = RCC_AHBPeriphClockCmd; //GPIOA
					RCC_Periph_GPIOx = RCC_AHBPeriph_GPIOA;
							
					/* MOSI Pin */
					GPIO_Pin_Mosi = GPIO_Pin_7;
					
					/* MISO Pin */
					GPIO_Pin_Miso = GPIO_Pin_6;
								
					/* SCK Pin */
					GPIO_Pin_Sck = GPIO_Pin_5;
										
					/* NSS Pin */
					GPIO_Pin_Nss = GPIO_Pin_4;

					/* ALternate configuration for MOSI Pin */
					GPIO_PinSource_Mosi = GPIO_PinSource7;
					Gpio_AlternateFunction_Mosi = GPIO_AF_0;

					/* ALternate configuration for MISO Pin */
					GPIO_PinSource_Miso = GPIO_PinSource6;
					Gpio_AlternateFunction_Miso = GPIO_AF_0;

					/* ALternate configuration for SCK Pin */
					GPIO_PinSource_Sck = GPIO_PinSource5;
					Gpio_AlternateFunction_Sck = GPIO_AF_0;
					
					/* ALternate configuration for NSS Pin */
					GPIO_PinSource_Nss = GPIO_PinSource4;
					Gpio_AlternateFunction_Nss = GPIO_AF_0;

					IRQn = SPI1_IRQn;
					
					break;

				default:	
					fprintf(stderr, "Unimplemented spi %i !\n", id);
					abort();
					break;
			} //switch spi id


			//enable clocks
			pfvRCC_SPI_PeriphClockCmd(RCC_Periph_SPIx, ENABLE);
			pfvRCC_UART_PeriphClockCmd(RCC_Periph_GPIOx, ENABLE);

			//configure pin alternate functions
			GPIO_PinAFConfig(GPIOId, GPIO_PinSource_Mosi, Gpio_AlternateFunction_Mosi);
			GPIO_PinAFConfig(GPIOId, GPIO_PinSource_Miso, Gpio_AlternateFunction_Miso);
			GPIO_PinAFConfig(GPIOId, GPIO_PinSource_Sck, Gpio_AlternateFunction_Sck);
			GPIO_PinAFConfig(GPIOId, GPIO_PinSource_Nss, Gpio_AlternateFunction_Nss);

			//configure GPIOs
			/* MOSI Pin */
			GPIO_StructInit(&GPIO_SPI);
			GPIO_SPI.GPIO_Pin = GPIO_Pin_Mosi;
			GPIO_SPI.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOId, &GPIO_SPI);

			/* MISO Pin */
			GPIO_StructInit(&GPIO_SPI);
			GPIO_SPI.GPIO_Pin = GPIO_Pin_Miso;
			GPIO_SPI.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOId, &GPIO_SPI);
			
			/* SCK Pin */
			GPIO_StructInit(&GPIO_SPI);
			GPIO_SPI.GPIO_Pin = GPIO_Pin_Sck;
			GPIO_SPI.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOId, &GPIO_SPI);
			
			/* NSS Pin */
			GPIO_StructInit(&GPIO_SPI);
			GPIO_SPI.GPIO_Pin = GPIO_Pin_Nss;
			GPIO_SPI.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOId, &GPIO_SPI);
	
			//configure SPI 1
			SPI_InitType.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
			SPI_InitType.SPI_Mode = SPI_Mode_Slave;
			SPI_InitType.SPI_DataSize = SPI_DataSize_8b;
			SPI_InitType.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitType.SPI_CPHA = SPI_CPHA_1Edge;

			SPI_Init(_SPIId, &SPI_InitType);

			//enable !
			SPI_Cmd(_SPIId, ENABLE);
			
			/*************** SPI INTERRUPT ****************/
			NVIC_InitType.NVIC_IRQChannel = IRQn;
			NVIC_InitType.NVIC_IRQChannelPriority = 0;
			NVIC_InitType.NVIC_IRQChannelCmd = ENABLE;

			NVIC_Init(&NVIC_InitType);
			
			SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

		}


		void Spi::send(const types::buffer& buf)
		{
			for (auto c : buf)
			{
					send(c);
			}

		}

		void Spi::send(const unsigned char* buf, unsigned int length)
		{
			unsigned int						i;
			
			for (i = 0; i < length; i++)
			{
				send(buf[i]);
			}
		}
		
		uint8_t Spi::send(uint8_t data)
		{
			while (SPI_I2S_GetFlagStatus(_SPIId, SPI_I2S_FLAG_TXE) == RESET);
			SPI_SendData8(_SPIId, data);
			return SPI_ReceiveData8(_SPIId);
		}

		#define USART_IRQ_CALLBACK(UsartX)	void USART##UsartX##_IRQHandler()									\
											{																	\
												gpSpis[UsartX - 1]->_callback(SPI_ReceiveData8(SPI##UsartX));					\
											}

		extern "C"
		{

			USART_IRQ_CALLBACK(1)
		}

	} /* namespace spi  */

} /* namespace stm32f0xx  */


namespace spi
{

	typedef ::stm32f0xx::spi::Spi ConcreteSpi;
} //namespace spi

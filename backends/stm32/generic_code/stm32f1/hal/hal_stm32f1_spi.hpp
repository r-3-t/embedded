#pragma once


#include <stm32f10x_spi.h>
#include <misc.h>
#include <SpiInterface.hpp>
#include <hal/stm32fx/spi_conf.hpp>


namespace stm32f1xx {

namespace  spi {

	class Spi : public ::spi::SpiInterface
	{
	public:
		Spi(unsigned int id, ::spi::Configuration config = ::spi::Configuration::_default());

		virtual uint8_t send(uint8_t data);

		virtual uint8_t recv();

		virtual void register_callback(void (*callback)(::spi::Spi&));

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

}

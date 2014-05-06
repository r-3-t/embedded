#pragma once


#include <stm32f0xx_spi.h>
#include <stm32f0xx_misc.h>
#include <SpiInterface.hpp>
#include <spi_conf.hpp>


namespace stm32f0xx
{

	namespace  spi
	{

		class Spi : public ::spi::SpiInterface
		{
		public:
			Spi(unsigned int id, spi_callback_T spi_callback, ::spi::Configuration config);

			virtual uint8_t send(uint8_t data);
			virtual void send(const types::buffer& buf);
			virtual void send(const unsigned char* buf, unsigned int length);

			virtual uint8_t recv();

		protected:
			SPI_TypeDef*			_SPIId;

		};

	} /* namespace spi  */

} /* namespace stm32f0xx  */

namespace spi
{

	typedef ::stm32f0xx::spi::Spi ConcreteSpi;
} //namespace spi

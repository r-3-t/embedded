#pragma once

#include <SpiInterface.hpp>
#include <spi_conf.hpp>
#include <hw_memmap.h>
#include <gpio.h>
#include <ssi.h>

namespace tix {

namespace  spi {

	using namespace tix::spi;

		class Spi : public ::spi::SpiInterface
		{
		public:

			Spi();
			Spi(unsigned int id, spi_callback_T spi_callback, ::spi::Configuration config);

			virtual uint8_t send(uint8_t data);;
			virtual uint8_t recv();;
			virtual void send(const types::buffer& buf);
			virtual void send(const unsigned char* buf, unsigned int length);

			unsigned long	  		SSI_Base;

			void		 			Configure();

		private:


			unsigned int			_id;
			::spi::Configuration	_config;
			bool					_configured;

		};


	} /* namespace spi  */

} /* namespace tix  */

namespace spi
{

	typedef ::tix::spi::Spi ConcreteSpi;

}

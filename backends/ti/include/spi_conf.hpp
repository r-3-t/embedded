#pragma once

#include <hw_types.h>
#include <ssi.h>

namespace tix
{

namespace spi
{

	namespace sp = ::spi;
	inline static unsigned long	conf_2_mode(sp::Configuration::Mode_t mode)
	{
		switch (mode)
		{
			case sp::Configuration::Master:		return SSI_MODE_MASTER;
			case sp::Configuration::Slave:		return SSI_MODE_SLAVE;
		}

		return (unsigned long)-1;
	}


	inline static unsigned long	conf_2_ClockPolarity(sp::Configuration::ClockPolarity_t clockPolarity)
	{
		switch (clockPolarity)
		{
			case sp::Configuration::Low:	return 0;
			case sp::Configuration::High:	return 1;
		}

		return (unsigned long)-1;
	}

	inline static unsigned long	conf_2_ClockPhase(sp::Configuration::ClockPhase_t clockPhase)
	{
		switch (clockPhase)
		{
			case sp::Configuration::_1_Edge:	return 0;
			case sp::Configuration::_2_Edge:	return 1;
		}

		return (unsigned long)-1;
	}


} // end namespace spi

} // end namespace tix


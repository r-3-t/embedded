#include <hw_types.h>
#include <types.hpp>
#include <lm4f120h5qr.h>
#include <sysctl.h>

uint32_t gTickFactor;

struct AutoInitSysTick
{
	AutoInitSysTick()
	{
	    gTickFactor = SysCtlClockGet() / 1000000;

	}
};

AutoInitSysTick gAutoInitSysTick;

namespace clock
{

	uint32_t getTickCount()
	{
		return NVIC_ST_CURRENT_R;
	}

	void usleep(unsigned int nTime)
	{
		//WARN : max counter value is 0xFFFFFF !!!
		//TODO: maybe we should decrement (nTime * gTickFactor) ?

		uint32_t start_TickCount = getTickCount();

		while( (start_TickCount - getTickCount()) <  (nTime * gTickFactor));
	}

	void msleep(unsigned int nTime)
	{
		unsigned int		i;

		//TODO: use another timer and prescale to ms.
		for (i = 0; i < nTime; i++)
		{
			usleep(1000);
		}
	}

	unsigned int getTickPerMs()
	{
		return gTickFactor * 1000;
	}

}


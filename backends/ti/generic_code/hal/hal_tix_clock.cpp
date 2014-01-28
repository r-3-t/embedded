#include <hw_types.h>
#include <types.hpp>
#include <lm4f120h5qr.h>
#include <sysctl.h>
#include <systick.h>
#include <interrupt.h>

uint32_t guTickFactor;
uint32_t gmTickFactor;

struct AutoInitSysTick
{
	AutoInitSysTick()
	{
	    //
	    // Set the clocking to run directly from the PLL at 80 MHz
	    //
	    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
	                               SYSCTL_OSC_MAIN);

	    //we set a period with to max representation of uint16_t
	    SysTickPeriodSet(0x0000FFFF + 1);

	    //enable systick counter
	    SysTickEnable();

	    guTickFactor = SysCtlClockGet() / 1000000;
	    gmTickFactor = SysCtlClockGet() / 1000;

		//
		// Enable global interrupts
		//
		IntMasterEnable();

	}
};

AutoInitSysTick gAutoInitSysTick;

namespace clock
{

	uint32_t getTickCount()
	{
		return NVIC_ST_CURRENT_R;
	}

	void decrease_ticks(uint32_t nbTicks)
	{
		uint16_t PreviousTickCounter = getTickCount();
		uint16_t CurrentTickCounter;

		//ticks count in one iteration
		uint16_t elapseTicks = 0;

		while( nbTicks > elapseTicks)
		{
			//decrease total ticks counter
			nbTicks -= elapseTicks;

			//calculate nb ticks between now and previous iteration
			CurrentTickCounter = getTickCount();
			elapseTicks = PreviousTickCounter - CurrentTickCounter;
			PreviousTickCounter = CurrentTickCounter;

		}
	}

	void usleep(unsigned int nTime)
	{
		//ticks count for the requested time
		decrease_ticks(nTime * guTickFactor);
	}

	void msleep(unsigned int nTime)
	{
		//ticks count for the requested time
		decrease_ticks(nTime * gmTickFactor);
	}

	unsigned int getTickPerMs()
	{
		return gmTickFactor;
	}

	unsigned int getTickPerUs()
	{
		return guTickFactor;
	}

}


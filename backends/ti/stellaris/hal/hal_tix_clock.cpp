#include <hw_types.h>
#include <types.hpp>
#undef GPIO_LOCK_KEY
#include <lm4f120h5qr.h>
#include <sysctl.h>
#include <systick.h>
#include <interrupt.h>

uint32_t guTickFactor;
uint32_t gmTickFactor;

extern "C"
{
	void InitClock()
	{
		//
		// Set the clocking to run directly from the PLL at 80 MHz
		//
		SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
								   SYSCTL_OSC_MAIN);

		//we set a period to its max representation (24 bits)
		SysTickPeriodSet(0x00FFFFFF + 1);

		//enable systick counter
		SysTickEnable();

		guTickFactor = SysCtlClockGet() / 1000000;
		gmTickFactor = SysCtlClockGet() / 1000;

		//
		// Enable global interrupts
		//
		IntMasterEnable();

	}
}

namespace clock
{

	uint32_t getTickCount()
	{
		return (NVIC_ST_CURRENT_R & 0xFFFFFF);
	}

	void decrease_ticks(uint32_t nbTicks)
	{
		uint32_t PreviousTickCounter = getTickCount();
		uint32_t CurrentTickCounter;

		//ticks count in one iteration
		uint32_t elapseTicks = 0;

		while( nbTicks > elapseTicks)
		{
			//decrease total ticks counter
			nbTicks -= elapseTicks;

			//calculate nb ticks between now and previous iteration
			CurrentTickCounter = getTickCount();
			if (CurrentTickCounter > PreviousTickCounter)
			{
				elapseTicks = 0xFFFFFF - (CurrentTickCounter - PreviousTickCounter);
			}
			else
			{
				elapseTicks = PreviousTickCounter - CurrentTickCounter;
			}
			PreviousTickCounter = CurrentTickCounter;

		}
	}
	
	uint32_t elapsedMicros(uint32_t PreviousTickCounter)
	{
		uint32_t CurrentTickCounter = getTickCount();
		uint32_t elapseTicks;
		
		if (CurrentTickCounter > PreviousTickCounter)
		{
			elapseTicks = 0xFFFFFF - (CurrentTickCounter - PreviousTickCounter);
		}
		else
		{
			elapseTicks = PreviousTickCounter - CurrentTickCounter;
		}
		
		return (elapseTicks/guTickFactor);
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


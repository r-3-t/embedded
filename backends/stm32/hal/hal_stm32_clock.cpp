#include "hal_stm32.hpp"

uint32_t guTickFactor;
uint32_t gmTickFactor;

struct AutoInitSysTick
{
	AutoInitSysTick()
	{
		//update SystemCoreClock to the right frequency
		SystemCoreClockUpdate();

		//set ms and us factor
	    guTickFactor = SystemCoreClock / 1000000;
	    gmTickFactor = SystemCoreClock / 1000;

	    //enable systick
	    SysTick->LOAD = 0x00ffffff;
	    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; //processor clock

	}
};

AutoInitSysTick gAutoInitSysTick;

namespace clock
{

	uint32_t getTickCount()
	{
		return SysTick->VAL;
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

			//calculate ticks count between now and previous iteration
			CurrentTickCounter = getTickCount();
			elapseTicks = PreviousTickCounter - CurrentTickCounter;
			PreviousTickCounter = CurrentTickCounter;

		}
	}

	uint32_t elapsedMicros(unsigned int PreviousTickCounter)
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


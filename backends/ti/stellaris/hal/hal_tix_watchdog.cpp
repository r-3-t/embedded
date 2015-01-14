#include "hal_tix_watchdog.hpp"

#include <watchdog.h>
#include <hw_watchdog.h>

#include <ClockInterface.hpp>

#include <stdio.h>
#include <stdlib.h>

namespace tix
{
	namespace watchdog
	{

	unsigned long get_watchdogtimer_base_from_id(::watchdog::Watchdog_Id Watchdog_Id)
	{
		switch (Watchdog_Id)
		{
		case 1:
			return WATCHDOG0_BASE;
			break;
		case 2:
			return WATCHDOG1_BASE;
			break;


		}

		fprintf(stderr, "Invalid Timer_Id : %i !\n", Watchdog_Id);
		abort();
	}

	unsigned long get_watchdogtimer_clock_from_id(::watchdog::Watchdog_Id Watchdog_Id)
	{
		switch (Watchdog_Id)
		{
		case 1:
			return SYSCTL_PERIPH_WDOG0;
			break;
		case 2:
			return SYSCTL_PERIPH_WDOG1;
			break;
		}

		fprintf(stderr, "Invalid WatchdogTimer_Id : %i !\n", Watchdog_Id);
		abort();
	}

	Watchdog::Watchdog(::watchdog::Watchdog_Id Watchdog_Id)
	{
		this->_Watchdog_Id = Watchdog_Id;
		this->_configured = false;
		this->_Watchdog_Base = get_watchdogtimer_base_from_id(Watchdog_Id);

	}

	void Watchdog::configure()
	{
		if (this->_configured == true)
		{
			return;
		}
		this->_configured = true;

		SysCtlPeripheralEnable(get_watchdogtimer_clock_from_id(this->_Watchdog_Id));

		//enable cpu reset when watchdog is not updated in time
		WatchdogResetEnable(this->_Watchdog_Base);

	}

	void Watchdog::setPeriodMs(uint32_t PeriodMs)
	{
		this->configure();

		WatchdogUnlock(this->_Watchdog_Base);

		//TODO: Prevent overflow !
		WatchdogReloadSet(this->_Watchdog_Base, PeriodMs * ::clock::getTickPerMs());

		WatchdogLock(this->_Watchdog_Base);

	}

	void Watchdog::update()
	{
		this->configure();

		WatchdogIntClear(this->_Watchdog_Base);

	}

	void Watchdog::enable()
	{
		this->configure();

		WatchdogUnlock(this->_Watchdog_Base);

		WatchdogEnable(this->_Watchdog_Base);

		WatchdogLock(this->_Watchdog_Base);
	}

	bool Watchdog::trigerred()
	{
		this->configure();

		if ( (SysCtlResetCauseGet() & SYSCTL_CAUSE_WDOG) == SYSCTL_CAUSE_WDOG)
		{
			return true;
		}
		return false;
	}



	} //namespace watchdog
} // namespace tix



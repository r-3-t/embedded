#pragma once

namespace watchdog
{
	typedef uint32_t		Watchdog_Id;

	class WatchdogInterface
	{
	public:
		WatchdogInterface() {};
		WatchdogInterface(::watchdog::Watchdog_Id Watchdog_Id) {};

		virtual void setPeriodMs(uint32_t PeriodMs) = 0;
		virtual void update() = 0;
		virtual bool trigerred() = 0;
		virtual void enable() = 0;

	private:


	};
}

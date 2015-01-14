#pragma once

#include <WatchdogInterface.hpp>

namespace tix
{

	namespace watchdog
	{

		class Watchdog: public ::watchdog::WatchdogInterface
		{
		public:
			Watchdog(::watchdog::Watchdog_Id Watchdog_Id);

			void setPeriodMs(uint32_t PeriodMs);
			void update();
			bool trigerred();
			void enable();

		private:
			void 						configure();
			bool						_configured;
			::watchdog::Watchdog_Id		_Watchdog_Id;
			unsigned long				_Watchdog_Base;

		};

	} //namespace watchdog
} //namespace tix

namespace watchdog
{

	typedef ::tix::watchdog::Watchdog						ConcreteWatchdog;

}//namespace watchdog


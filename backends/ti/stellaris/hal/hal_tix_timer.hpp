#pragma once

#include <timer.h>

#include <TimerInterface.hpp>

namespace tix {

	namespace timer
	{

		class Timer : public ::timer::TimerInterface
		{
		public:
			Timer(::timer::Timer_Id TimerId, ::timer::SubdivisionDelay_T Delay, uint16_t Period, ::timer::callback_T callback);

			void clear();

			bool triggered();

			void enable();

			void disable();

			void setPeriod(uint16_t Period);

			void configure();

			::timer::callback_T 			_callback;

		private:
			bool							_configured;
			::timer::SubdivisionDelay_T 	_SubdivisionDelay;
			unsigned long					_TimerBase;
			::timer::Timer_Id 				_TimerId;
			uint16_t						_Period;

		};

	} //namespace timer

} //namespace tix

namespace timer
{

	typedef ::tix::timer::Timer						ConcreteTimer;

}//namespace timer



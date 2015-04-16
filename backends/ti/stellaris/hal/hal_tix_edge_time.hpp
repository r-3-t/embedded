#pragma once

#include <PinoutInterface.hpp>
#include <TimerInterface.hpp>
#include <EdgeTimeInterface.hpp>
#include <Priority.hpp>

namespace tix {

	namespace edge_time
	{

		class EdgeTime : public ::edge_time::EdgeTimeInterface
		{
		public:
			EdgeTime(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId, ::timer::callback_T callback, Priority_T priority = INTERRUPT_PRIORITY(1));

			void configure();
			void clear();

			void enable();
			void disable();

			uint32_t 		get_last_record();

			void 			_save_ticks();

			uint32_t 						_ticks_record;

			::timer::callback_T 			_callback;

		private:
			uint32_t 						_get_ticks();

			unsigned long					_GPIOId;
			unsigned long					_PINId;

			Priority_T						_Priority;

			unsigned long					_TimerBase;
			unsigned long					_TimerConfig;

			bool							_configured;

		};

	}//namespace edge_time

}//namespace tix

namespace edge_time
{

	typedef ::tix::edge_time::EdgeTime						ConcreteEdgeTime;

}//namespace edge_time

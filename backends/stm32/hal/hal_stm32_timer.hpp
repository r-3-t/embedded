#pragma once

#include "hal_stm32.hpp"

#include <TimerInterface.hpp>

namespace stm32 {

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


		private:
			GPIO_TypeDef* 					_GPIOx;
			uint16_t						_Gpio_Pin;
			TIM_TypeDef*					_Timer;
			uint16_t						_Channel;
			::timer::SubdivisionDelay_T 	_Delay;

		};

	} //namespace timer

} //namespace stm32

namespace timer
{

	typedef ::stm32::timer::Timer						ConcreteTimer;

}//namespace timer



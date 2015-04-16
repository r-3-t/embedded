#pragma once

#include <PwmInterface.hpp>
#include <PinoutInterface.hpp>

#include "hal_tix_timer.hpp"

namespace tix {

	namespace pwm
	{

		class Pwm : public ::pwm::PwmInterface
		{
		public:
			Pwm(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId, uint32_t Frequency, uint32_t MaxDuty);

			virtual void setDuty(uint32_t Duty);
			virtual void configure();
			virtual void enable();
			virtual void disable();

		private:
			uint32_t					 	_Frequency;
			uint32_t					 	_MaxDuty;
			unsigned long					_TimerBase;
			unsigned long					_PeriodUs;
			unsigned long 					_PwmConfig;
			unsigned long					_TimerConfig;
			//uint16_t						_Channel;
			bool							_configured;
			unsigned long					_prescalerFactor;
			unsigned long					_TimeByTickPrescaleNs;
			unsigned long 					_TickCountForFrequency;
			unsigned long					_GPIOId;
			unsigned long					_PINId;

			unsigned long 					_Current_duty;

		};


	} //namespace pwm

} //namespace stm32

namespace pwm
{

	typedef ::tix::pwm::Pwm		ConcretePwm;

}//namespace pwm

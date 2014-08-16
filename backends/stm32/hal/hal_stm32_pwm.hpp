#pragma once

#include "hal_stm32.hpp"

#include <PwmInterface.hpp>
#include <PinoutInterface.hpp>

namespace stm32 {

	namespace pwm
	{

		class Pwm : public ::pwm::PwmInterface
		{
		public:
			Pwm(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId, uint32_t Frequency, uint32_t MaxDuty);

			virtual void setDuty(uint32_t Duty);

		private:
			GPIO_TypeDef* 					_GPIOx;
			uint16_t						_Gpio_Pin;
			uint32_t					 	_Frequency;
			uint32_t					 	_MaxDuty;
			TIM_TypeDef*					_Timer;
			uint16_t						_Channel;

		};


	} //namespace pwm

} //namespace stm32

namespace pwm
{

	typedef ::stm32::pwm::Pwm		ConcretePwm;

}//namespace pwm



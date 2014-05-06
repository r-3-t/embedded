#pragma once

#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <misc.h>

#include <PwmInterface.hpp>
#include <PinoutInterface.hpp>

namespace stm32f1xx {

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

} //namespace stm32f1xx

namespace pwm
{

	typedef ::stm32f1xx::pwm::Pwm		ConcretePwm;

}//namespace pwm



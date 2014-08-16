#pragma once

#include "hal_stm32.hpp"

#include <PinoutInterface.hpp>
#include <ExtintInterface.hpp>

namespace stm32 {

	namespace extint
	{

		class Extint : public ::extint::ExtintInterface
		{
		public:

			Extint() {}
			Extint(::pinout::Pin_id PINId, ::pinout::Gpio_id 	GPIOId, ::extint::InterruptTrigger_T Mode, ::extint::callback_T callback);

			void clear();
			bool triggered();
			bool is_high();
			void disable();
			void enable();


		private:
			EXTI_InitTypeDef 								_EXTIx;
			uint32_t										_EXTI_Line;
			GPIO_TypeDef* 									_GPIOx;
			uint16_t										_Gpio_Pin;
			::extint::InterruptTrigger_T 					_Mode;

		};

	} //namespace extint

} //namespace stm32

namespace extint
{

	typedef ::stm32::extint::Extint						ConcreteExtint;

}//namespace extint


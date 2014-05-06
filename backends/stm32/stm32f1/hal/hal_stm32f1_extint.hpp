#pragma once

#include <stm32f10x_exti.h>
#include <stm32f10x_rcc.h>
#include <misc.h>

#include <PinoutInterface.hpp>
#include <ExtintInterface.hpp>

namespace stm32f1xx {

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

} //namespace stm32f1xx

namespace extint
{

	typedef ::stm32f1xx::extint::Extint						ConcreteExtint;

}//namespace extint


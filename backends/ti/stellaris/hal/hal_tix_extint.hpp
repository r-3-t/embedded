#pragma once

#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>

#include <ExtintInterface.hpp>
#include <PinoutInterface.hpp>
#include <Priority.hpp>

namespace tix
{

	namespace extint
	{
		
		class Extint: public ::extint::ExtintInterface
		{
		public:

			Extint() {}
			Extint(::pinout::Pin_id PINId, ::pinout::Gpio_id 	GPIOId, ::extint::InterruptTrigger_T Mode, ::extint::callback_T callback, Priority_T priority = INTERRUPT_PRIORITY(0));

			void clear();
			bool triggered();
			bool is_high();
			void disable();
			void enable();
			void set_callback(::extint::callback_T callback);
			void set_mode(::extint::InterruptTrigger_T Mode);

		private:
			void		 			Configure();

			unsigned long 			GpioPortBase;
			unsigned long			GpioPin;
		};

	} /* namespace extint  */

} /* namespace tix  */

namespace extint
{

	typedef ::tix::extint::Extint						ConcreteExtint;

}//namespace extint

#pragma once

#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>

#include <ExtintInterface.hpp>
#include <PinoutInterface.hpp>

namespace tix
{

	namespace extint
	{
		
		class Extint: public ::extint::ExtintInterface
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

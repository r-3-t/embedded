#include <arduino_gpio.hpp>
#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>
#include <GpioInterface.hpp>
#include <ExtintInterface.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO: must be placed in mapping file
#define DEFAULT_GPIO_OUTPUT_PORT					1
#define DEFAULT_GPIO_INPUT_PORT						2
#define DEFAULT_EXINT_PIN							0

namespace arduino
{
	namespace gpio
	{
		extern "C"
		{
		void pinInterruptHandler();
		}
	}
}

::extint::ConcreteExtint Eint0(0, DEFAULT_GPIO_INPUT_PORT, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler);
::extint::ConcreteExtint Eint1(1, DEFAULT_GPIO_INPUT_PORT, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler);
::extint::ConcreteExtint Eint2(2, DEFAULT_GPIO_INPUT_PORT, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler);
::extint::ConcreteExtint Eint3(3, DEFAULT_GPIO_INPUT_PORT, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler);

namespace arduino
{
	namespace gpio
	{
		/*int modes[1];
		::extint::callback_T callbacks[1];
		 */
		extern "C"
		{
		void pinInterruptHandler()
		{
			fprintf(stderr, "Invalid interrupt, external interrupt is not configured ! !\n");
			abort();
		}
		}

		void pinMode(::pinout::Pin_id pin, int Pin_Mode)
		{
			switch (Pin_Mode)
			{
			case OUTPUT:
				::gpio::configure_gpio_pin(DEFAULT_GPIO_OUTPUT_PORT, pin);
				break;
			case INPUT:
				::gpio::configure_input_pin(DEFAULT_GPIO_INPUT_PORT, pin);
				break;
			default:
				//unsupported
				break;
			}

		}

		void digitalWrite(::pinout::Pin_id pin, int Pin_State)
		{
			switch (Pin_State)
			{
			case HIGH:
				::gpio::set_pin(DEFAULT_GPIO_OUTPUT_PORT, pin);
				break;
			case LOW:
				::gpio::reset_pin(DEFAULT_GPIO_OUTPUT_PORT, pin);
				break;
			}
		}

		int digitalRead(::pinout::Pin_id pin)
		{
			if (::gpio::is_pin_high(DEFAULT_GPIO_INPUT_PORT, pin) == true)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		::extint::ExtintInterface* get_exint(::pinout::Pin_id pin)
		{
			::extint::ConcreteExtint* pEint;

			switch (pin)
			{
			case 0:
				pEint = &Eint0;
				break;
			case 1:
				pEint = &Eint1;
				break;
			case 2:
				pEint = &Eint2;
				break;
			case 3:
				pEint = &Eint3;
				break;
			default:
				fprintf(stderr, "Invalid pin id !\n");
				abort();
				break;
			}

			return pEint;
		}

		void attachInterrupt(::pinout::Pin_id pin, ::extint::callback_T cb, int mode)
		{
			::extint::InterruptTrigger_T Mode;
			::extint::ExtintInterface* pEint;

			switch (mode)
			{
			case RISING:
				Mode = ::extint::RisingTrigger;
				break;
			case FALLING:
				Mode = ::extint::FallingTrigger;
				break;
			case CHANGE:
				Mode = ::extint::RisingFallingTrigger;
				break;
			default:
				fprintf(stderr, "Invalid mode !\n");
				abort();
				break;
			}

			pEint = get_exint(pin);

			pEint->set_callback(cb);
			pEint->set_mode(Mode);
			pEint->enable();
		}

		void detachInterrupt(::pinout::Pin_id pin)
		{
			get_exint(pin)->disable();
		}

	}
}

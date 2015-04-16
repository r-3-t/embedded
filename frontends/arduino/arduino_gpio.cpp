#include <arduino_gpio.hpp>
#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>
#include <GpioInterface.hpp>
#include <ExtintInterface.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

//::extint::ConcreteExtint Eint0(nullptr, nullptr, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler, INTERRUPT_PRIORITY(2));
/*::extint::ConcreteExtint Eint1(1, DEFAULT_GPIO_INPUT_PORT, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler, INTERRUPT_PRIORITY(2));
::extint::ConcreteExtint Eint2(2, DEFAULT_GPIO_INPUT_PORT, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler, INTERRUPT_PRIORITY(2));
::extint::ConcreteExtint Eint3(3, DEFAULT_GPIO_INPUT_PORT, ::extint::RisingFallingTrigger, &::arduino::gpio::pinInterruptHandler, INTERRUPT_PRIORITY(2));
*/
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

		unsigned int get_port_from_gpio_pin_id(::pinout::Gpio_Pin_id GpioPin)
		{
			return (GpioPin >> 16) & 0xFFFF;
		}

		unsigned int get_pin_from_gpio_pin_id(::pinout::Gpio_Pin_id GpioPin)
		{
			return (GpioPin) & 0xFFFF;
		}

		void pinMode(::pinout::Gpio_Pin_id GpioPin, int Pin_Mode)
		{
			switch (Pin_Mode)
			{
			case OUTPUT:
				::gpio::configure_gpio_pin(get_port_from_gpio_pin_id(GpioPin), get_pin_from_gpio_pin_id(GpioPin));
				break;
			case INPUT:
				::gpio::configure_input_pin(get_port_from_gpio_pin_id(GpioPin), get_pin_from_gpio_pin_id(GpioPin));
				break;
			default:
				//unsupported
				break;
			}

		}

		void digitalWrite(::pinout::Gpio_Pin_id GpioPin, int Pin_State)
		{
			switch (Pin_State)
			{
			case HIGH:
				::gpio::set_pin(get_port_from_gpio_pin_id(GpioPin), get_pin_from_gpio_pin_id(GpioPin));
				break;
			case LOW:
				::gpio::reset_pin(get_port_from_gpio_pin_id(GpioPin), get_pin_from_gpio_pin_id(GpioPin));
				break;
			}
		}

		int digitalRead(::pinout::Gpio_Pin_id GpioPin)
		{
			if (::gpio::is_pin_high(get_port_from_gpio_pin_id(GpioPin), get_pin_from_gpio_pin_id(GpioPin)) == true)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		::extint::ExtintInterface* get_exint(::pinout::Gpio_Pin_id pin)
		{
			::extint::ConcreteExtint* pEint;

			switch (pin)
			{
			/*case 0:
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
				break;*/
			default:
				fprintf(stderr, "Invalid pin id !\n");
				abort();
				break;
			}

			return pEint;
		}

		void attachInterrupt(::pinout::Gpio_Pin_id pin, ::extint::callback_T cb, int mode)
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

		void detachInterrupt(::pinout::Gpio_Pin_id pin)
		{
			get_exint(pin)->disable();
		}

	}
}

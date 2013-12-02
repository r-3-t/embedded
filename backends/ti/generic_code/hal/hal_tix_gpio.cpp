#include <hw_types.h>
#include <gpio.h>
#include <hw_gpio.h>
#include <hw_memmap.h>
#include <sysctl.h>

#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>
#include <hal/Gpio.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

namespace tix
{
	namespace gpio
	{
		unsigned long get_GPIO_port_from_id(::pinout::Gpio_id 	GPIOId)
		{

			switch (GPIOId)
			{
			case 1:
				//GPIOA
				return GPIO_PORTA_BASE;
				break;
			case 2:
				//GPIOB
				return GPIO_PORTB_BASE;
				break;
			case 3:
				//GPIOC
				return GPIO_PORTC_BASE;
				break;
			case 4:
				//GPIOD
				return GPIO_PORTD_BASE;
				break;
			case 5:
				//GPIOE
				return GPIO_PORTE_BASE;
				break;
			case 6:
				//GPIOF
				return GPIO_PORTF_BASE;
				break;
			case 7:
				//GPIOG
				return GPIO_PORTG_BASE;
				break;
			case 8:
				//GPIOH
				return GPIO_PORTH_BASE;
				break;
			}

			fprintf(stderr, "Invalid GPIO port : %i !\n", GPIOId);
			abort();
		}

		unsigned long get_GPIO_pin_from_id(::pinout::Pin_id PINId)
		{

			assert(PINId < TIX_PIN_MAX_COUNT);

			return (1 << PINId);
		}

		void enable_port_clock(unsigned long ulPort)
		{
			switch (ulPort)
			{
			case GPIO_PORTA_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
				break;
			case GPIO_PORTB_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
				break;
			case GPIO_PORTC_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
				break;
			case GPIO_PORTD_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
				break;
			case GPIO_PORTE_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
				break;
			case GPIO_PORTF_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
				break;
			case GPIO_PORTG_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
				break;
			case GPIO_PORTH_BASE:
				SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
				break;
			}

			fprintf(stderr, "Invalid GPIO : %lx !\n", ulPort);
			abort();

		}

		void configure_gpio_pin(unsigned long ulPort, unsigned char ucPins)
		{
			enable_port_clock(ulPort);
			GPIOPinTypeGPIOOutput(ulPort, ucPins);

		}

		void set_pin(unsigned long ulPort, unsigned char ucPins)
		{
			GPIOPinWrite(ulPort, ucPins, ucPins);
		}

		void reset_pin(unsigned long ulPort, unsigned char ucPins)
		{
			GPIOPinWrite(ulPort, ucPins, 0);
		}

	}
}



namespace gpio
{

	void configure_gpio_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		unsigned long ulPort;

		ulPort = ::tix::gpio::get_GPIO_port_from_id(GPIOId);

		::tix::gpio::configure_gpio_pin(ulPort, ::tix::gpio::get_GPIO_pin_from_id(PINId));
	}

	void set_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		unsigned long ulPort;

		ulPort = ::tix::gpio::get_GPIO_port_from_id(GPIOId);

		::tix::gpio::set_pin(ulPort, ::tix::gpio::get_GPIO_pin_from_id(PINId));
	}

	void reset_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		unsigned long ulPort;

		ulPort = ::tix::gpio::get_GPIO_port_from_id(GPIOId);

		::tix::gpio::reset_pin(ulPort, ::tix::gpio::get_GPIO_pin_from_id(PINId));
	}

} //namespace gpio

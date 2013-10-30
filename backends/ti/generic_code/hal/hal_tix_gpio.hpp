#pragma once

#include <hw_types.h>
#include <gpio.h>
#include <hw_gpio.h>
#include <hw_memmap.h>
#include <sysctl.h>
#include <gpio.hpp>
#include <pinout.hpp>


namespace tix
{
	namespace gpio
	{

		inline void enable_port_clock(unsigned long ulPort)
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
			default:
				break;
			}

		}

		inline void configure_gpio_pin(unsigned long ulPort, unsigned char ucPins)
		{
			enable_port_clock(ulPort);
			GPIOPinTypeGPIOOutput(ulPort, ucPins);

		}

		inline void set_pin(unsigned long ulPort, unsigned char ucPins)
		{
			GPIOPinWrite(ulPort, ucPins, ucPins);
		}

		inline void reset_pin(unsigned long ulPort, unsigned char ucPins)
		{
			GPIOPinWrite(ulPort, ucPins, 0);
		}

	}
}



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
		default:
			return 0;
			break;
		}
	}

	unsigned long get_GPIO_pin_from_id(::pinout::Pin_id PINId)
	{

		return (1 << PINId);
	}

	void configure_gpio_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		unsigned long ulPort;

		ulPort = get_GPIO_port_from_id(GPIOId);

		//TODO: error management when no GPIO port exists
		if (ulPort == 0)
		{
			return;
		}

		::tix::gpio::configure_gpio_pin(ulPort, get_GPIO_pin_from_id(PINId));
	}

	void set_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		unsigned long ulPort;

		ulPort = get_GPIO_port_from_id(GPIOId);

		//TODO: error management when no GPIO port exists
		if (ulPort == 0)
		{
			return;
		}

		::tix::gpio::set_pin(ulPort, get_GPIO_pin_from_id(PINId));
	}

	void reset_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		unsigned long ulPort;

		ulPort = get_GPIO_port_from_id(GPIOId);

		//TODO: error management when no GPIO port exists
		if (ulPort == 0)
		{
			return;
		}

		::tix::gpio::reset_pin(ulPort, get_GPIO_pin_from_id(PINId));
	}

	class GPIO : public ::gpio::PinOut
	{
	public:
		GPIO(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
		{

			_ucPins = 1 << PINId;

			_ulPort = get_GPIO_port_from_id(GPIOId);

			//TODO: error management when no GPIO port exists
			if (_ulPort == 0)
			{
				return;
			}

			::tix::gpio::configure_gpio_pin(_ulPort, _ucPins);
		}


		virtual void high()
		{
			::tix::gpio::set_pin(_ulPort, _ucPins);
		}

		virtual void low()
		{
			::tix::gpio::reset_pin(_ulPort, _ucPins);
		}

	private:
		unsigned long 	_ulPort;
		unsigned char	_ucPins;
	};

} //namespace gpio

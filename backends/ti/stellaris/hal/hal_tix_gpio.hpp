#pragma once

#include <hw_types.h>
#include <gpio.h>
#include <hw_gpio.h>
#include <hw_memmap.h>
#include <sysctl.h>
#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>

#define TIX_PIN_MAX_COUNT							8

namespace tix
{
	namespace gpio
	{

		unsigned long get_GPIO_port_from_id(::pinout::Gpio_id 	GPIOId);
		unsigned long get_GPIO_pin_from_id(::pinout::Pin_id PINId);
		void configure_gpio_pin(unsigned long ulPort, unsigned char ucPins);
		void configure_extint_pin(unsigned long ulPort, unsigned char ucPins);
		void set_pin(unsigned long ulPort, unsigned char ucPins);
		void reset_pin(unsigned long ulPort, unsigned char ucPins);
		bool is_pin_high(unsigned long ulPort, unsigned char ucPins);

	}
}



namespace gpio
{




} //namespace gpio

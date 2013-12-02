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

	}
}



namespace gpio
{

	void configure_gpio_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	void set_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	void reset_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);


} //namespace gpio

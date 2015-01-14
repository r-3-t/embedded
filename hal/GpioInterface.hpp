#pragma once

#include <PinoutInterface.hpp>

namespace gpio {

	void configure_gpio_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	void set_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	void reset_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	bool is_pin_high(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	void configure_input_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);

}



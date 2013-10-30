#pragma once

#include <pinout.hpp>

namespace gpio {


	class PinOut
	{
	public:
		PinOut() {}

		virtual void high() = 0;
		virtual void low() = 0;
	};

	void configure_gpio_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	void set_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);
	void reset_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId);

}



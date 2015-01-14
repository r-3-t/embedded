#pragma once

#include <PinoutInterface.hpp>
#include <ExtintInterface.hpp>

#define INPUT 				0
#define OUTPUT 				1
#define INPUT_PULLUP 		2

#define LOW					0
#define HIGH				1

#define FALLING				0
#define RISING				1
#define CHANGE				2

namespace arduino
{
	namespace gpio
	{

		void pinMode(::pinout::Pin_id pin, int Pin_Mode);
		void digitalWrite(::pinout::Pin_id pin, int Pin_State);
		int digitalRead(::pinout::Pin_id pin);
		void attachInterrupt(::pinout::Pin_id pin, ::extint::callback_T cb, int mode);
		void detachInterrupt(::pinout::Pin_id pin);
		::extint::ExtintInterface* get_exint(::pinout::Pin_id pin);

	}
}

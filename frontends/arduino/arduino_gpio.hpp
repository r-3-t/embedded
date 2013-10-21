#pragma once

#define INPUT 				0
#define OUTPUT 				1
#define INPUT_PULLUP 		2

#define LOW					0
#define HIGH				1

namespace arduino
{
	namespace gpio
	{

		void pinMode(int pin, int Pin_Mode);
		void digitalWrite(int pin, int Pin_State);

	}
}

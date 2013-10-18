#pragma once

typedef enum
{
	INPUT = 0,
	OUTPUT,
	INPUT_PULLUP
} Arduino_GPIO_Pin_Mode;

typedef enum
{
	LOW = 0,
	HIGH
} Arduino_GPIO_Pin_State;

namespace arduino
{
	namespace gpio
	{

		void pinMode(int pin, Arduino_GPIO_Pin_Mode Pin_Mode);
		void digitalWrite(int pin, Arduino_GPIO_Pin_State Pin_State);

	}
}

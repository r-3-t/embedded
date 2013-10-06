#include <led.hpp>
#include <hal/gpio.hpp>

namespace led
{

//typedef enum
// {
// 	GREEN			=	GPIO_Pin_12,
// 	ORANGE			=	GPIO_Pin_13,
// 	RED				=	GPIO_Pin_14,
// 	BLUE			=	GPIO_Pin_15,

// 	GREEN_ORANGE	=	GREEN | ORANGE,
// 	GREEN_RED		=	GREEN | RED,
// 	GREEN_BLUE		=	GREEN | BLUE,

// 	ORANGE_RED		=	ORANGE | RED,
// 	ORANGE_BLUE		=	ORANGE | BLUE,

// 	RED_BLUE		=	RED | BLUE,

// 	ALL				=	GREEN | ORANGE | RED | BLUE
// } Stm32f4_LedId_t;

typedef enum {
	GREEN_LED	=	GPIO_Pin_12,
	ORANGE_LED	=	GPIO_Pin_13,
	RED_LED		=	GPIO_Pin_14,
	BLUE_LED	=	GPIO_Pin_15,

	ALL_LEDS		= GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED,
} Stm32f4_LedId_t;

/* The GPIO port where the leds are connected
* (same pin numbers are present on many GPIO ports).
* Leds are connected to pins 12 through 15 on GPIO port D,
* so we use the port GPIOD.
* GPIOD is just a memory address casted to a GPIO_TypeDef pointer
* GPIO_TypeDef is defined in stm32f4xx.h
*/
static GPIO_TypeDef* LEDS_GPIO_PORT = GPIOD;

struct AutoInitLed
{
	AutoInitLed()
	{
		stm32f4::gpio::configure_pin(GPIOD, ALL_LEDS, GPIO_PuPd_NOPULL, GPIO_Mode_OUT);
	}
};

AutoInitLed gAutoInitLeds;

const LedGroup LedList[] = {LedGroup(GREEN_LED), LedGroup(ORANGE_LED), LedGroup(RED_LED), LedGroup(BLUE_LED)};

LedId_t	getNextLed(LedId_t currentLedId)
{
	if (currentLedId == invalidLedId())
		return GREEN_LED;
	else if (currentLedId == GREEN_LED)
		return ORANGE_LED;
	else if (currentLedId == ORANGE_LED)
		return RED_LED;
	else if (currentLedId == RED_LED)
		return BLUE_LED;
	else
		return invalidLedId();
}

LedColor_t	getLedColor(LedId_t LedId)
{
	if (LedId == GREEN_LED)
		return GREEN;
	else if (LedId == ORANGE_LED)
		return ORANGE ;
	else if (LedId == RED_LED)
		return RED ;
	else if (LedId == BLUE_LED)
		return BLUE ;
	else
		return INVALID;
}

LedGroup::LedGroup(LedId_t ledIds) : _ledIds(ledIds)
{
	if (ledIds == (LedId_t)-1)
		_ledIds = ALL_LEDS;
}

void LedGroup::on() const
{
	GPIO_SetBits(LEDS_GPIO_PORT, _ledIds);
}

void LedGroup::off() const
{
	GPIO_ResetBits(LEDS_GPIO_PORT, _ledIds);
}

void LedGroup::toggle() const
{
	GPIO_ToggleBits(LEDS_GPIO_PORT, _ledIds);
}

}

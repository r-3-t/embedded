#include <hal/led.hpp>
//#include <hal/gpio.hpp>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

namespace led
{

typedef enum {
	GREEN_LED	=	GPIO_Pin_9,
	BLUE_LED	=	GPIO_Pin_8,

	GREEN_BLUE  = GREEN_LED | BLUE_LED,

	ALL_LEDS		= GREEN_LED | BLUE_LED | GREEN_BLUE,
} Stm32f1_LedId_t;


static GPIO_TypeDef* LEDS_GPIO_PORT = GPIOC;

struct AutoInitLed
{
	AutoInitLed()
	{
		GPIO_InitTypeDef  GPIO_InitStructure;
  
		/* Enable the GPIO_LED Clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

		/* Configure the GPIO_LED pin */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;	  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);
	}
};

AutoInitLed gAutoInitLed;

const LedGroup LedList[] = {LedGroup(GREEN_LED), LedGroup(BLUE_LED)};


LedId_t	getNextLed(LedId_t currentLedId)
{
	if (currentLedId == invalidLedId())
		return GREEN_LED;
	else if (currentLedId == GREEN_LED)
		return BLUE_LED;
	else
		return invalidLedId();
}

LedColor_t	getLedColor(LedId_t LedId)
{
	if (LedId == GREEN_LED)
		return GREEN;
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
	LEDS_GPIO_PORT->BSRR = _ledIds;
}

void LedGroup::off() const
{
	LEDS_GPIO_PORT->BRR = _ledIds;}

void LedGroup::toggle() const
{
	LEDS_GPIO_PORT->ODR ^= _ledIds;
}

}

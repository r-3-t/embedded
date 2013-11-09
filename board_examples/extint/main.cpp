#include <hal/gpio.hpp>
#include <hal/extint.hpp>

#define LED_PORT							1
#define LED_PIN								1

#define EXTINT_PORT							1
#define EXTINT_PIN							0

//------------------------------------------------------------------------------

//configure led
::gpio::GPIO pinLed = ::gpio::GPIO(LED_PORT, LED_PIN);

//led interrupt service routine
void Led_High_ISR()
{
	pinLed.high();

	return;
}

//------------------------------------------------------------------------------
int main(void)
{

	//force led low
	pinLed.low();

	//configure external interrupt
	::extint::init_instance(EXTINT_PIN, EXTINT_PORT, ::extint::RisingTrigger, &Led_High_ISR);

	while (1)
	{

	}

}

//------------------------------------------------------------------------------


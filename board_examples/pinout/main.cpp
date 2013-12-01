
#include <hal/clock.hpp>
#include <hal/gpio.hpp>

#define LED_PORT							6
#define LED_PIN								1

//------------------------------------------------------------------------------

int main(void)
{

  ::gpio::GPIO pinLed = ::gpio::GPIO(LED_PORT, LED_PIN);

  int			time;

  time = 500;
  while(1)
  {
	if (time < 10) time = 500;
	pinLed.high();
    clock::msleep(time);
    pinLed.low();
    clock::msleep(time);
    time -= 20;

  }
}

//------------------------------------------------------------------------------



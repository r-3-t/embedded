
#include <hal/clock.hpp>
#include <hal/gpio.hpp>

//------------------------------------------------------------------------------

int main(void)
{

  ::gpio::GPIO pinLed = ::gpio::GPIO(1, 0);

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



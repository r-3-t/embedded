
#include <LedInterface.hpp>
#include <ClockInterface.hpp>



/* This is how long we wait in the delay function. */
#define PAUSE_LONG  1000
#define PAUSE_SHORT 400


/* Turn on the color leds one after another.
 * The order of the leds is defined in the array leds above.
 * The functions GPIO_SetBits and GPIO_ResetBits are declared
 * in stm32f4xx_gpio.h and implemented in stm32f4xx_gpio.c.
 *
 * You might want to look at the implementation in order to see
 * how this works.
 * Basically, this works by using the memory map mechanism of the
 * Cortex-M4: the pins of the GPIO port D are mapped to special
 * memory addresses which these function write to.
 * The exact addresses are represented by the fields of the
 * GPIO_TypeDef structure (that is by their offsets).
 * See also the structure GPIO_TypeDef in stm32f4xx.h.
 */
static void led_round(void)
{
  for (unsigned int i = 0; i < led::getNumLed(); i++)
  {
    /* Turn on led */
    led::LedList[i].on();
    /* Wait a short time */
    clock::msleep(PAUSE_LONG);
    /* Turn off led */
    led::LedList[i].off();
    /* Wait again before looping */
    clock::msleep(PAUSE_SHORT);
  }
}

/* Turn all leds on and off 4 times. */
static void flash_all_leds(void)
{
  led::LedGroup allLed;

  for (unsigned i = 0; i < 2; i++)
  {
    /* Turn on all user leds */
    allLed.on();
    // Wait a short time 
    clock::msleep(PAUSE_SHORT);
    /* Turn off all leds */
    allLed.off();
    /* Wait again before looping */
    clock::msleep(PAUSE_SHORT);
  }
}

void snake()
{

  for (unsigned int k = 0; k < 2; k++)
  {
    for (unsigned int i = 0; i < led::getNumLed(); i++)
    {
      // Turn on led 
      led::LedList[i].toggle();
      /* Wait a short time */
      clock::msleep(PAUSE_LONG);
    }
  }
}

/* Main function, the entry point of this program.
 * The main function is called from the startup code in file
 * Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s
 * (line 101)
 */
int main(void)
{
    while (1)
    {
      led_round();
      flash_all_leds();
      snake();
    }

    return 0; // never returns actually
}





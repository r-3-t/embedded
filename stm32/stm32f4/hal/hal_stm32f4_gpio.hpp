#pragma once

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#include <gpio.hpp>

namespace stm32f4
{
	namespace gpio
	{
		inline void configure_pin(GPIO_TypeDef* 	GPIOx, uint32_t		GPIO_Pin, GPIOPuPd_TypeDef GPIOPuPd, GPIOMode_TypeDef GpioMode)
		{
			uint32_t	  RCC_AHBxPeriph_GPIOx;

			if (GPIOx == GPIOA)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOA;
			else if (GPIOx == GPIOB)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOB;
			else if (GPIOx == GPIOC)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOC;
			else if (GPIOx == GPIOD)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOD;
			else if (GPIOx == GPIOE)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOE;
			else if (GPIOx == GPIOF)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOF;
			else if (GPIOx == GPIOG)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOG;
			else if (GPIOx == GPIOH)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOH;
			else if (GPIOx == GPIOI)
				RCC_AHBxPeriph_GPIOx = RCC_AHB1Periph_GPIOI;
			else
				RCC_AHBxPeriph_GPIOx = -1;
				
			

			/* enable the peripheral clock for the pins used by
			* USART2, PA2 for TX and PA3 for RX
			*/
			RCC_AHB1PeriphClockCmd(RCC_AHBxPeriph_GPIOx, ENABLE);

			/* This sequence sets up the TX and RX pins
			* so they work correctly with the USART2 peripheral
			*/

			GPIO_InitTypeDef	GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin; // Pins 6 (TX) and 7 (RX) are used
			GPIO_InitStruct.GPIO_Mode = GpioMode;       // the pins are configured as alternate function so the USART peripheral has access to them
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    // this defines the IO speed and has nothing to do with the baudrate!
			GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;     // this defines the output type as push pull mode (as opposed to open drain)
			GPIO_InitStruct.GPIO_PuPd = GPIOPuPd;     // this activates the pullup resistors on the IO pins
			GPIO_Init(GPIOx, &GPIO_InitStruct);         // now all the values are passed to the GPIO_Init() function which sets the GPIO registers
		}

		inline void configure_pin(GPIO_TypeDef* 	GPIOx, uint32_t		GPIO_Pin, GPIOPuPd_TypeDef GPIOPuPd)
		{
			configure_pin(GPIOx, GPIO_Pin, GPIOPuPd, GPIO_Mode_AF);
		}


		class Stm32f4_PinOut : public ::gpio::PinOut
		{
		public:
			Stm32f4_PinOut(GPIO_TypeDef* 	GPIOx, uint16_t Gpio_Pin) : _GPIOx(GPIOx), _Gpio_Pin(Gpio_Pin)
			{
				configure_pin(GPIOx, Gpio_Pin, GPIO_PuPd_UP, GPIO_Mode_OUT);
			}

			virtual void high()
			{
				GPIO_SetBits(_GPIOx, _Gpio_Pin);
			}

			virtual void low()
			{
				GPIO_ResetBits(_GPIOx, _Gpio_Pin);
			}

		private:
			GPIO_TypeDef* 	_GPIOx;
			uint16_t		_Gpio_Pin;
		};

	}
}

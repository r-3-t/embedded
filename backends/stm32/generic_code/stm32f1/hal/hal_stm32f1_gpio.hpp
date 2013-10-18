#pragma once

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include <gpio.hpp>

namespace gpio
{
	inline void configure_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin, GPIOMode_TypeDef GpioMode)
	{
		uint32_t	  RCC_AHBxPeriph_GPIOx;

		if (GPIOx == GPIOA)
			RCC_AHBxPeriph_GPIOx = RCC_APB2Periph_GPIOA;
		else if (GPIOx == GPIOB)
			RCC_AHBxPeriph_GPIOx = RCC_APB2Periph_GPIOB;
		else if (GPIOx == GPIOC)
			RCC_AHBxPeriph_GPIOx = RCC_APB2Periph_GPIOC;
		else if (GPIOx == GPIOD)
			RCC_AHBxPeriph_GPIOx = RCC_APB2Periph_GPIOD;
		else if (GPIOx == GPIOE)
			RCC_AHBxPeriph_GPIOx = RCC_APB2Periph_GPIOE;
		else if (GPIOx == GPIOF)
			RCC_AHBxPeriph_GPIOx = RCC_APB2Periph_GPIOF;
		else if (GPIOx == GPIOG)
			RCC_AHBxPeriph_GPIOx = RCC_APB2Periph_GPIOG;
		else
			RCC_AHBxPeriph_GPIOx = -1;


		/* enable the peripheral clock for the pins used by
		* USART2, PA2 for TX and PA3 for RX
		*/
		RCC_APB2PeriphClockCmd(RCC_AHBxPeriph_GPIOx, ENABLE);


		GPIO_InitTypeDef	GPIO_InitStruct; //
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin; //
		GPIO_InitStruct.GPIO_Mode = GpioMode;       // the pins are configured as alternate function so the USART peripheral has access to them
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    // this defines the IO speed and has nothing to do with the baudrate!
		GPIO_Init(GPIOx, &GPIO_InitStruct);         // now all the values are passed to the GPIO_Init() function which sets the GPIO registers
	}

	inline void configure_gpio_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
	{
		configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_Out_PP);
	}

	inline void set_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
	{
		GPIO_SetBits(GPIOx, GPIO_Pin);
	}

	inline void reset_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin);
	}
} //namespace gpio

namespace stm32f1xx
{
	namespace gpio
	{
		class Stm32f1xx_PinOut : public ::gpio::PinOut
		{
		public:
			Stm32f1xx_PinOut(GPIO_TypeDef* 	GPIOx, uint16_t Gpio_Pin) : _GPIOx(GPIOx), _Gpio_Pin(Gpio_Pin)
			{
				::gpio::configure_gpio_pin(GPIOx, Gpio_Pin);
			}

			virtual void high()
			{
				::gpio::set_pin(_GPIOx, _Gpio_Pin);
			}

			virtual void low()
			{
				::gpio::reset_pin(_GPIOx, _Gpio_Pin);
			}

		private:
			GPIO_TypeDef* 	_GPIOx;
			uint16_t		_Gpio_Pin;
		};

	}
}


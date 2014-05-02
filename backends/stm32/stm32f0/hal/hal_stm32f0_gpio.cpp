#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>

#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>

#include "hal_stm32f0_gpio.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

namespace stm32f0xx
{
	namespace gpio
	{

		GPIO_TypeDef* get_GPIO_port_from_id(::pinout::Gpio_id 	GPIOId)
		{

			switch (GPIOId)
			{
			case 1:
				//GPIOA
				return GPIOA;
				break;
			case 2:
				//GPIOB
				return GPIOB;
				break;
			case 3:
				//GPIOC
				return GPIOC;
				break;
			case 4:
				//GPIOD
				return GPIOD;
				break;
			case 5:
				//GPIOE
				return GPIOE;
				break;
			case 6:
				//GPIOF
				return GPIOF;
				break;
			}

			fprintf(stderr, "Invalid GPIO port : %i !\n", GPIOId);
			abort();
		}

		uint16_t get_GPIO_pin_from_id(::pinout::Pin_id PINId)
		{

			assert(PINId < STM32F0XX_PIN_MAX_COUNT);

			return (1 << PINId);
		}

		void configure_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin, GPIOMode_TypeDef GpioMode, GPIOOType_TypeDef GPIOOType, GPIOPuPd_TypeDef GPIOPuPd)
		{
			uint32_t	  RCC_AHBxPeriph_GPIOx;

			if (GPIOx == GPIOA)
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOA;
			else if (GPIOx == GPIOB)
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOB;
			else if (GPIOx == GPIOC)
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOC;
			else if (GPIOx == GPIOD)
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOD;
			else if (GPIOx == GPIOE)
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOE;
			else if (GPIOx == GPIOF)
				RCC_AHBxPeriph_GPIOx = RCC_AHBPeriph_GPIOF;
			else
			{
				fprintf(stderr, "Invalid GPIO : %x !\n", (unsigned int)GPIOx);
				abort();
			}


			RCC_AHBPeriphClockCmd(RCC_AHBxPeriph_GPIOx, ENABLE);


			GPIO_InitTypeDef	GPIO_InitStruct; //
			GPIO_InitStruct.GPIO_Mode = GpioMode;
			GPIO_InitStruct.GPIO_OType = GPIOOType;
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
			GPIO_InitStruct.GPIO_PuPd = GPIOPuPd;
			GPIO_Init(GPIOx, &GPIO_InitStruct);         // now all the values are passed to the GPIO_Init() function which sets the GPIO registers
		}

		void configure_gpio_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
			configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
		}

		void configure_extint_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
			//configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_IN_FLOATING);
		}

		void configure_pwm_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
			//configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_AF_PP);
		}

		void set_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
			GPIO_SetBits(GPIOx, GPIO_Pin);
		}

		void reset_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
			GPIO_ResetBits(GPIOx, GPIO_Pin);
		}

		bool is_pin_high(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
			if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_SET)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}//namespace gpio

} //namespace stm32f0xx



namespace gpio
{

	void configure_gpio_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		::stm32f0xx::gpio::configure_gpio_pin(::stm32f0xx::gpio::get_GPIO_port_from_id(GPIOId), ::stm32f0xx::gpio::get_GPIO_pin_from_id(PINId));
	}

	void set_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		::stm32f0xx::gpio::set_pin(::stm32f0xx::gpio::get_GPIO_port_from_id(GPIOId), ::stm32f0xx::gpio::get_GPIO_pin_from_id(PINId));
	}

	void reset_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		::stm32f0xx::gpio::reset_pin(::stm32f0xx::gpio::get_GPIO_port_from_id(GPIOId), ::stm32f0xx::gpio::get_GPIO_pin_from_id(PINId));
	}

} //namespace gpio

#include "hal_stm32.hpp"

#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>

#include "hal_stm32_gpio.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

namespace stm32
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
#ifdef STM32F4XX
			case 6:
				//GPIOF
				return GPIOF;
			case 7:
				//GPIOG
				return GPIOG;
			case 8:
				//GPIOH
				return GPIOH;
			case 9:
				//GPIOI
				return GPIOI;
				break;
#endif //STM32F4XX
			}

			fprintf(stderr, "Invalid GPIO port : %i !\n", GPIOId);
			abort();
		}

		uint16_t get_GPIO_pin_from_id(::pinout::Pin_id PINId)
		{

			assert(PINId < STM32_PIN_MAX_COUNT);

			return (1 << PINId);
		}

#ifdef STM32F1XX
		void configure_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin, GPIOMode_TypeDef GpioMode)
		{
#else
		void configure_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin, GPIOMode_TypeDef GpioMode, GPIOOType_TypeDef GPIOOType, GPIOPuPd_TypeDef GPIOPuPd)
		{
#endif
#ifdef STM32F0XX
			if (GPIOx == GPIOA)
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
			else if (GPIOx == GPIOB)
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
			else if (GPIOx == GPIOC)
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
			else if (GPIOx == GPIOD)
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
			else if (GPIOx == GPIOE)
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
			else if (GPIOx == GPIOF)
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
#elif STM32F1XX		
			if (GPIOx == GPIOA)
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			else if (GPIOx == GPIOB)
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			else if (GPIOx == GPIOC)
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			else if (GPIOx == GPIOD)
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
			else if (GPIOx == GPIOE)
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
			else if (GPIOx == GPIOF)
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
			else if (GPIOx == GPIOG)
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
#elif STM32F4XX
			if (GPIOx == GPIOA)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			else if (GPIOx == GPIOB)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			else if (GPIOx == GPIOC)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
			else if (GPIOx == GPIOD)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			else if (GPIOx == GPIOE)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			else if (GPIOx == GPIOF)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
			else if (GPIOx == GPIOG)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
			else if (GPIOx == GPIOH)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
			else if (GPIOx == GPIOI)
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
#endif //STM32F0XX
			else
			{
				fprintf(stderr, "Invalid GPIO : %x !\n", (unsigned int)GPIOx);
				abort();
			}

			GPIO_InitTypeDef	GPIO_InitStruct;

			GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
			GPIO_InitStruct.GPIO_Mode = GpioMode;

#ifdef STM32F0XX
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
			GPIO_InitStruct.GPIO_OType = GPIOOType;
			GPIO_InitStruct.GPIO_PuPd = GPIOPuPd;
			GPIO_Init(GPIOx, &GPIO_InitStruct);
#elif STM32F1XX	
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOx, &GPIO_InitStruct);
#elif STM32F4XX
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_OType = GPIOOType;
			GPIO_InitStruct.GPIO_PuPd = GPIOPuPd;
#endif

			GPIO_Init(GPIOx, &GPIO_InitStruct);
		}

		void configure_gpio_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{	
#ifdef STM32F1XX
			configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_Out_PP);
#else
			configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
#endif
		}

		void configure_extint_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
#ifdef STM32F1XX
			configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_IN_FLOATING);
#else
			
#endif
		}

		void configure_pwm_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin)
		{
#ifdef STM32F1XX
			configure_pin(GPIOx, GPIO_Pin, GPIO_Mode_Out_PP);
#else

#endif
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

} //namespace stm32



namespace gpio
{

	void configure_gpio_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		::stm32::gpio::configure_gpio_pin(::stm32::gpio::get_GPIO_port_from_id(GPIOId), ::stm32::gpio::get_GPIO_pin_from_id(PINId));
	}

	void set_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		::stm32::gpio::set_pin(::stm32::gpio::get_GPIO_port_from_id(GPIOId), ::stm32::gpio::get_GPIO_pin_from_id(PINId));
	}

	void reset_pin(::pinout::Gpio_id 	GPIOId, ::pinout::Pin_id PINId)
	{
		::stm32::gpio::reset_pin(::stm32::gpio::get_GPIO_port_from_id(GPIOId), ::stm32::gpio::get_GPIO_pin_from_id(PINId));
	}

} //namespace gpio

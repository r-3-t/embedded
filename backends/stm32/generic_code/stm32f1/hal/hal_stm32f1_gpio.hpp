#pragma once

#include <stm32f10x_gpio.h>

#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>

#define STM32F1XX_GPIO_MAX_COUNT								7
#define STM32F1XX_PIN_MAX_COUNT									16

namespace stm32f1xx
{
	namespace gpio
	{

		GPIO_TypeDef* get_GPIO_port_from_id(::pinout::Gpio_id 	GPIOId);

		uint16_t get_GPIO_pin_from_id(::pinout::Pin_id PINId);

		void configure_gpio_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin);

		void configure_extint_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin);

		void configure_pwm_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin);

		void set_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin);

		void reset_pin(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin);

		bool is_pin_high(GPIO_TypeDef* 	GPIOx, uint16_t		GPIO_Pin);

	} //namespace gpio

} //namespace stm32f1xx

namespace gpio
{


} //namespace gpio

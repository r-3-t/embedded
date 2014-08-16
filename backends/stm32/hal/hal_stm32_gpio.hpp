#pragma once

#ifdef STM32F0XX
#include <stm32f0xx_gpio.h>
#elif STM32F1XX
#include <stm32f10x_gpio.h>
#elif STM32F4XX
#include <stm32f4xx_gpio.h>
#endif //STM32F0XX

#include <GpioInterface.hpp>
#include <PinoutInterface.hpp>

namespace stm32
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

} //namespace stm32

namespace gpio
{


} //namespace gpio

#pragma once

#ifdef STM32F0XX
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_misc.h>
#include <stm32f0xx_usart.h>
#include <stm32f0xx_spi.h>
#include <stm32f0xx_i2c.h>
#include <stm32f0xx_tim.h>
#include <stm32f0xx_exti.h>
#include <core_cm0.h>
#define	STM32_UART_MAX_COUNT							5
#define STM32_GPIO_MAX_COUNT							5
#define STM32_PIN_MAX_COUNT								16
#define STM32_EXTINT_MAX_COUNT							16
#elif STM32F1XX
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <misc.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_spi.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_exti.h>
#include <core_cm3.h>
#define	STM32_UART_MAX_COUNT							5
#define STM32_GPIO_MAX_COUNT							5
#define STM32_PIN_MAX_COUNT								16
#define STM32_EXTINT_MAX_COUNT							16
#elif STM32F4XX
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <misc.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_i2c.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_exti.h>
#include <core_cm4.h>
#define	STM32_UART_MAX_COUNT							5
#define STM32_GPIO_MAX_COUNT							9
#define STM32_PIN_MAX_COUNT								16
#define STM32_EXTINT_MAX_COUNT							16
#endif //STM32F0XX


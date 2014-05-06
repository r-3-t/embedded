#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <misc.h>

#include <PwmInterface.hpp>
#include <PinoutInterface.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

namespace stm32f1xx {

	namespace pwm
	{

		TIM_TypeDef* get_timer_from_gpio(GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin)
		{

			//TODO: add pwm for GPIOC/D/E....
			if (GPIOx == GPIOA)
			{
				switch (Gpio_Pin)
				{
				case GPIO_Pin_0:
				case GPIO_Pin_1:
				case GPIO_Pin_2:
				case GPIO_Pin_3:
					return TIM2;
					break;
				case GPIO_Pin_6:
				case GPIO_Pin_7:
					return TIM3;
					break;
				case GPIO_Pin_8:
				case GPIO_Pin_9:
				case GPIO_Pin_10:
				case GPIO_Pin_11:
				case GPIO_Pin_12:
					return TIM1;
					break;
				}
			}
			else if (GPIOx == GPIOB)
			{
				switch (Gpio_Pin)
				{
				case GPIO_Pin_0:
				case GPIO_Pin_1:
					return TIM3;
					break;
				case GPIO_Pin_6:
				case GPIO_Pin_7:
				case GPIO_Pin_8:
				case GPIO_Pin_9:
					return TIM4;
					break;
				case GPIO_Pin_12:
				case GPIO_Pin_13:
				case GPIO_Pin_14:
				case GPIO_Pin_15:
					return TIM1;
					break;
				}

			}//if GPIOx

			fprintf(stderr, "Invalid GPIO %x and Pin %x !\n", (unsigned int)GPIOx, (unsigned int)Gpio_Pin);
			abort();
		}

		uint16_t get_channel_from_gpio(GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin)
		{

			//TODO: add pwm for GPIOC/D/E....
			if (GPIOx == GPIOA)
			{
				switch (Gpio_Pin)
				{
				case GPIO_Pin_0:
					return TIM_Channel_1;
					break;
				case GPIO_Pin_1:
					return TIM_Channel_2;
					break;
				case GPIO_Pin_2:
					return TIM_Channel_3;
					break;
				case GPIO_Pin_3:
					return TIM_Channel_4;
					break;
				case GPIO_Pin_6:
					return TIM_Channel_1;
					break;
				case GPIO_Pin_7:
					return TIM_Channel_2;
					break;
				case GPIO_Pin_8:
					return TIM_Channel_1;
					break;
				case GPIO_Pin_9:
					return TIM_Channel_2;
					break;
				case GPIO_Pin_10:
					return TIM_Channel_3;
					break;
				case GPIO_Pin_11:
					return TIM_Channel_4;
					break;
				}

			}
			else if (GPIOx == GPIOB)
			{
				switch (Gpio_Pin)
				{
				case GPIO_Pin_0:
					return TIM_Channel_3;
					break;
				case GPIO_Pin_1:
					return TIM_Channel_4;
					break;
				case GPIO_Pin_6:
					return TIM_Channel_1;
					break;
				case GPIO_Pin_7:
					return TIM_Channel_2;
					break;
				case GPIO_Pin_8:
					return TIM_Channel_3;
					break;
				case GPIO_Pin_9:
					return TIM_Channel_4;
					break;
				case GPIO_Pin_13:
					return TIM_Channel_1;
					break;
				case GPIO_Pin_14:
					return TIM_Channel_2;
					break;
				case GPIO_Pin_15:
					return TIM_Channel_3;
					break;
				}
			} //if GPIOx

			fprintf(stderr, "Invalid GPIO %x and Pin %x !\n", (unsigned int)GPIOx, (unsigned int)Gpio_Pin);
			abort();
		}

		void enable_timer_clock(TIM_TypeDef* Timer)
		{
		    if (Timer == TIM1)
		    {
		    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		    }
		    else if (Timer == TIM2)
		    {
		    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		    }
		    else if (Timer == TIM3)
		    {
		    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		    }
		    else if (Timer == TIM4)
		    {
		    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		    }
		    else
		    {
				fprintf(stderr, "Invalid Timer %x !\n", (unsigned int)Timer);
				abort();
		    }
		}

		//GPIOA-G / 16 pins
		static ::pwm::PwmInterface* gpPwm[STM32F1XX_GPIO_MAX_COUNT][STM32F1XX_PIN_MAX_COUNT];

		Pwm::Pwm(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId, uint32_t Frequency, uint32_t MaxDuty)
		{

			TIM_TimeBaseInitTypeDef 		TIM_TimeBaseInitStruct;
			TIM_OCInitTypeDef 				TIM_OCInitStruct;

			//check params
			assert(GPIOId < STM32F1XX_GPIO_MAX_COUNT);
			assert(PINId < STM32F1XX_PIN_MAX_COUNT);


			gpPwm[GPIOId][PINId] = this;

			_GPIOx = ::stm32f1xx::gpio::get_GPIO_port_from_id(GPIOId);
			_Gpio_Pin = ::stm32f1xx::gpio::get_GPIO_pin_from_id(PINId);
			_Frequency = Frequency;
			_MaxDuty = MaxDuty;
			_Timer = get_timer_from_gpio(_GPIOx, _Gpio_Pin);
			_Channel = get_channel_from_gpio(_GPIOx, _Gpio_Pin);

			//configure GPIO pin for pwm
			::stm32f1xx::gpio::configure_pwm_pin(_GPIOx, _Gpio_Pin);

			//init time base struct
			TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
			TIM_OCStructInit(&TIM_OCInitStruct);

			//enable APB clock
			enable_timer_clock(_Timer);

			// configure frequency resolution
			TIM_TimeBaseInitStruct.TIM_Period = MaxDuty;
			TIM_TimeBaseInitStruct.TIM_Prescaler = (SystemCoreClock / (TIM_TimeBaseInitStruct.TIM_Period)) / Frequency;
			TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;


			//init timer
			TIM_TimeBaseInit(_Timer, &TIM_TimeBaseInitStruct);

			//configure ouput channel
			TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
			// Initial duty cycle equals 0. Value can range from zero to MaxDuty.
			TIM_OCInitStruct.TIM_Pulse = 0;

			switch (_Channel)
			{
			case TIM_Channel_1:
				TIM_OC1Init(_Timer, &TIM_OCInitStruct);
				break;
			case TIM_Channel_2:
				TIM_OC2Init(_Timer, &TIM_OCInitStruct);
				break;
			case TIM_Channel_3:
				TIM_OC3Init(_Timer, &TIM_OCInitStruct);
				break;
			case TIM_Channel_4:
				TIM_OC4Init(_Timer, &TIM_OCInitStruct);
				break;
			default:
				fprintf(stderr, "Invalid Channel %x !\n", _Channel);
				abort();
				break;
			}

			//enable
			TIM_Cmd(_Timer, ENABLE);


		}

		void Pwm::setDuty(uint32_t Duty)
		{
			switch (_Channel)
			{
			case TIM_Channel_1:
				_Timer->CCR1 = Duty;
				break;
			case TIM_Channel_2:
				_Timer->CCR2 = Duty;
				break;
			case TIM_Channel_3:
				_Timer->CCR3 = Duty;
				break;
			case TIM_Channel_4:
				_Timer->CCR4 = Duty;
				break;
			default:
				fprintf(stderr, "Invalid Channel %x !\n", _Channel);
				abort();
				break;
			}
		}

	} //namespace pwm

} //namespace stm32f1xx

namespace pwm
{

	typedef ::stm32f1xx::pwm::Pwm		ConcretePwm;

}//namespace pwm



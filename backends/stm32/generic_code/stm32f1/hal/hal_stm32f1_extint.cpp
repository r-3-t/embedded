#include <stm32f10x_exti.h>
#include <stm32f10x_rcc.h>
#include <misc.h>

#include <ExtintInterface.hpp>
#include <PinoutInterface.hpp>
#include <hal/Extint.hpp>
#include <hal/Gpio.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#define STM32F1XX_EXTINT_MAX_COUNT								16

namespace stm32f1xx {

	namespace extint
	{

		EXTITrigger_TypeDef get_stm32_trigger_from_hal_trigger(::extint::InterruptTrigger_T Mode)
		{
			switch (Mode)
			{
			case ::extint::RisingTrigger:
				return EXTI_Trigger_Rising;
				break;
			case ::extint::FallingTrigger:
				return EXTI_Trigger_Falling;
				break;
			case ::extint::RisingFallingTrigger:
				return EXTI_Trigger_Rising_Falling;
				break;
			default:
				fprintf(stderr, "Invalid Trigger Mode : %i !\n", Mode);
				abort();
				break;
			}

			return EXTI_Trigger_Rising_Falling;

		}

		IRQn_Type get_IRQn_Type_from_ext_line(uint32_t EXT_Line)
		{
			switch (EXT_Line)
			{
			case EXTI_Line0:
				return EXTI0_IRQn;
				break;
			case EXTI_Line1:
				return EXTI1_IRQn;
				break;
			case EXTI_Line2:
				return EXTI2_IRQn;
				break;
			case EXTI_Line3:
				return EXTI3_IRQn;
				break;
			case EXTI_Line4:
				return EXTI4_IRQn;
				break;
			case EXTI_Line5:
			case EXTI_Line6:
			case EXTI_Line7:
			case EXTI_Line8:
			case EXTI_Line9:
				return EXTI9_5_IRQn;
				break;
			case EXTI_Line10:
			case EXTI_Line11:
			case EXTI_Line12:
			case EXTI_Line13:
			case EXTI_Line14:
			case EXTI_Line15:
				return EXTI15_10_IRQn;
				break;
			}

			fprintf(stderr, "Invalid EXT_Line : %x !\n", (unsigned int)EXT_Line);
			abort();;
		}

		uint32_t get_extint_line_from_id(::pinout::Pin_id PINId)
		{

			return (1 << PINId);
		}

		extint::Extint* 	gpExtint[STM32F1XX_EXTINT_MAX_COUNT];

		Extint::Extint(::pinout::Pin_id PINId, ::pinout::Gpio_id 	GPIOId, ::extint::InterruptTrigger_T Mode, ::extint::callback_T callback)
		{
			NVIC_InitTypeDef		NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

			//check params
			assert(PINId < sizeof(gpExtint)/sizeof(extint::Extint*));

			gpExtint[PINId] = this;

			_GPIOx = ::stm32f1xx::gpio::get_GPIO_port_from_id(GPIOId);
			_Gpio_Pin = ::stm32f1xx::gpio::get_GPIO_pin_from_id(PINId);
			_EXTI_Line = get_extint_line_from_id(PINId);
			_Mode = Mode;
			_callback = callback;

			//configure GPIO pin as external interrupt
			::stm32f1xx::gpio::configure_extint_pin(_GPIOx, _Gpio_Pin);

			//configure stm32 exti structure
			EXTI_StructInit(&_EXTIx);

			_EXTIx.EXTI_Line = _EXTI_Line;
			_EXTIx.EXTI_Mode = EXTI_Mode_Interrupt;
			_EXTIx.EXTI_Trigger = stm32f1xx::extint::get_stm32_trigger_from_hal_trigger(Mode);
			_EXTIx.EXTI_LineCmd = ENABLE;

			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group
			NVIC_InitStructure.NVIC_IRQChannel = stm32f1xx::extint::get_IRQn_Type_from_ext_line(_EXTI_Line); //IRQ type
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     // this sets the subpriority inside the group
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      // enable interrupt
			NVIC_Init(&NVIC_InitStructure);              // the properties are passed to the NVIC_Init function which takes care of the low level stuff

			//clear pending IT before enabling it
			clear();

			//initialize external interrupt and enable it
			EXTI_Init(&_EXTIx);
		}

		void Extint::clear()
		{
			//clear pending IT
			EXTI_ClearITPendingBit(_EXTI_Line);
		}

		bool Extint::triggered()
		{
			//is this external line generate the interrupt ?
			if (EXTI_GetITStatus(_EXTI_Line) == SET)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool Extint::is_high()
		{
			return ::stm32f1xx::gpio::is_pin_high(_GPIOx, _Gpio_Pin);
		}
		void Extint::disable()
		{
			_EXTIx.EXTI_LineCmd = DISABLE;

			//disable external interrupt
			EXTI_Init(&_EXTIx);

		}

		void Extint::enable()
		{
			_EXTIx.EXTI_LineCmd = ENABLE;

			//enable external interrupt
			EXTI_Init(&_EXTIx);
		}


	#define EXTINT_IRQ_CALLBACK(ExtiX) void EXTI##ExtiX##_IRQHandler()									\
										{																\
											gpExtint[ExtiX]->_callback();								\
											gpExtint[ExtiX]->clear(); /* clear interrupt */\
										}

	extern "C"
	{
		EXTINT_IRQ_CALLBACK(0)
		EXTINT_IRQ_CALLBACK(1)
		EXTINT_IRQ_CALLBACK(2)
		EXTINT_IRQ_CALLBACK(3)
		EXTINT_IRQ_CALLBACK(4)

		void EXTI9_5_IRQHandler()
		{
			int 		i;

			//search for interrupt source, several interrupts may occur
			for (i = 5; i <= 9; i++)
			{
				if (gpExtint[i] != 0)
				{
					if (gpExtint[i]->triggered() == true)
					{
						gpExtint[i]->_callback();
						gpExtint[i]->clear(); /* clear interrupt */
					}
				}
			}
		}

		void EXTI15_10_IRQHandler()
		{
			int 		i;

			//search for interrupt source, several interrupts may occur
			for (i = 10; i <= 15; i++)
			{
				if (gpExtint[i] != 0)
				{
					if (gpExtint[i]->triggered() == true)
					{
						gpExtint[i]->_callback();
						gpExtint[i]->clear(); /* clear interrupt */
					}
				}
			}
		}

	}


	} //namespace extint

} //namespace stm32f1xx


#pragma once

#include <stm32f10x_exti.h>
#include <stm32f10x_rcc.h>
#include <misc.h>
#include <gpio.hpp>
#include <extint.hpp>
#include <pinout.hpp>
#include <map>

namespace stm32f1xx {

	namespace extint
	{

		inline EXTITrigger_TypeDef get_stm32_trigger_from_hal_trigger(::extint::InterruptTrigger_T Mode)
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
				//TODO: generate error
				break;
			}

			return EXTI_Trigger_Rising_Falling;

		}

		inline IRQn_Type get_IRQn_Type_from_ext_line(uint32_t EXT_Line)
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

			//TODO: generate error
			return EXTI0_IRQn;
		}

		inline uint32_t get_extint_line_from_id(::pinout::Pin_id PINId)
		{

			return (1 << PINId);
		}


		class Extint : public ::extint::Extint
		{
		public:
			Extint(::pinout::Pin_id PINId, ::pinout::Gpio_id 	GPIOId, ::extint::InterruptTrigger_T Mode, ::extint::callback_T callback)
			{
				NVIC_InitTypeDef		NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)


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

			void clear()
			{
				//clear pending IT
				EXTI_ClearITPendingBit(_EXTI_Line);
			}

			bool triggered()
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

		private:
			EXTI_InitTypeDef 				_EXTIx;
			uint32_t						_EXTI_Line;
			GPIO_TypeDef* 					_GPIOx;
			uint16_t						_Gpio_Pin;
			::extint::InterruptTrigger_T 	_Mode;

		};

	#define EXTINT_IRQ_CALLBACK(ExtiX) inline void EXTI##ExtiX##_IRQHandler()									\
										{																\
											::extint::get_instance(ExtiX)->_callback();					\
											::extint::get_instance(ExtiX)->clear(); /* clear interrupt */\
										}

	extern "C"
	{
		EXTINT_IRQ_CALLBACK(0)
		EXTINT_IRQ_CALLBACK(1)
		EXTINT_IRQ_CALLBACK(2)
		EXTINT_IRQ_CALLBACK(3)
		EXTINT_IRQ_CALLBACK(4)

		inline void EXTI9_5_IRQHandler()
		{
			int 		i;

			//search for interrupt source, several interrupts may occur
			for (i = 5; i <= 9; i++)
			{
				if (::extint::get_instance(i) != nullptr)
				{
					if (::extint::get_instance(i)->triggered() == true)
					{
						::extint::get_instance(i)->_callback();
						::extint::get_instance(i)->clear(); /* clear interrupt */
					}
				}
			}
		}

		inline void EXTI15_10_IRQHandler()
		{
			int 		i;

			//search for interrupt source, several interrupts may occur
			for (i = 10; i <= 15; i++)
			{
				if (::extint::get_instance(i) != nullptr)
				{
					if (::extint::get_instance(i)->triggered() == true)
					{
						::extint::get_instance(i)->_callback();
						::extint::get_instance(i)->clear(); /* clear interrupt */
					}
				}
			}
		}

	}


	static std::map< ::pinout::Pin_id, Extint* > gpExtint;

	} //namespace extint

} //namespace stm32f1xx

namespace extint
{
	inline unsigned int	num_instance()
	{
		return (sizeof(::stm32f1xx::extint::gpExtint)/sizeof(::stm32f1xx::extint::Extint*));
	}

	inline void init_instance(::pinout::Pin_id PINId, ::pinout::Gpio_id 	GPIOId, InterruptTrigger_T Mode, callback_T callback)
	{
		::stm32f1xx::extint::gpExtint[PINId] = new ::stm32f1xx::extint::Extint(PINId, GPIOId, Mode, callback);
	}

	inline Extint* get_instance(::pinout::Pin_id PINId)
	{
		//search for a valid exint object
		if (::stm32f1xx::extint::gpExtint.count(PINId) > 0)
		{
			return ::stm32f1xx::extint::gpExtint[PINId];
		}
		return nullptr;
	}
}//namespace extint


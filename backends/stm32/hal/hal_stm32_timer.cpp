#include "hal_stm32.hpp"

#include <TimerInterface.hpp>
#include "hal_stm32_timer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

namespace stm32 {

	namespace timer
	{

		TIM_TypeDef* get_timer_from_id(::timer::Timer_Id TimerId)
		{
			switch (TimerId)
			{
			case 1:
				return TIM1;
				break;
			case 2:
				return TIM2;
				break;
			case 3:
				return TIM3;
				break;
			case 6:
				return TIM6;
				break;
			case 7:
				return TIM7;
				break;
			case 14:
				return TIM14;
				break;
#ifdef STM32F0XX
			case 15:
				return TIM15;
				break;
#endif //STM32F0XX
#ifdef STM32F1XX
			case 4:
				return TIM4;
				break;
			case 5:
				return TIM5;
				break;
			case 8:
				return TIM8;
				break;
			case 9:
				return TIM9;
				break;
			case 10:
				return TIM10;
				break;
			case 11:
				return TIM11;
				break;
			case 12:
				return TIM12;
				break;
			case 13:
				return TIM13;
				break;
			case 15:
				return TIM15;
				break;
#endif //STM32F1XX
			}

			fprintf(stderr, "Invalid TimerId : %i !\n", TimerId);
			abort();

		}

		inline uint8_t get_IRQn_Type_from_timer(TIM_TypeDef* Timer)
		{
			if (Timer == TIM2)
			{
				return TIM2_IRQn;
			}
			else if (Timer == TIM3)
			{
				return TIM3_IRQn;
			}
#ifdef STM32F1XX
			else if (Timer == TIM4)
			{
				return TIM4_IRQn;
			}
#endif //STM32F1XX

			fprintf(stderr, "Invalid Timer : %x !\n", (unsigned int)Timer);
			abort();


		}

		inline void enable_timer_clock(TIM_TypeDef* Timer)
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
#ifdef STM32F1XX
		    else if (Timer == TIM4)
		    {
		    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		    }
#endif //STM32F1XX
		    else
		    {
		    	fprintf(stderr, "Invalid Timer : %x !\n", (unsigned int)Timer);
		    	abort();
		    }


		}

		static ::timer::TimerInterface* gpTimer[8];

		Timer::Timer(::timer::Timer_Id TimerId, ::timer::SubdivisionDelay_T Delay, uint16_t Period, ::timer::callback_T callback)
		{

			TIM_TimeBaseInitTypeDef 		TIM_TimeBaseInitStruct;
			TIM_OCInitTypeDef 				TIM_OCInitStruct;
			NVIC_InitTypeDef				NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

			//check args
			assert(TimerId < sizeof(gpTimer)/sizeof(::timer::TimerInterface*));

			_Timer = get_timer_from_id(TimerId);
			_callback = callback;
			_Delay = Delay;

			gpTimer[TimerId] = this;

			//init time base struct
			TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
			TIM_OCStructInit(&TIM_OCInitStruct);

			//enable APB clock
			enable_timer_clock(_Timer);

			/* Set the default configuration */
			TIM_TimeBaseInitStruct.TIM_Period = 0xffff;
			if (Delay == ::timer::SubdivisionDelayMs)
			{
				TIM_TimeBaseInitStruct.TIM_Prescaler = (SystemCoreClock / 2) / 1000; //resolution @ (1 / 2) ms
			}
			else if (Delay == ::timer::SubdivisionDelayUs)
			{
				TIM_TimeBaseInitStruct.TIM_Prescaler = (SystemCoreClock) / 1000000; //resolution @ 1 us
				TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
			}
			else
			{
				fprintf(stderr, "Invalid SubdivisionDelay !\n");
				abort();
			}

			TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
			TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; //not implemented

			//init timer
			TIM_TimeBaseInit(_Timer, &TIM_TimeBaseInitStruct);

			//enable autoreload register
			TIM_ARRPreloadConfig(_Timer, ENABLE);

			//enable NVIC for this timer
			NVIC_InitStructure.NVIC_IRQChannel = stm32::timer::get_IRQn_Type_from_timer(_Timer); //IRQ type
#ifdef STM32F0XX
			NVIC_InitStructure.NVIC_IRQChannelPriority = 0;     // this sets the subpriority inside the group
#endif //STM32F0XX

#ifdef STM32F1XX
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
#endif //STM32F1XX
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      // enable interrupt
			NVIC_Init(&NVIC_InitStructure);

			//set period
			setPeriod(Period);
		}

		void Timer::clear()
		{
			//clear pending IT
			TIM_ClearITPendingBit(_Timer, TIM_IT_Update);
		}

		bool Timer::triggered()
		{
			//is this timer generate the interrupt ?
			if (TIM_GetITStatus(_Timer, TIM_IT_Update) == SET)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void Timer::enable()
		{
			//reset counter
			TIM_SetCounter(_Timer, 0);

			//enable
			TIM_Cmd(_Timer, ENABLE);
		}

		void Timer::disable()
		{
			//disable timer
			TIM_Cmd(_Timer, DISABLE);
		}

		void Timer::setPeriod(uint16_t Period)
		{

			if (_Delay == ::timer::SubdivisionDelayMs)
			{
				if (Period > 0x7FFF)
				{
					//Period * 2 cannot be represented with uint16_t
					//TODO: generate error
					return;
				}

				//readjust delay for ms
				Period = Period * 2;
			}

			//update period
			TIM_SetAutoreload(_Timer, Period);

			//disable timer interrupt on update event
			TIM_ITConfig(_Timer, TIM_IT_Update, DISABLE);

			//update event to reload period
			TIM_GenerateEvent(_Timer, TIM_EventSource_Update);

			//clear interrupt
			TIM_ClearITPendingBit(_Timer, TIM_IT_Update);

			//reenable timer for interrupt on update event
			TIM_ITConfig(_Timer, TIM_IT_Update, ENABLE);

		}


		#define TIMER_IRQ_CALLBACK(TimX) void TIM##TimX##_IRQHandler()									\
											{																\
												gpTimer[TimX]->_callback();					\
												gpTimer[TimX]->clear(); /* clear interrupt */\
											}

		extern "C"
		{
			TIMER_IRQ_CALLBACK(2)
			TIMER_IRQ_CALLBACK(3)
#ifdef STM32F1XX
			TIMER_IRQ_CALLBACK(4)
#endif //STM32F1XX
		}


	} //namespace timer

} //namespace stm32

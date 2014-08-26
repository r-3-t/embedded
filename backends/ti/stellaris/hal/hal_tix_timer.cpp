#include <timer.h>

#include <TimerInterface.hpp>
#include <ClockInterface.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TIX_TIMER_COUNT							6

namespace tix {

	namespace timer
	{

		static ::tix::timer::Timer* gpTimer[TIX_TIMER_COUNT];

	//		#define TIMER_IRQ_CALLBACK(TimX) void TIM##TimX##_IRQHandler()									\
	//											{																\
	//												gpTimer[TimX]->_callback();					\
	//												gpTimer[TimX]->clear(); /* clear interrupt */\
	//											}
	//
	//		extern "C"
	//		{
	//			TIMER_IRQ_CALLBACK(2)
	//			TIMER_IRQ_CALLBACK(3)
	//			TIMER_IRQ_CALLBACK(4)
	//		}

		extern "C"
		{
		void WTIMER0_Handler()
		{
			gpTimer[0]->_callback();
			gpTimer[0]->clear();
		}

		} //extern "C"


		unsigned long get_timer_base_from_id(::timer::Timer_Id TimerId)
		{
			switch (TimerId)
			{
			//64 bits only
			case 1:
				return WTIMER0_BASE;
				break;
			case 2:
				return WTIMER1_BASE;
				break;
			case 3:
				return WTIMER2_BASE;
				break;
			case 4:
				return WTIMER3_BASE;
				break;
			case 5:
				return WTIMER4_BASE;
				break;
			case 6:
				return WTIMER5_BASE;
				break;

			}

			fprintf(stderr, "Invalid Timer_Id : %i !\n", TimerId);
			abort();
		}

		unsigned long get_timer_clock_from_id(::timer::Timer_Id TimerId)
		{
			switch (TimerId)
			{
			//64 bits only
			case 1:
				return SYSCTL_PERIPH_WTIMER0;
				break;
			case 2:
				return SYSCTL_PERIPH_WTIMER1;
				break;
			case 3:
				return SYSCTL_PERIPH_WTIMER2;
				break;
			case 4:
				return SYSCTL_PERIPH_WTIMER3;
				break;
			case 5:
				return SYSCTL_PERIPH_WTIMER4;
				break;
			case 6:
				return SYSCTL_PERIPH_WTIMER5;
				break;

			}

			fprintf(stderr, "Invalid Timer_Id : %i !\n", TimerId);
			abort();
		}


		Timer::Timer(::timer::Timer_Id TimerId, ::timer::SubdivisionDelay_T Delay, uint16_t Period, ::timer::callback_T callback)
		{

			assert( (TimerId - 1) < sizeof(gpTimer)/sizeof(Timer*));
			gpTimer[TimerId - 1] = this;

			this->_TimerId = TimerId;
			this->_TimerBase = get_timer_base_from_id(TimerId);
			this->_callback = callback;
			this->_SubdivisionDelay = Delay;
			this->_Period = Period;

			this->_configured = false;

		}

		void Timer::configure()
		{
			this->_configured = true;

			//enable clock
			SysCtlPeripheralEnable(get_timer_clock_from_id(this->_TimerId));

			//configure for periodic interrupt
			TimerConfigure(this->_TimerBase, TIMER_CFG_PERIODIC);

			//configure period
			this->setPeriod(this->_Period);

			//register interrupt handler
			TimerIntRegister(this->_TimerBase, TIMER_BOTH, WTIMER0_Handler);

			//enable interrupt on counter overflow
			TimerIntEnable(this->_TimerBase, TIMER_TIMA_TIMEOUT);
		}

		void Timer::clear()
		{
			TimerIntClear(this->_TimerBase, TIMER_TIMA_TIMEOUT);
		}

		bool Timer::triggered()
		{
			if (this->_configured != true)
			{
				this->configure();
			}

			if (TimerIntStatus(this->_TimerBase, false) & TIMER_TIMA_TIMEOUT == TIMER_TIMA_TIMEOUT)
			{
				return true;
			}
		}

		void Timer::enable()
		{
			if (this->_configured != true)
			{
				this->configure();
			}
			TimerEnable(this->_TimerBase, TIMER_BOTH);
		}

		void Timer::disable()
		{
			if (this->_configured != true)
			{
				this->configure();
			}

			TimerDisable(this->_TimerBase, TIMER_BOTH);
		}

		void Timer::setPeriod(uint16_t Period)
		{
			if (this->_configured != true)
			{
				this->configure();
			}

			if (this->_SubdivisionDelay == ::timer::SubdivisionDelayUs)
			{
				//64 bits timer
				TimerLoadSet64(this->_TimerBase, Period * ::clock::getTickPerUs());
			}
			else if (this->_SubdivisionDelay == ::timer::SubdivisionDelayMs)
			{
				//64 bits timer
				TimerLoadSet64(this->_TimerBase, Period * ::clock::getTickPerMs());
			}
			else
			{
				fprintf(stderr, "Invalid SubdivisionDelay_T !\n");
				abort();
			}
		}

	} //namespace timer

} //namespace tix

namespace timer
{

	typedef ::tix::timer::Timer						ConcreteTimer;

}//namespace timer



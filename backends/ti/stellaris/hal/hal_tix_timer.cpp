#include <timer.h>
#include <interrupt.h>
#include <hw_memmap.h>
#include <hw_ints.h>

#include <TimerInterface.hpp>
#include <ClockInterface.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TIX_TIMER_COUNT							6

namespace tix {

	namespace timer
	{

		static const unsigned long g_ppulTimerIntMap[][2] =
		{
			{ TIMER0_BASE, INT_TIMER0A },
			{ TIMER1_BASE, INT_TIMER1A },
			{ TIMER2_BASE, INT_TIMER2A },
			{ TIMER3_BASE, INT_TIMER3A },
			{ TIMER4_BASE, INT_TIMER4A },
			{ TIMER5_BASE, INT_TIMER5A },
			{ WTIMER0_BASE, INT_WTIMER0A },
			{ WTIMER1_BASE, INT_WTIMER1A },
			{ WTIMER2_BASE, INT_WTIMER2A },
			{ WTIMER3_BASE, INT_WTIMER3A },
			{ WTIMER4_BASE, INT_WTIMER4A },
			{ WTIMER5_BASE, INT_WTIMER5A },
		};

		static long
		TimerIntNumberGet(unsigned long ulBase)
		{
			unsigned long ulIdx;

			//
			// Loop through the table that maps timer base addresses to interrupt
			// numbers.
			//
			for(ulIdx = 0; ulIdx < (sizeof(g_ppulTimerIntMap) /
									sizeof(g_ppulTimerIntMap[0])); ulIdx++)
			{
				//
				// See if this base address matches.
				//
				if(g_ppulTimerIntMap[ulIdx][0] == ulBase)
				{
					//
					// Return the corresponding interrupt number.
					//
					return(g_ppulTimerIntMap[ulIdx][1]);
				}
			}

			//
			// The base address could not be found, so return an error.
			//
			return(-1);
		}


		static ::tix::timer::Timer* gpTimer[TIX_TIMER_COUNT];

			#define TIMER_IRQ_CALLBACK(TimX) void WTIMER##TimX##_Handler()									\
												{																\
													gpTimer[TimX]->_callback();					\
													gpTimer[TimX]->clear(); /* clear interrupt */\
												}

			extern "C"
			{
				TIMER_IRQ_CALLBACK(0)
				TIMER_IRQ_CALLBACK(1)
				TIMER_IRQ_CALLBACK(2)
				TIMER_IRQ_CALLBACK(3)
				TIMER_IRQ_CALLBACK(4)
				TIMER_IRQ_CALLBACK(5)
			}


		unsigned long get_timer_base_from_id(::timer::Timer_Id TimerId, bool wide)
		{
			if (wide == true)
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
			}
			else
			{
				switch (TimerId)
				{
				//32 bits only
				case 1:
					return TIMER0_BASE;
					break;
				case 2:
					return TIMER1_BASE;
					break;
				case 3:
					return TIMER2_BASE;
					break;
				case 4:
					return TIMER3_BASE;
					break;
				case 5:
					return TIMER4_BASE;
					break;
				case 6:
					return TIMER5_BASE;
					break;

				}
			}

			fprintf(stderr, "Invalid Timer_Id : %i !\n", TimerId);
			abort();
		}

		unsigned long get_timer_clock_from_id(::timer::Timer_Id TimerId, bool wide)
		{
			if (wide == true)
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

			}
			else
			{
				switch (TimerId)
				{
				//32 bits only
				case 1:
					return SYSCTL_PERIPH_TIMER0;
					break;
				case 2:
					return SYSCTL_PERIPH_TIMER1;
					break;
				case 3:
					return SYSCTL_PERIPH_TIMER2;
					break;
				case 4:
					return SYSCTL_PERIPH_TIMER3;
					break;
				case 5:
					return SYSCTL_PERIPH_TIMER4;
					break;
				case 6:
					return SYSCTL_PERIPH_TIMER5;
					break;
				}
			}

			fprintf(stderr, "Invalid Timer_Id : %i !\n", TimerId);
			abort();
		}

		unsigned long get_timer_clock_from_base(unsigned long TimerBase)
		{
			switch (TimerBase)
			{
			//64 bits only
			case WTIMER0_BASE:
				return SYSCTL_PERIPH_WTIMER0;
				break;
			case WTIMER1_BASE:
				return SYSCTL_PERIPH_WTIMER1;
				break;
			case WTIMER2_BASE:
				return SYSCTL_PERIPH_WTIMER2;
				break;
			case WTIMER3_BASE:
				return SYSCTL_PERIPH_WTIMER3;
				break;
			case WTIMER4_BASE:
				return SYSCTL_PERIPH_WTIMER4;
				break;
			case WTIMER5_BASE:
				return SYSCTL_PERIPH_WTIMER5;
				break;
			case TIMER0_BASE:
				return SYSCTL_PERIPH_TIMER0;
				break;
			case TIMER1_BASE:
				return SYSCTL_PERIPH_TIMER1;
				break;
			case TIMER2_BASE:
				return SYSCTL_PERIPH_TIMER2;
				break;
			case TIMER3_BASE:
				return SYSCTL_PERIPH_TIMER3;
				break;
			case TIMER4_BASE:
				return SYSCTL_PERIPH_TIMER4;
				break;
			case TIMER5_BASE:
				return SYSCTL_PERIPH_TIMER5;
				break;
			}

			fprintf(stderr, "Invalid TimerBase : %i !\n", TimerBase);
			abort();
		}


		Timer::Timer(::timer::Timer_Id TimerId, ::timer::SubdivisionDelay_T Delay, uint16_t Period, ::timer::callback_T callback, Priority_T Priority)
		{

			assert( (TimerId - 1) < sizeof(gpTimer)/sizeof(Timer*));
			gpTimer[TimerId - 1] = this;

			this->_TimerId = TimerId;
			this->_TimerBase = get_timer_base_from_id(TimerId, true);
			this->_callback = callback;
			this->_SubdivisionDelay = Delay;
			this->_Period = Period;
			this->_Priority = Priority;

			this->_configured = false;

		}

		void Timer::configure()
		{
			this->_configured = true;

			//enable clock
			SysCtlPeripheralEnable(get_timer_clock_from_id(this->_TimerId, true));

			//configure for periodic interrupt
			TimerConfigure(this->_TimerBase, TIMER_CFG_PERIODIC);

			//configure period
			this->setPeriod(this->_Period);

			switch(this->_TimerId)
			{
			case 1:
				//register interrupt handler
				TimerIntRegister(this->_TimerBase, TIMER_BOTH, WTIMER0_Handler);
				break;
			case 2:
				//register interrupt handler
				TimerIntRegister(this->_TimerBase, TIMER_BOTH, WTIMER1_Handler);
				break;
			case 3:
				//register interrupt handler
				TimerIntRegister(this->_TimerBase, TIMER_BOTH, WTIMER2_Handler);
				break;
			case 4:
				//register interrupt handler
				TimerIntRegister(this->_TimerBase, TIMER_BOTH, WTIMER3_Handler);
				break;
			case 5:
				//register interrupt handler
				TimerIntRegister(this->_TimerBase, TIMER_BOTH, WTIMER4_Handler);
				break;
			case 6:
				//register interrupt handler
				TimerIntRegister(this->_TimerBase, TIMER_BOTH, WTIMER5_Handler);
				break;
			}

			//set priority
			IntPrioritySet(TimerIntNumberGet(this->_TimerBase), this->_Priority);

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



#include "hal_tix_edge_time.hpp"

#include "hal_tix_timer.hpp"

#include <stdlib.h>

#include <timer.h>
#include <interrupt.h>
#include <hw_memmap.h>
#include <hw_ints.h>
#include <hw_timer.h>
#include <hw_types.h>

#include <PinoutInterface.hpp>
#include <TimerInterface.hpp>
#include <Priority.hpp>

namespace tix {

	namespace edge_time
	{

		static ::tix::edge_time::EdgeTime* gpTimer[TIX_TIMER_COUNT][2];
		static ::tix::edge_time::EdgeTime* gpWTimer[TIX_WTIMER_COUNT][2];

		#define EDGE_TIME_IRQ_CALLBACK(TimX, SubTimX) void EDGE_TIME_##TimX##_##SubTimX##_Handler()									\
											{																\
												gpTimer[TimX][SubTimX]->_callback();					\
												gpTimer[TimX][SubTimX]->_save_ticks();					\
												gpTimer[TimX][SubTimX]->clear(); /* clear interrupt */\
											}

		#define WEDGE_TIME_IRQ_CALLBACK(TimX, SubTimX) void WEDGE_TIME_##TimX##_##SubTimX##_Handler()									\
									{																\
										gpWTimer[TimX][SubTimX]->_callback();					\
										gpWTimer[TimX][SubTimX]->_save_ticks();					\
										gpWTimer[TimX][SubTimX]->clear(); /* clear interrupt */\
									}

		extern "C"
		{
		EDGE_TIME_IRQ_CALLBACK(0,0)
		EDGE_TIME_IRQ_CALLBACK(0,1)
		EDGE_TIME_IRQ_CALLBACK(1,0)
		EDGE_TIME_IRQ_CALLBACK(1,1)
		EDGE_TIME_IRQ_CALLBACK(2,0)
		EDGE_TIME_IRQ_CALLBACK(2,1)
		EDGE_TIME_IRQ_CALLBACK(3,0)
		EDGE_TIME_IRQ_CALLBACK(3,1)
		EDGE_TIME_IRQ_CALLBACK(4,0)
		EDGE_TIME_IRQ_CALLBACK(4,1)
		EDGE_TIME_IRQ_CALLBACK(5,0)
		EDGE_TIME_IRQ_CALLBACK(5,1)

		WEDGE_TIME_IRQ_CALLBACK(0,0)
		WEDGE_TIME_IRQ_CALLBACK(0,1)
		WEDGE_TIME_IRQ_CALLBACK(1,0)
		WEDGE_TIME_IRQ_CALLBACK(1,1)
		WEDGE_TIME_IRQ_CALLBACK(2,0)
		WEDGE_TIME_IRQ_CALLBACK(2,1)
		WEDGE_TIME_IRQ_CALLBACK(3,0)
		WEDGE_TIME_IRQ_CALLBACK(3,1)
		WEDGE_TIME_IRQ_CALLBACK(4,0)
		WEDGE_TIME_IRQ_CALLBACK(4,1)
		WEDGE_TIME_IRQ_CALLBACK(5,0)
		WEDGE_TIME_IRQ_CALLBACK(5,1)
		}

		EdgeTime::EdgeTime(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId, ::timer::callback_T callback, Priority_T priority): 	_GPIOId(GPIOId),
																																	_PINId(PINId),
																																	_callback(callback),
																																	_Priority(priority),
																																	_TimerBase(::tix::timer::get_timer_base_from_pin(GPIOId, PINId)),
																																	_TimerConfig(::tix::timer::get_timer_config_from_pin(GPIOId, PINId)),
																																	_configured(false)
		{

		}

		unsigned long get_edge_time_config_from_pin(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId)
		{
			if ((PINId % 2) == 0)
			{
				return TIMER_CFG_A_CAP_TIME_UP;
			}
			else
			{
				return TIMER_CFG_B_CAP_TIME_UP;
			}
		}

		unsigned long get_edge_time_event_from_pin(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId)
		{
			if ((PINId % 2) == 0)
			{
				return TIMER_CAPA_EVENT;
			}
			else
			{
				return TIMER_CAPB_EVENT;
			}
		}

		void EdgeTime::configure()
		{
			unsigned long PinConfig;
			unsigned long GPIOPeripheral;
			// the gpio used
			unsigned long GPIO_Port;
			unsigned char GPIO_Pin;			// the selected pin

			unsigned long Ctl;
			unsigned long Timer_O_TnMR;

			this->_configured = true;

			switch (this->_GPIOId)
			{
			//port B
			case 2:
				switch (this->_PINId)
				{
				case 0:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB0_T2CCP0;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_0;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_2_0_Handler);
					gpTimer[2][0] = this;
					break;
				case 1:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB1_T2CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_1;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_2_1_Handler);
					gpTimer[2][1] = this;
					break;
				case 2:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB2_T3CCP0;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_2;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_3_0_Handler);
					gpTimer[3][0] = this;
					break;
				case 3:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB3_T3CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_3;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_3_1_Handler);
					gpTimer[3][1] = this;
					break;
				case 4:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB4_T1CCP0;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_4;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_1_0_Handler);
					gpTimer[1][0] = this;
					break;
				case 5:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB5_T1CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_5;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_1_1_Handler);
					gpTimer[1][1] = this;
					break;
				case 6:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB6_T0CCP0;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_6;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_0_0_Handler);
					gpTimer[0][0] = this;
					break;
				case 7:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB7_T0CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_7;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_0_1_Handler);
					gpTimer[0][1] = this;
					break;
				}
				break;
			//port C
			case 3:
				switch (this->_PINId)
				{
				case 0:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC0_T4CCP0;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_0;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_4_0_Handler);
					gpTimer[4][0] = this;
					break;
				case 1:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC1_T4CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_1;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_4_1_Handler);
					gpTimer[4][1] = this;
					break;
				case 2:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC2_T5CCP0;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_2;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_5_0_Handler);
					gpTimer[5][0] = this;
					break;
				case 3:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC3_T5CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_3;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_5_0_Handler);
					gpTimer[5][1] = this;
					break;
				case 4:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC4_WT0CCP0;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_4;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, WEDGE_TIME_0_0_Handler);
					gpWTimer[0][0] = this;
					break;
				case 5:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC5_WT0CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_5;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, WEDGE_TIME_0_1_Handler);
					gpWTimer[0][1] = this;
					break;
				case 6:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC6_WT1CCP0;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_6;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, WEDGE_TIME_1_0_Handler);
					gpWTimer[1][0] = this;
					break;
				case 7:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC7_WT1CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_7;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, WEDGE_TIME_1_1_Handler);
					gpWTimer[1][1] = this;
					break;
				}
				break;
			//port D
			case 4:
				switch (this->_PINId)
				{
				case 0:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD0_WT2CCP0;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_0;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, WEDGE_TIME_2_0_Handler);
					gpWTimer[2][0] = this;
					break;
				case 1:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD1_WT2CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_1;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, WEDGE_TIME_2_1_Handler);
					gpWTimer[2][1] = this;
					break;
				case 2:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD2_WT3CCP0;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_2;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, WEDGE_TIME_3_0_Handler);
					gpWTimer[3][0] = this;
					break;
				case 3:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD3_WT3CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_3;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, WEDGE_TIME_3_1_Handler);
					gpWTimer[3][1] = this;
					break;
				case 4:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD4_WT4CCP0;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_4;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, WEDGE_TIME_4_0_Handler);
					gpWTimer[4][0] = this;
					break;
				case 5:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD5_WT4CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_5;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, WEDGE_TIME_4_1_Handler);
					gpWTimer[4][1] = this;
					break;
				case 6:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD6_WT5CCP0;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_6;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, WEDGE_TIME_5_0_Handler);
					gpWTimer[5][0] = this;
					break;
				case 7:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD7_WT5CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_7;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, WEDGE_TIME_5_1_Handler);
					gpWTimer[5][1] = this;
					break;
				}
				break;
			//port F
			case 6:
				switch (this->_PINId)
				{
				case 0:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOF;
					PinConfig = GPIO_PF0_T0CCP0;
					GPIO_Port = GPIO_PORTF_BASE;
					GPIO_Pin = GPIO_PIN_0;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_0_0_Handler);
					gpTimer[0][0] = this;
					break;
				case 1:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOF;
					PinConfig = GPIO_PF1_T0CCP1;
					GPIO_Port = GPIO_PORTF_BASE;
					GPIO_Pin = GPIO_PIN_1;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_0_1_Handler);
					gpTimer[0][1] = this;
					break;
				case 2:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOF;
					PinConfig = GPIO_PF2_T1CCP0;
					GPIO_Port = GPIO_PORTF_BASE;
					GPIO_Pin = GPIO_PIN_2;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_1_0_Handler);
					gpTimer[1][0] = this;
					break;
				case 3:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOF;
					PinConfig = GPIO_PF3_T1CCP1;
					GPIO_Port = GPIO_PORTF_BASE;
					GPIO_Pin = GPIO_PIN_3;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_B, EDGE_TIME_1_1_Handler);
					gpTimer[1][1] = this;
					break;
				case 4:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOF;
					PinConfig = GPIO_PF4_T2CCP0;
					GPIO_Port = GPIO_PORTF_BASE;
					GPIO_Pin = GPIO_PIN_4;
					//register interrupt handler
					TimerIntRegister(this->_TimerBase, TIMER_A, EDGE_TIME_2_0_Handler);
					gpTimer[2][0] = this;
					break;
				}
				break;
				abort();
			}


			//
			// Enable the peripherals
			//
			SysCtlPeripheralEnable(GPIOPeripheral);

			//
			// Set GPIO for EdgeTimer pin.
			//
			GPIOPinConfigure(PinConfig);
			GPIOPinTypeTimer(GPIO_Port, GPIO_Pin);

			//enable clock
			SysCtlPeripheralEnable(::tix::timer::get_timer_clock_from_base(this->_TimerBase));

			//get previous control flags
			Ctl = HWREG(this->_TimerBase + TIMER_O_CTL);

			if (_TimerConfig == TIMER_A)
			{
				//we save timer B config before erased by TimerConfigure
				Timer_O_TnMR = HWREG(this->_TimerBase + TIMER_O_TBMR);
			}
			else //TIMER_B
			{
				//we save timer A config before erased by TimerConfigure
				Timer_O_TnMR = HWREG(this->_TimerBase + TIMER_O_TAMR);

			}

			//configure for periodic interrupt
			TimerConfigure(this->_TimerBase, TIMER_CFG_SPLIT_PAIR | get_edge_time_config_from_pin(_GPIOId, _PINId));

			if (_TimerConfig == TIMER_A)
			{
				//we restore timer B config
				HWREG(this->_TimerBase + TIMER_O_TBMR) = Timer_O_TnMR;
			}
			else //TIMER_B
			{
				//we restore timer A config
				HWREG(this->_TimerBase + TIMER_O_TAMR) = Timer_O_TnMR;

			}

			//reapply previous control
			HWREG(this->_TimerBase + TIMER_O_CTL) = Ctl;

			//invert output
			TimerControlEvent(this->_TimerBase, this->_TimerConfig, TIMER_EVENT_BOTH_EDGES);

			//set priority
			IntPrioritySet(::tix::timer::TimerIntNumberGet(this->_TimerBase), this->_Priority);

			//enable interrupt on counter overflow
			TimerIntEnable(this->_TimerBase, get_edge_time_event_from_pin(_GPIOId, _PINId));

		}

		void EdgeTime::clear()
		{
			TimerIntClear(this->_TimerBase, get_edge_time_event_from_pin(_GPIOId, _PINId));
		}

		void EdgeTime::enable()
		{
			if (!_configured)
			{
				this->configure();
			}
			TimerEnable(this->_TimerBase, this->_TimerConfig);
		}

		void EdgeTime::disable()
		{
			if (!_configured)
			{
				this->configure();
			}
			TimerDisable(this->_TimerBase, this->_TimerConfig);
		}

		uint32_t EdgeTime::get_last_record()
		{
			return (this->_get_ticks() - _ticks_record);
		}

		void EdgeTime::_save_ticks()
		{
			_ticks_record = this->_get_ticks();
		}

		uint32_t EdgeTime::_get_ticks()
		{
			return (uint32_t)TimerValueGet(this->_TimerBase, this->_TimerConfig);
		}



	} //namesapce edge_time

} //namespace tix

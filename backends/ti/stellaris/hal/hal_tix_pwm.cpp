#include <timer.h>
#include <interrupt.h>
#include <hw_memmap.h>
#include <hw_ints.h>

#include <PwmInterface.hpp>
#include <TimerInterface.hpp>
#include <ClockInterface.hpp>

#include "hal_tix_timer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TIX_TIMER_COUNT							6

namespace tix {

	namespace pwm
	{

		unsigned long get_timer_base_from_pin(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId)
		{
			switch (GPIOId)
			{
			//port B
			case 2:
				switch (PINId)
				{
				case 0:
				case 1:
					return TIMER2_BASE;
					break;
				case 2:
				case 3:
					return TIMER3_BASE;
					break;
				case 4:
				case 5:
					return TIMER1_BASE;
					break;
				case 6:
				case 7:
					return TIMER0_BASE;
					break;
				}
				break;
			//port C
			case 3:
				switch (PINId)
				{
				case 0:
				case 1:
					return TIMER4_BASE;
					break;
				case 2:
				case 3:
					return TIMER5_BASE;
					break;
				case 4:
				case 5:
					return WTIMER0_BASE;
					break;
				case 6:
				case 7:
					return WTIMER1_BASE;
					break;
				}
				break;
			//port D
			case 4:
				switch (PINId)
				{
				case 0:
				case 1:
					return WTIMER2_BASE;
					break;
				case 2:
				case 3:
					return WTIMER3_BASE;
					break;
				case 4:
				case 5:
					return WTIMER4_BASE;
					break;
				case 6:
				case 7:
					return WTIMER5_BASE;
					break;
				}
				break;

			}
			abort();
		}

		unsigned long get_pwm_config_from_pin(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId)
		{
			if ((PINId % 2) == 0)
			{
				return TIMER_CFG_A_PWM;
			}
			else
			{
				return TIMER_CFG_B_PWM;
			}
		}

		unsigned long get_timer_config_from_pin(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId)
		{
			if ((PINId % 2) == 0)
			{
				return TIMER_A;
			}
			else
			{
				return TIMER_B;
			}
		}

		bool is_wide_timer(unsigned long TimerBase)
		{
			if ((TimerBase == WTIMER0_BASE) || (TimerBase == WTIMER1_BASE) || (TimerBase == WTIMER2_BASE) || (TimerBase == WTIMER3_BASE) || (TimerBase == WTIMER4_BASE) || (TimerBase == WTIMER5_BASE))
			{
				return true;
			}
			return false;
		}

		Pwm::Pwm(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId, uint32_t Frequency, uint32_t MaxDuty)
		{
			this->_TimerBase = get_timer_base_from_pin(GPIOId, PINId);
			this->_Frequency = Frequency;
			this->_PeriodUs = (1000000/Frequency);
			this->_MaxDuty = MaxDuty;
			this->_PwmConfig = get_pwm_config_from_pin(GPIOId, PINId);
			this->_TimerConfig = get_timer_config_from_pin(GPIOId, PINId);
			this->_TickCountForFrequency = 0;
			this->_GPIOId = GPIOId;
			this->_PINId = PINId;

						this->_configured = false;

		}

		void Pwm::configure()
		{

			unsigned long PinConfig;
			unsigned long GPIOPeripheral;
			// the gpio used
			unsigned long GPIO_Port;
			unsigned char GPIO_Pin;			// the selected pin

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
					break;
				case 1:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB1_T2CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_1;
					break;
				case 2:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB2_T3CCP0;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_2;
					break;
				case 3:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB3_T3CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_3;
					break;
					break;
				case 4:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB4_T1CCP0;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_4;
					break;
				case 5:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB5_T1CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_5;
					break;
				case 6:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB6_T0CCP0;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_6;
					break;
				case 7:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOB;
					PinConfig = GPIO_PB7_T0CCP1;
					GPIO_Port = GPIO_PORTB_BASE;
					GPIO_Pin = GPIO_PIN_7;
					break;
				default:
					abort();
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
					break;
				case 1:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC1_T4CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_1;
					break;
				case 2:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC2_T5CCP0;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_2;
					break;
				case 3:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC3_T5CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_3;
					break;
				case 4:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC4_WT0CCP0;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_4;
					break;
				case 5:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC5_WT0CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_5;
					break;
				case 6:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC6_WT1CCP0;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_6;
					break;
				case 7:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOC;
					PinConfig = GPIO_PC7_WT1CCP1;
					GPIO_Port = GPIO_PORTC_BASE;
					GPIO_Pin = GPIO_PIN_7;
					break;
				default:
					abort();
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
					break;
				case 1:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD1_WT2CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_1;
					break;
				case 2:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD2_WT3CCP0;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_2;
					break;
				case 3:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD3_WT3CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_3;
					break;
				case 4:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD4_WT4CCP0;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_4;
					break;
				case 5:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD5_WT4CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_5;
					break;
				case 6:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD6_WT5CCP0;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_6;
					break;
				case 7:
					//configure GPIO pin
					GPIOPeripheral = SYSCTL_PERIPH_GPIOD;
					PinConfig = GPIO_PD7_WT5CCP1;
					GPIO_Port = GPIO_PORTD_BASE;
					GPIO_Pin = GPIO_PIN_7;
					break;
				default:
					abort();
				}
				break;
			default:
				abort();
			}

			//
			// Enable the peripherals
			//
			SysCtlPeripheralEnable(GPIOPeripheral);

			//
			// Set GPIO for PWM pin.
			//
			GPIOPinConfigure(PinConfig);
			GPIOPinTypeTimer(GPIO_Port, GPIO_Pin);


			//calculate number of ticks to represent Frequency
			//(1/Frequency) /*s*/ / (1/SysCtlClockGet())
			this->_TickCountForFrequency = SysCtlClockGet() / this->_Frequency;

			//enable clock
			SysCtlPeripheralEnable(::tix::timer::get_timer_clock_from_base(this->_TimerBase));

			//configure for periodic interrupt
			TimerConfigure(this->_TimerBase, TIMER_CFG_SPLIT_PAIR | this->_PwmConfig);

			//invert output
			TimerControlLevel(this->_TimerBase, this->_TimerConfig, true);

			if (is_wide_timer(this->_TimerBase) == true)
			{
				this->_prescalerFactor = 1;
			}
			else
			{
				//now we try to scale number of ticks to 16 bits counter
				this->_prescalerFactor = (this->_TickCountForFrequency/65536) + 1; //+1 around upper

				//TODO: this->_prescalerFactor > 256 -> failed

				//now we deduce the granularity time (in ns)
				this->_TimeByTickPrescaleNs = (1000*this->_prescalerFactor) / ((SysCtlClockGet()/1000000));

				//configure prescaler
				TimerPrescaleSet(this->_TimerBase, this->_TimerConfig, this->_prescalerFactor - 1);
			}

			//configure period ticks
			TimerLoadSet(this->_TimerBase, this->_TimerConfig, this->_TickCountForFrequency / this->_prescalerFactor);


		}

		void Pwm::setDuty(uint32_t Duty)
		{
			unsigned long value;

			if (this->_configured != true)
			{
				this->configure();
			}

			value = this->_TickCountForFrequency * Duty / this->_MaxDuty;

			if (is_wide_timer(this->_TimerBase) == true)
			{
				TimerMatchSet(this->_TimerBase, this->_TimerConfig, value);
			}
			else
			{
				TimerMatchSet(this->_TimerBase, this->_TimerConfig, value & 0xffff);
				TimerPrescaleMatchSet(this->_TimerBase, this->_TimerConfig, (value >> 16) & 0xffff);
			}

		}

		void Pwm::enable()
		{
			if (this->_configured != true)
			{
				this->configure();
			}
			TimerEnable(this->_TimerBase, this->_TimerConfig);
		}

		void Pwm::disable()
		{
			if (this->_configured != true)
			{
				this->configure();
			}

			TimerDisable(this->_TimerBase, this->_TimerConfig);
		}

	} //namespace pwm

} //namespace tix

namespace timer
{

	typedef ::tix::timer::Timer						ConcreteTimer;

}//namespace timer



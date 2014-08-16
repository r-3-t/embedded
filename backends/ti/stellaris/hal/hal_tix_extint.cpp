#include <string.h>
#include <hw_types.h>
#include <hw_memmap.h>
#include <ExtintInterface.hpp>
#include <PinoutInterface.hpp>
#include <gpio.h>
#include <interrupt.h>
#include <hw_ints.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TIX_EXTINT_MAX_PORT_COUNT				6
#define TIX_EXTINT_MAX_PIN_COUNT				8

namespace tix
{

	namespace extint
	{
		Extint* 	gpExtint[TIX_EXTINT_MAX_PORT_COUNT][TIX_EXTINT_MAX_PIN_COUNT];

#define EXTINT_HANLDER(ExtintX) void EXTINT##ExtintX##_Handler()									\
		{																							\
			int i;																					\
			/*search interrupt pin source*/															\
			for (i = 0; i < TIX_EXTINT_MAX_PIN_COUNT; i++)											\
			{																						\
				/*valid entrie*/																	\
				if (gpExtint[ExtintX - 1][i] != 0)													\
				{																					\
					if (gpExtint[ExtintX - 1][i]->triggered() == true)								\
					{																				\
						gpExtint[ExtintX - 1][i]->clear();											\
						gpExtint[ExtintX - 1][i]->_callback();										\
						return;																		\
					}																				\
				}																					\
			}																						\
			return;																					\
		}

		extern "C"
		{
			EXTINT_HANLDER(1)
			EXTINT_HANLDER(2)
			EXTINT_HANLDER(3)
			EXTINT_HANLDER(4)
			EXTINT_HANLDER(5)
			EXTINT_HANLDER(6)

		}


		Extint::Extint(::pinout::Pin_id PINId, ::pinout::Gpio_id 	GPIOId, ::extint::InterruptTrigger_T Mode, ::extint::callback_T callback)
		{
			assert(PINId < sizeof(gpExtint)/sizeof(Extint*));

			gpExtint[GPIOId - 1][PINId] = this;

			this->_callback=callback;

			this->GpioPortBase = ::tix::gpio::get_GPIO_port_from_id(GPIOId);

			this->GpioPin = ::tix::gpio::get_GPIO_pin_from_id(PINId);

			::tix::gpio::configure_extint_pin(this->GpioPortBase, (unsigned char)this->GpioPin);

			switch (Mode){
			case ::extint::RisingTrigger:
				GPIOIntTypeSet(this->GpioPortBase, this->GpioPin, GPIO_RISING_EDGE);
				break;
			case ::extint::FallingTrigger:
				GPIOIntTypeSet(this->GpioPortBase, this->GpioPin, GPIO_FALLING_EDGE);
				break;
			case ::extint::RisingFallingTrigger:
				GPIOIntTypeSet(this->GpioPortBase, this->GpioPin, GPIO_BOTH_EDGES);
				break;
			default:
				fprintf(stderr, "Invalid trigger mode !\n");
				abort();
				break;
			}

			switch (GPIOId)
			{
			case 1:
				//register handler
				GPIOPortIntRegister(this->GpioPortBase, EXTINT1_Handler);
				break;
			case 2:
				//register handler
				GPIOPortIntRegister(this->GpioPortBase, EXTINT2_Handler);
				break;
			case 3:
				//register handler
				GPIOPortIntRegister(this->GpioPortBase, EXTINT3_Handler);
				break;
			case 4:
				//register handler
				GPIOPortIntRegister(this->GpioPortBase, EXTINT4_Handler);
				break;
			case 5:
				//register handler
				GPIOPortIntRegister(this->GpioPortBase, EXTINT5_Handler);
				break;
			case 6:
				//register handler
				GPIOPortIntRegister(this->GpioPortBase, EXTINT6_Handler);
				break;
			default:
				fprintf(stderr, "Invalid GPIOd !\n");
				abort();
				break;
			}

			//enable interrupts
			this->enable();

			IntMasterEnable();
		}

		void Extint::clear()
		{
			//clear pending IT
			GPIOPinIntClear(this->GpioPortBase, this->GpioPin);
		}

		bool Extint::triggered()
		{
			//is this external line generate the interrupt ?
			if ( (GPIOPinIntStatus(this->GpioPortBase, false) & this->GpioPin) == this->GpioPin)
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
			return ::tix::gpio::is_pin_high(this->GpioPortBase, this->GpioPin);
		}
		void Extint::disable()
		{
			GPIOPinIntDisable(this->GpioPortBase, this->GpioPin);
		}

		void Extint::enable()
		{
			GPIOPinIntEnable(this->GpioPortBase, this->GpioPin);
		}

	} /* namespace extint  */

} /* namespace tix  */


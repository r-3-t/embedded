#include "hal_tix_adc.hpp"

#include <adc.h>
#include <gpio.h>
#include <hw_memmap.h>

#include <stdio.h>
#include <stdlib.h>

#define TIXX_ADC_MAX_COUNT								12

#define DEFAULT_SS										3

namespace tix
{
	namespace adc
	{

		static ::tix::adc::Adc*				gpAdcs[TIXX_ADC_MAX_COUNT];

		extern "C"
		{
		void ADC0_SS0_Handler()
		{
			gpAdcs[0]->_callback(gpAdcs[0]->read());
		}
		}

		unsigned long get_port_for_adc(unsigned int id)
		{
			switch (id)
			{
			case 1:
				return GPIO_PORTE_BASE;
				break;
			case 2:
				return GPIO_PORTE_BASE;
				break;
			case 3:
				return GPIO_PORTE_BASE;
				break;
			case 4:
				return GPIO_PORTE_BASE;
				break;
			case 5:
				return GPIO_PORTD_BASE;
				break;
			case 6:
				return GPIO_PORTD_BASE;
				break;
			case 7:
				return GPIO_PORTD_BASE;
				break;
			case 8:
				return GPIO_PORTD_BASE;
				break;
			default:
				abort();
				break;
			}
		}

		unsigned char get_pin_for_adc(unsigned int id)
		{
			switch (id)
			{
			case 1:
				return (1 << 3);
				break;
			case 2:
				return (1 << 2);
				break;
			case 3:
				return (1 << 1);
				break;
			case 4:
				return (1 << 0);
				break;
			case 5:
				return (1 << 3);
				break;
			case 6:
				return (1 << 2);
				break;
			case 7:
				return (1 << 1);
				break;
			case 8:
				return (1 << 1);
				break;
			default:
				abort();
				break;
			}
		}

		unsigned char get_channel_for_adc(unsigned int id)
		{
			switch (id)
			{
			case 1:
				return ADC_CTL_CH0;
				break;
			case 2:
				return ADC_CTL_CH1;
				break;
			case 3:
				return ADC_CTL_CH2;
				break;
			case 4:
				return ADC_CTL_CH3;
				break;
			case 5:
				return ADC_CTL_CH4;
				break;
			case 6:
				return ADC_CTL_CH5;
				break;
			case 7:
				return ADC_CTL_CH6;
				break;
			case 8:
				return ADC_CTL_CH7;
				break;
			default:
				abort();
				break;
			}
		}

		Adc::Adc(unsigned int id, ::adc::AdcInterface::adc_callback_T callback)
		{
			this->_callback = callback;
			this->_port = get_port_for_adc(id);
			this->_pin = get_pin_for_adc(id);
			this->_channel = get_channel_for_adc(id);
			this->_adc_base = ADC0_BASE;
			this->_configured = false;

			gpAdcs[id - 1] = this;

		}

		void Adc::_configure()
		{
			if (this->_configured == true)
			{
				return;
			}
			this->_configured = true;

			SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //Enable ADC0 Peripheral

			GPIOPinTypeADC(this->_port, this->_pin);


			ADCSequenceDisable(this->_adc_base, DEFAULT_SS);

			ADCSequenceConfigure(this->_adc_base, DEFAULT_SS, ADC_TRIGGER_PROCESSOR, 0);

			ADCSequenceStepConfigure(this->_adc_base, DEFAULT_SS, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END); //Sequencer Step 0

			//register handler
			ADCIntRegister(this->_adc_base, DEFAULT_SS, ADC0_SS0_Handler);

			ADCSequenceEnable(this->_adc_base, DEFAULT_SS); //Enable ADC Sequence

			ADCIntEnable(this->_adc_base, DEFAULT_SS);



		}

		void Adc::eval()
		{
			this->_configure();
			ADCProcessorTrigger(this->_adc_base, DEFAULT_SS); // Trigger ADC Interrupt
		}

		uint32_t Adc::read()
		{
			uint32_t adc_values[8];

			this->_configure();

			ADCSequenceDataGet(this->_adc_base, DEFAULT_SS, adc_values); //Grab the Entire FIFO

			ADCIntClear(this->_adc_base, DEFAULT_SS);

			return adc_values[0];
		}

	}
}

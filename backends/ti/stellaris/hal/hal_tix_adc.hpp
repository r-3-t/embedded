#pragma once

#include <AdcInterface.hpp>

namespace tix
{
	namespace adc
	{
		class Adc : public ::adc::AdcInterface
		{
		public:
			Adc(unsigned int id, ::adc::AdcInterface::adc_callback_T callback);
			void eval();
			uint32_t read();

		private:
			void _configure();
			bool _configured;

			unsigned long _port;
			unsigned char _pin;
			unsigned long _channel;
			unsigned long _adc_base;
		};
	}
}

namespace adc
{
	typedef ::tix::adc::Adc					ConcreteAdc;
}

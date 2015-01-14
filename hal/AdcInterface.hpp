#pragma once

#include <types.hpp>

namespace adc
{
	class AdcInterface
	{
	public:
		typedef void (*adc_callback_T)(const uint32_t v);

		AdcInterface() {}
		AdcInterface(unsigned int, void (*)(uint32_t)) {}

		virtual void eval()								= 0;

		adc_callback_T _callback;

	};
}

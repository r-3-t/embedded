#pragma once

#include <pinout.hpp>
#include <functional>

namespace extint {

	//external interrupt callback function
	typedef void (*callback_T)();

	typedef enum {
		RisingTrigger = 0,
		FallingTrigger,
		RisingFallingTrigger,
	} InterruptTrigger_T;

	class Extint
	{
	public:
		Extint() {}

		virtual bool triggered () = 0;
		virtual void clear() = 0;

		callback_T _callback;

	};

	inline unsigned int	num_instance();

	inline void init_instance(::pinout::Pin_id PINId, ::pinout::Gpio_id 	GPIOId, InterruptTrigger_T Triiger, callback_T callback);

	inline Extint* get_instance(::pinout::Pin_id PINId);


}

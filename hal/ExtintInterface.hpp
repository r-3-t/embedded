#pragma once

namespace extint {

	//external interrupt callback function
	typedef void (*callback_T)();

	typedef enum {
		RisingTrigger = 0,
		FallingTrigger,
		RisingFallingTrigger,
	} InterruptTrigger_T;

	class ExtintInterface
	{
	public:
		ExtintInterface() {}

		virtual bool triggered () = 0;
		virtual void clear() = 0;
		virtual bool is_high() = 0;
		virtual void disable() = 0;
		virtual void enable() = 0;
		virtual void set_callback(::extint::callback_T callback) = 0;
		virtual void set_mode(::extint::InterruptTrigger_T mode) = 0;

		callback_T _callback;

	};

}

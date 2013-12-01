/*
 * pwm.hpp
 *
 *  Created on: 10 nov. 2013
 *      Author: val
 */
#pragma once

namespace timer {

	//external interrupt callback function
	typedef void (*callback_T)();

	//timer id
	typedef unsigned int			Timer_Id;

	//delay type for us and ms
	typedef enum
	{
		SubdivisionDelayMs = 0,
		SubdivisionDelayUs
	} SubdivisionDelay_T;

	class TimerInterface
	{
	public:
		TimerInterface() {}

		virtual bool triggered () = 0;
		virtual void clear() = 0;
		virtual void enable() = 0;
		virtual void disable() = 0;
		virtual void setPeriod(uint16_t Period) = 0;

		callback_T _callback;

	};

}


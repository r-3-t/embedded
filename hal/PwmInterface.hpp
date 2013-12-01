/*
 * pwm.hpp
 *
 *  Created on: 10 nov. 2013
 *      Author: val
 */
#pragma once

namespace pwm {

	class PwmInterface
	{
	public:
		PwmInterface() {}

		virtual void setDuty(uint32_t Duty) = 0;

	};

}


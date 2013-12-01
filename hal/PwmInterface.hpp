/*
 * pwm.hpp
 *
 *  Created on: 10 nov. 2013
 *      Author: val
 */

#ifndef PWM_HPP_
#define PWM_HPP_

namespace pwm {

	class Pwm
	{
	public:
		Pwm() {}

		virtual void setDuty(uint32_t Duty) = 0;

	};

	inline unsigned int	num_instance();

	inline void init_instance(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId, uint32_t Frequency, uint32_t MaxDuty);

	inline Pwm* get_instance(::pinout::Gpio_id GPIOId, ::pinout::Pin_id PINId);


}

#endif /* PWM_HPP_ */


#include <hal/pwm.hpp>
#include <hal/clock.hpp>

#define PWM_PORT							1
#define PWM_PIN								1

//------------------------------------------------------------------------------

int main(void)
{
	//initialize pwm with frequency of 100hz, duty can change from 0 to 100
	::pwm::init_instance(PWM_PORT, PWM_PIN, 100/*Hz*/, 100 /* From 0 to 100 */);

	::pwm::Pwm& pwm = *::pwm::get_instance(PWM_PORT, PWM_PIN);

	while (1)
	{
		pwm.setDuty(0); // 0%
		clock::msleep(1000);

		pwm.setDuty(25); // 25%
		clock::msleep(1000);

		pwm.setDuty(50); // 50%
		clock::msleep(1000);

		pwm.setDuty(75); // 75%
		clock::msleep(1000);

		pwm.setDuty(100); // 100%
		clock::msleep(1000);
	}
}

//------------------------------------------------------------------------------



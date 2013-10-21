#include <arduino_clock.hpp>
#include <hal/clock.hpp>

namespace arduino
{
	namespace clock
	{
		void delay(::types::uint32 delay)
		{
			::clock::msleep(delay);
		}

		void delayMicroseconds(::types::uint32 _delay)
		{
			//TODO: implement udelay
			return delay(1);
		}

		::types::uint32 millis()
		{
			return ::clock::getTickCount() / ::clock::getTickPerMs();
		}
	}
}

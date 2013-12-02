#include <arduino_clock.hpp>
#include <hal/Clock.hpp>

namespace arduino
{
	namespace clock
	{
		void delay(::types::uint32 delay)
		{
			::clock::msleep(delay);
		}

		void delayMicroseconds(::types::uint32 delay)
		{
			::clock::usleep(delay);
		}

		::types::uint32 millis()
		{
			return ::clock::getTickCount() / ::clock::getTickPerMs();
		}
	}
}

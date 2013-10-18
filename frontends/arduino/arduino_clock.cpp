#include <arduino_clock.hpp>
#include <hal/clock.hpp>

namespace arduino
{
	namespace clock
	{
		void delay(::types::uint32 delay)
		{
			::clock::usleep(delay);
		}
	}
}

#include <arduino_clock.hpp>
#include <ClockInterface.hpp>

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

		::types::uint32 getTickCount()
		{
			return ::clock::getTickCount();
		}

		::types::uint32 millis()
		{
			return ::clock::getTickCount() / ::clock::getTickPerMs();
		}

		::types::uint32 micros()
		{
			return ::clock::getTickCount() / ::clock::getTickPerUs();
		}
		
		::types::uint32 elapsedMicros(uint32_t PreviousTickCounter)
		{
			return ::clock::elapsedMicros(PreviousTickCounter);
		}
	}
}

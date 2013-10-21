#pragma once
#include <types.hpp>

namespace arduino
{
	namespace clock
	{
		void delay(::types::uint32 delay);

		void delayMicroseconds(::types::uint32 delay);

		::types::uint32 millis();
	}
}

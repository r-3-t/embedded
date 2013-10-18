#pragma once

namespace clock
{
	unsigned int getTickCount();
	constexpr unsigned int getTickPerMs(); 

	void msleep(unsigned int nTime);
}

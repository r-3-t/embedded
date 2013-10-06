#pragma once

namespace clock
{
	unsigned int getTickCount();
	constexpr unsigned int getTickPerMs(); 

	void usleep(unsigned int nTime);
}

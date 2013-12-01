#pragma once

namespace clock
{
	unsigned int getTickCount();
	unsigned int getTickPerMs();

	void msleep(unsigned int nTime);
	void usleep(unsigned int nTime);
}

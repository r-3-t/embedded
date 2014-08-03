#pragma once

namespace clock
{
	unsigned int getTickCount();
	unsigned int getTickPerMs();
	unsigned int getTickPerUs();

	void msleep(unsigned int nTime);
	void usleep(unsigned int nTime);
}

#pragma once

namespace clock
{
	unsigned int getTickCount();
	unsigned int getTickPerMs();
	unsigned int getTickPerUs();

	uint32_t elapsedMicros(unsigned int PreviousTickCounter);

	void msleep(unsigned int nTime);
	void usleep(unsigned int nTime);
}

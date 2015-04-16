#pragma once

namespace clock
{
	uint32_t getTickCount();
	unsigned int getTickPerMs();
	unsigned int getTickPerUs();

	uint32_t elapsedMicros(uint32_t PreviousTickCounter);
	uint32_t ticksToUs(uint32_t Ticks);

	void msleep(unsigned int nTime);
	void usleep(unsigned int nTime);
}

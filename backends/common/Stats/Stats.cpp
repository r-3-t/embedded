#include "Stats.hpp"


Stats::Stats()
{
	this->SumUsage = 0;
	this->CurrentUsage = 0;
	this->MaxUsage = 0;
	this->log_count = 0;
}

void Stats::log_memory_usage(int UsageSize)
{
	this->CurrentUsage = UsageSize;
	this->SumUsage += UsageSize;
	this->log_count++;
	if (UsageSize > this->MaxUsage)
	{
		this->MaxUsage = UsageSize;
	}

	return;
}

int Stats::getAverageUsage()
{
	return this->SumUsage/this->log_count;
}

int Stats::getMaxUsage()
{
	return this->MaxUsage;
}

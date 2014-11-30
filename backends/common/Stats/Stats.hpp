#pragma once

class Stats
{
public:
	Stats();

	virtual void log_memory_usage(int UsageSize);

	int getMaxUsage();
	int getAverageUsage();

private:
	int				CurrentUsage;
	int				log_count;
	int				SumUsage;
	int				MaxUsage;
};

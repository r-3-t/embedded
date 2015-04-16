#pragma once

namespace edge_time {

	class EdgeTimeInterface
	{
	public:
		EdgeTimeInterface() { }
		~EdgeTimeInterface() { }

		virtual void enable() = 0;
		virtual void disable() = 0;

		virtual uint32_t get_last_record() = 0;

	};

}

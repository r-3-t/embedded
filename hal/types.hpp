#pragma once

#include <vector>
#include <list>

#include <stdint.h>

namespace types {

	typedef unsigned char			byte;
	typedef byte*					bytes;

	typedef unsigned int			uint32;
	typedef unsigned int			uint16;

	typedef std::vector<byte>		buffer;
	typedef std::list<byte>		fifo;
}

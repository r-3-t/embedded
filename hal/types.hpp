#pragma once

#ifdef STREAM_DEBUG
#include <stream.hpp>
#else
#include <vector>
#endif

#include <stdint.h>

namespace types {

	typedef unsigned char			byte;
	typedef byte*					bytes;

	typedef unsigned int			uint32;
	typedef unsigned int			uint16;

#ifdef STREAM_DEBUG
	typedef stream					buffer;
#else
	typedef std::vector<byte>		buffer;
#endif
}

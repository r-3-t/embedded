#pragma once

#include <vector>
#include <list>

#include <stdint.h>

#include <cbuff.h>

namespace types {

	typedef uint8_t					byte;
	typedef byte*					bytes;

	typedef uint32_t				uint32;
	typedef uint16_t				uint16;
	typedef uint8_t					uint8;

	typedef int32_t					int32;
	typedef int16_t					int16;

	typedef cbuff_t					buffer;
	typedef cbuff_t					fifo;
}

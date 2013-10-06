#pragma once

#include <led.hpp>

namespace led
{

constexpr unsigned int	getNumLed()
{
	return 4;
}


constexpr unsigned int invalidLedId()
{
	return (unsigned int)-1;
}
	
}

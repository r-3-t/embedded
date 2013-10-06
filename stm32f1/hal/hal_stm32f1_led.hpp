#pragma once

#include <led.hpp>

namespace led
{

constexpr unsigned int	getNumLed()
{
	return 2;
}


constexpr unsigned int invalidLedId()
{
	return (unsigned int)-1;
}
	
}

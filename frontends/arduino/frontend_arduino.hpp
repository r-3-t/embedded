#include "binary.h"
#include "arduino_gpio.hpp"
#include "arduino_clock.hpp"
#include "arduino_spi.hpp"

#include <algorithm>
using namespace std;
#define pgm_read_byte(X)				(*X)

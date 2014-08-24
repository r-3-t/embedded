#include "binary.h"
#include "Arduino.h"
#include "arduino_gpio.hpp"
#include "arduino_clock.hpp"
#include "arduino_spi.hpp"
#include "arduino_serial.hpp"
#include "arduino_wire.hpp"
#include "Print.hpp"

using namespace ::arduino::gpio;
using namespace ::arduino::clock;
using namespace ::arduino::wire;
using namespace ::arduino::serial;
using namespace ::arduino::spi;
using namespace ::arduino::print;

#include <algorithm>
typedef uint8_t							byte;
#define F(X)							X
#define pgm_read_byte(X)				(*X)

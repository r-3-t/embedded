#include "binary.h"
#include "arduino_gpio.hpp"
#include "arduino_clock.hpp"
#include "arduino_spi.hpp"
#include "arduino_serial.hpp"
#include "arduino_wire.hpp"

using namespace ::arduino::gpio;
using namespace ::arduino::clock;
using namespace ::arduino::wire;
using namespace ::arduino::serial;

#include <algorithm>
using namespace std;
typedef uint8_t							byte;
#define pgm_read_byte(X)				(*X)

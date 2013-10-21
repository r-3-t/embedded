#include "arduino_gpio.hpp"
#include "arduino_clock.hpp"
#include "arduino_spi.hpp"

#include <algorithm>
using namespace std;
#define pgm_read_byte(X)				(*X)

//TODO: smart this
#define B0								0x0
#define B1								0x1
#define B10								0x2
#define B11								0x3
#define B100							0x4
#define B101							0x5
#define B110							0x6
#define B111							0x7
#define B1000							0x8
#define B1001							0x9
#define B1010							0xA
#define B1011							0xB
#define B1100							0xC
#define B1101							0xD
#define B1110							0xE
#define B1111							0xF


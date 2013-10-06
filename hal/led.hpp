#pragma once

namespace led
{
typedef enum {
	INVALID,
	YELLOW,
	GREEN,
	BLUE,
	RED,
	ORANGE,
} LedColor_t;

constexpr unsigned int	getNumLed();
constexpr unsigned int invalidLedId();

typedef unsigned int	LedId_t;
LedId_t	getNextLed(LedId_t);


LedColor_t getLedColor(LedId_t LedId);

class LedGroup
{
public:
	// invalidLedId means select all avalaibles leds
	LedGroup(LedId_t ledIds = invalidLedId());


	void on() const;
	void off() const;
	void toggle() const;

private:
	LedId_t _ledIds;
};


extern const LedGroup LedList[];


}

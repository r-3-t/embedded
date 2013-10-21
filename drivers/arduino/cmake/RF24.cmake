include(../../frontends/arduino/arduino.cmake)
list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_LIST_DIR}/../RF24/RF24.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../RF24/)

EXECUTE_PROCESS(COMMAND sed -i "s,typedef char const char;,,e" ${CMAKE_CURRENT_LIST_DIR}/../RF24/RF24_config.h OUTPUT_VARIABLE DATETIMESTRING)

file (WRITE ${CMAKE_CURRENT_LIST_DIR}/../RF24/WProgram.h
"#include <frontend_arduino.hpp>
using namespace ::arduino::gpio;
using namespace ::arduino::clock;
using namespace ::arduino::spi;
")

cmake_minimum_required(VERSION 2.6)

project("test_arduino_mpu6050")

set (PROJECT_SOURCES	main.cpp)

include(../../frontends/arduino/arduino.cmake) 
include(../cmake/example.cmake)

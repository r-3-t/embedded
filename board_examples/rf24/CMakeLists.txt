cmake_minimum_required(VERSION 2.6)

project("rf24")

set (PROJECT_SOURCES	main.cpp)

include(../../drivers/arduino/cmake/RF24.cmake)

include(../cmake/example.cmake) 


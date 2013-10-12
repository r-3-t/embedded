cmake_minimum_required(VERSION 2.6)

project("sandbox")

set (PROJECT_SOURCES	main.cpp
						stm32f4_discovery.c
						stm32f4_discovery.h)

include(../cmake/example.cmake) 


cmake_minimum_required(VERSION 2.6)

set(EMBEDDED_PATH ${CMAKE_CURRENT_LIST_DIR}/../../)
include(${EMBEDDED_PATH}/backends/cmake/project.cmake)

build_project(test_spi main.cpp)

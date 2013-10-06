cmake_minimum_required(VERSION 2.6)

project("test_zigbee")

set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
include(embedded)

# set minimum cmake version
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Uncomment if you want to do profiling with gprof
# SET(CMAKE_CXX_FLAGS "-pg")

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf		main.cpp)

ADD_CUSTOM_TARGET(${CMAKE_PROJECT_NAME}.hex ALL DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${OBJCOPY} -O ihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex)
ADD_CUSTOM_TARGET(${CMAKE_PROJECT_NAME}.bin ALL DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)

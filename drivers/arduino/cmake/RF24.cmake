include(../../frontends/arduino/arduino.cmake)
list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_LIST_DIR}/../RF24/RF24.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../RF24/)


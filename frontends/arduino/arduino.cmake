list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_LIST_DIR}/arduino_gpio.cpp)
list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_LIST_DIR}/arduino_clock.cpp)
list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_LIST_DIR}/arduino_spi.cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/)

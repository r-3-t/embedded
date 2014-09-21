add_library(pinout OBJECT Pinout.cpp Pinout.hpp PinoutInterface.hpp)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(pinout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
#target_link_libraries(pinout PUBLIC hal_${mcu})


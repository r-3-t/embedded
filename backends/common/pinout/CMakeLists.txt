add_library(pinout Pinout.cpp Pinout.hpp PinoutInterface.hpp)
target_include_directories(pinout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
target_link_libraries(pinout hal_${mcu})


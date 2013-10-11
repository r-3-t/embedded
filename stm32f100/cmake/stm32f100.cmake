INCLUDE(CMakeForceCompiler)


set (STM32F1_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../stm32f1")
set (STM32F10x_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include (${STM32F1_ROOT_DIR}/cmake/stm32f10x.cmake)


set (STM32F1_BOARD_SPECIFIC_FILES ${STM32F10x_ROOT_DIR}/hal/hal_stm32f100_led.cpp)



configure_file(${CMAKE_CURRENT_LIST_DIR}/../../hal/clock.hpp ${CMAKE_BINARY_DIR}/hal/clock.hpp COPYONLY)
configure_file(${STM32F10x_ROOT_DIR}/hal/hal_stm32f100_led.hpp ${CMAKE_BINARY_DIR}/hal/led.hpp COPYONLY)
configure_file(${STM32F10x_ROOT_DIR}/hal/hal_stm32f100_uart.hpp ${CMAKE_BINARY_DIR}/hal/uart.hpp COPYONLY)
include_directories(${CMAKE_BINARY_DIR})



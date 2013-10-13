INCLUDE(CMakeForceCompiler)


set (STM32F1_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../../generic_code/stm32f1")
set (STM32F10x_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/..")
set (BASE_HAL_DIR			"${CMAKE_CURRENT_LIST_DIR}/../../../hal/")

#add medium device value line definitions
add_definitions(-DSTM32F10X_MD_VL)
include (${STM32F1_ROOT_DIR}/cmake/stm32f10x.cmake)


set (STM32F1_BOARD_SPECIFIC_FILES ${STM32F10x_ROOT_DIR}/hal/hal_stm32f100_led.cpp)



configure_file(${BASE_HAL_DIR}/clock.hpp ${CMAKE_BINARY_DIR}/hal/clock.hpp COPYONLY)
configure_file(${STM32F10x_ROOT_DIR}/hal/hal_stm32f100_led.hpp ${CMAKE_BINARY_DIR}/hal/led.hpp COPYONLY)
configure_file(${STM32F1_ROOT_DIR}/hal/hal_stm32f1_uart.hpp ${CMAKE_BINARY_DIR}/hal/uart.hpp COPYONLY)
configure_file(${STM32F1_ROOT_DIR}/hal/hal_stm32f1_gpio.hpp ${CMAKE_BINARY_DIR}/hal/gpio.hpp COPYONLY)
configure_file(${STM32F1_ROOT_DIR}/hal/hal_stm32f1_spi.hpp ${CMAKE_BINARY_DIR}/hal/spi.hpp COPYONLY)
include_directories(${CMAKE_BINARY_DIR})



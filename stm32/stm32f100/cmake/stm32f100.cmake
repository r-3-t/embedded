INCLUDE(CMakeForceCompiler)


set (STM32F1_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../../generic_code/stm32f1")
set (STM32F10x_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/..")
set (BASE_HAL_DIR			"${CMAKE_CURRENT_LIST_DIR}/../../../hal/")

# add medium device value line definitions
add_definitions(-DSTM32F10X_MD_VL)

# hal files for stm32f100
set (HAL_IMPLEMENTED_LED 			${STM32F10x_ROOT_DIR}/hal/hal_stm32f100_led.hpp)
set (HAL_IMPLEMENTED_CLOCK			${BASE_HAL_DIR}/clock.hpp)
set (HAL_IMPLEMENTED_UART			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_uart.hpp)
set (HAL_IMPLEMENTED_GPIO			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_gpio.hpp)
set (HAL_IMPLEMENTED_SPI			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_spi.hpp)

set (STM32F1_BOARD_SPECIFIC_FILES	${STM32F10x_ROOT_DIR}/hal/hal_stm32f100_led.cpp)

include (${STM32F1_ROOT_DIR}/cmake/stm32f10x.cmake)


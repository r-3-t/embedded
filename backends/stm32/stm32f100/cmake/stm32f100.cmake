INCLUDE(CMakeForceCompiler)


set (STM32F1_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../../generic_code/stm32f1")
set (STM32F10x_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/..")

# add medium device value line definitions
add_definitions(-DSTM32F10X_MD_VL)

# hal files for stm32f100
set (HAL_IMPLEMENTED_CLOCK			${BASE_HAL_DIR}/ClockInterface.hpp)
set (HAL_IMPLEMENTED_UART			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_uart.hpp)
set (HAL_IMPLEMENTED_GPIO			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_gpio.hpp)
set (HAL_IMPLEMENTED_EXTINT			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_extint.hpp)
set (HAL_IMPLEMENTED_PWM			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_pwm.hpp)
set (HAL_IMPLEMENTED_TIMER			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_timer.hpp)
set (HAL_IMPLEMENTED_SPI			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_spi.hpp)



set (_RAM_SIZE				8K)
set (_FLASH_SIZE			128K)
set (_MIN_STACK_SIZE		0xC00)
set (_MIN_HEAP_SIZE			0x800)

include (${STM32F1_ROOT_DIR}/cmake/stm32f10x.cmake)


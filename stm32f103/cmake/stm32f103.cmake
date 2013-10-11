INCLUDE(CMakeForceCompiler)


set (STM32F1_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../stm32f1")
set (STM32F10x_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include (${STM32F1_ROOT_DIR}/cmake/stm32f10x.cmake)


set (STM32F1_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../stm32f1/")
set (STM32F103_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")


configure_file(${CMAKE_CURRENT_LIST_DIR}/../../hal/clock.hpp ${CMAKE_BINARY_DIR}/hal/clock.hpp COPYONLY)
configure_file(${STM32F10x_ROOT_DIR}/hal/hal_stm32f103_uart.hpp ${CMAKE_BINARY_DIR}/hal/uart.hpp COPYONLY)
configure_file(${STM32F1_ROOT_DIR}/hal/hal_stm32f1_gpio.hpp ${CMAKE_BINARY_DIR}/hal/gpio.hpp COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../../stm32fx/hal/stm32fx/usart_conf.hpp ${CMAKE_BINARY_DIR}/hal/stm32fx/usart_conf.hpp COPYONLY)



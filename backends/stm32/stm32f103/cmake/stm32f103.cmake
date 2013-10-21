INCLUDE(CMakeForceCompiler)


set (STM32F1_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../../generic_code/stm32f1")
set (STM32F10x_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/..")


#add medium device definitions
add_definitions(-DSTM32F10X_MD)

# hal files for stm32f103
set (HAL_IMPLEMENTED_LED 			) # no available led
set (HAL_IMPLEMENTED_CLOCK			${BASE_HAL_DIR}/clock.hpp)
set (HAL_IMPLEMENTED_UART			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_uart.hpp)
set (HAL_IMPLEMENTED_GPIO			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_gpio.hpp)
set (HAL_IMPLEMENTED_SPI			${STM32F1_ROOT_DIR}/hal/hal_stm32f1_spi.hpp)

include (${STM32F1_ROOT_DIR}/cmake/stm32f10x.cmake)

set (GDBINIT_CONTENT
"target remote localhost:3333
")

set (OPENOCDCFG_CONTENT
"interface ft2232
ft2232_device_desc \"USB<=>JTAG&RS232\"
ft2232_layout jtagkey
ft2232_vid_pid 0x1457 0x5118

source [find target/stm32f1x.cfg]

#jtag_rclk 1500

gdb_breakpoint_override hard

#reset_config trst_and_srst srst_pulls_trst srst_gates_jtag
reset_config trst_and_srst separate

")


file (WRITE ${CMAKE_BINARY_DIR}/.gdbinit ${GDBINIT_CONTENT})
file (WRITE ${CMAKE_BINARY_DIR}/openocd.cfg ${OPENOCDCFG_CONTENT})

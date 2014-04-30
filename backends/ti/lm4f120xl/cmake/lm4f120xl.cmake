set (LM4F120_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../")
set (TIX_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../../generic_code/")

# hal files for lm4f120
set (HAL_IMPLEMENTED_LED 			) # no available led
set (HAL_IMPLEMENTED_CLOCK			${BASE_HAL_DIR}/ClockInterface.hpp)
set (HAL_IMPLEMENTED_UART			${TIX_ROOT_DIR}/hal/hal_tix_uart.hpp)
set (HAL_IMPLEMENTED_GPIO			${TIX_ROOT_DIR}/hal/hal_tix_gpio.hpp)
set (HAL_IMPLEMENTED_SPI			${TIX_ROOT_DIR}/hal/hal_tix_spi.hpp)
set (HAL_IMPLEMENTED_I2C			${TIX_ROOT_DIR}/hal/hal_tix_i2c.hpp)


#configure TI lib to use LM4F120H5QR
add_definitions(-DPART_LM4F120H5QR)

# maybe put this in extra cmake
include(${TIX_ROOT_DIR}/cmake/tix.cmake)

set (GDBINIT_CONTENT
"target remote localhost:3333
monitor reset init
")

set (OPENOCDCFG_CONTENT
"source [find board/ek-lm4f120xl.cfg]
")


file (WRITE ${CMAKE_BINARY_DIR}/.gdbinit ${GDBINIT_CONTENT})
file (WRITE ${CMAKE_BINARY_DIR}/openocd.cfg ${OPENOCDCFG_CONTENT})


INCLUDE(CMakeForceCompiler)

set (LM4F120_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../")
set (TIX_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/../../generic_code/")
list(APPEND MCU_HAL_FILES_SOURCES ${TIX_ROOT_DIR}/hal/hal_lm4f120_clock.cpp)

# hal files for lm4f120
set (HAL_IMPLEMENTED_LED 			) # no available led
set (HAL_IMPLEMENTED_CLOCK			${BASE_HAL_DIR}/clock.hpp)
set (HAL_IMPLEMENTED_UART			)
set (HAL_IMPLEMENTED_GPIO			${TIX_ROOT_DIR}/hal/hal_lm4f120_gpio.hpp)
set (HAL_IMPLEMENTED_SPI			)


# maybe put this in extra cmake
include(${TIX_ROOT_DIR}/cmake/tix.cmake)

set (GDBINIT_CONTENT
"target remote localhost:3333
")

set (OPENOCDCFG_CONTENT
"source [find board/ek-lm4f120xl.cfg]
")


file (WRITE ${CMAKE_BINARY_DIR}/.gdbinit ${GDBINIT_CONTENT})
file (WRITE ${CMAKE_BINARY_DIR}/openocd.cfg ${OPENOCDCFG_CONTENT})


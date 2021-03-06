
list(APPEND MCU_HAL_FILES_SOURCES ${TIX_ROOT_DIR}/hal/hal_tix_clock.cpp)
list(APPEND MCU_HAL_FILES_SOURCES ${TIX_ROOT_DIR}/hal/hal_tix_uart.cpp)
list(APPEND MCU_HAL_FILES_SOURCES ${TIX_ROOT_DIR}/hal/hal_tix_gpio.cpp)
list(APPEND MCU_HAL_FILES_SOURCES ${TIX_ROOT_DIR}/hal/hal_tix_i2c.cpp)

################################################################################
# TI system headers
set(TIX_LIBRARY_PATH ${TIX_ROOT_DIR}/system_files/)
set (TARGET_INCLUDE_DIRECTORIES		${TIX_ROOT_DIR}
									${TIX_LIBRARY_PATH}
									${TIX_LIBRARY_PATH}/inc/
									${TIX_LIBRARY_PATH}/driverlib/
									${TIX_ROOT_DIR}/system_files/
									CACHE STRING "TARGET_INCLUDE_DIRECTORIES")


# for SysCtlDelay in sysctl.c
add_definitions(-Dgcc)

################################################################################
# TI system sources
set(TIX_DriverLib				${TIX_LIBRARY_PATH}/driverlib)
set(TIX_SYSCTL_SOURCE				sysctl)
set(TIX_SYSTICK_SOURCE				systick)
set(TIX_GPIO_SOURCE				gpio)
set(TIX_SSI_SOURCE				ssi)
set(TIX_I2C_SOURCE				i2c)
set(TIX_UART_SOURCE				uart)
set(TIX_INTERRUPT_SOURCE			interrupt)
set(TIX_CPU_SOURCE				cpu)

################################################################################

################################################################################
# stm32f4 system sources list
set(TIX_SYSTEM_SOURCES				TIX_SYSCTL_SOURCE
						TIX_SYSTICK_SOURCE
						TIX_GPIO_SOURCE
						TIX_SSI_SOURCE
						TIX_I2C_SOURCE
						TIX_UART_SOURCE
						TIX_INTERRUPT_SOURCE
						TIX_CPU_SOURCE
						)
																																																																																																																																																

################################################################################
# add sources requested by the user in the CMakeLists.txt

foreach(SYSTEM_SOURCE ${TIX_SYSTEM_SOURCES})
		list(APPEND TIX_SYSTEM_FILES_SOURCES ${TIX_DriverLib}/${${SYSTEM_SOURCE}}.c)
		list(APPEND TIX_SYSTEM_FILES_HEADERS ${TIX_DriverLib}/${${SYSTEM_SOURCE}}.h)
endforeach()

################################################################################

################################################################################
# just warn user if HSE is not set that default HSE value from HAL
################################################################################
if (NOT HSE)
	message("No HSE is provide, so default HSE value will be used.")
else()
	add_definitions(-DHSE_VALUE=${HSE})
endif()

################################################################################
# find stm32 system file Devices vector table
list(APPEND PROJECT_SOURCES  "${TIX_ROOT_DIR}/system_files/startup_lm4f120.c")
################################################################################

################################################################################
# find STM32F4xx Devices vector table
list(APPEND PROJECT_SOURCES  "${TIX_ROOT_DIR}/system_files/syscall.c")
################################################################################


set (MCU_SYSTEM_FILES_SOURCES	${TIX_SYSTEM_FILES_SOURCES})
set (MCU_SYSTEM_FILES_HEADERS	${TIX_SYSTEM_FILES_HEADERS})


SET(MCFLAGS "-mlittle-endian -mthumb -mcpu=cortex-m4")
set (_RAM_ORIGIN			0x20000000)
set (_RAM_SIZE				32k)
set (_FLASH_ORIGIN			0x00000000)
set (_FLASH_SIZE			256k)
set (_MIN_STACK_SIZE		0x800)
set (_MIN_HEAP_SIZE			0x800)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../../../generic_code/linker_script.ld ${CMAKE_BINARY_DIR}/)
set (LDSCRIPT "${CMAKE_BINARY_DIR}/linker_script.ld")


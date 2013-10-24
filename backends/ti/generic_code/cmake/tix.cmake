
list(APPEND MCU_HAL_FILES_SOURCES ${TIX_ROOT_DIR}/hal/hal_lm4f120_clock.cpp)

################################################################################
# TI system headers
set(TIX_LIBRARY_PATH ${TIX_ROOT_DIR}/system_files/)
include_directories(${TIX_LIBRARY_PATH})
include_directories(${TIX_LIBRARY_PATH}/inc/)
include_directories(${TIX_LIBRARY_PATH}/driverlib/)
include_directories(${TIX_ROOT_DIR}/system_files/)

# for SysCtlDelay in sysctl.c
add_definitions(-Dgcc)

################################################################################
# TI system sources
set(TIX_DriverLib				${TIX_LIBRARY_PATH}/driverlib)
set(TIX_SYSCTL_SOURCE				sysctl)
set(TIX_SYSTICK_SOURCE				systick)
set(TIX_GPIO_SOURCE				gpio)

################################################################################

################################################################################
# stm32f4 system sources list
set(TIX_SYSTEM_SOURCES				TIX_SYSCTL_SOURCE
						TIX_SYSTICK_SOURCE
						TIX_GPIO_SOURCE
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
list(APPEND TIX_SYSTEM_FILES_SOURCES  "${TIX_ROOT_DIR}/system_files/startup_lm4f120.c")
################################################################################

################################################################################
# find STM32F4xx Devices vector table
list(APPEND TIX_SYSTEM_FILES_SOURCES  "${TIX_ROOT_DIR}/system_files/syscall.c")
################################################################################


set (MCU_SYSTEM_FILES_SOURCES	${TIX_SYSTEM_FILES_SOURCES})
set (MCU_SYSTEM_FILES_HEADERS	${TIX_SYSTEM_FILES_HEADERS})


SET(MCFLAGS "-mlittle-endian -mthumb -mcpu=cortex-m4")
set (LDSCRIPT "${TIX_ROOT_DIR}/system_files/lm4f120.ld")



function(add_executable ...)
	_add_executable(${ARGV}		${STM32F1_NEEDED_SYSTEM_FILES}
								${STM32F1_ACCESS_LAYER_SYSTEM_SOURCE_FILE}
								${STM32F1_DEVICE_VECTOR_TABLE_SOURCE_FILE}
								${STM32F1_SYSCALL_SOURCE_FILE}
								${STM32F1_ROOT_DIR}/hal/hal_stm32f1_clock.cpp
								${STM32F1_BOARD_SPECIFIC_FILES}
							)
endfunction()


SET(CMAKE_CROSSCOMPILING TRUE) 
# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Generic)

################################################################################

set (SYSTEM_FILES_DIR "${STM32F10x_ROOT_DIR}/system_files")

################################################################################

include_directories(${CMAKE_BINARY_DIR})

include (arm-none-eabi-gcc)


################################################################################
# HAL FILES

macro (add_hal_files hal_implemented hal_type)

	if (NOT ${hal_implemented})
		message ("${hal_type} is not implemented for this architecture")
	elseif (${${hal_implemented}} STREQUAL "")
		message ("${hal_type} is not implemented for this architecture")
	else()

		set(hal_filename ${hal_type}.hpp)

		file (TO_NATIVE_PATH ${${hal_implemented}}				HAL_IMPLEMENTED_NATIVE_PATH)
		file (TO_NATIVE_PATH ${BASE_HAL_DIR}/${hal_filename}	HAL_NATIVE_PATH)

		file (READ ${HAL_IMPLEMENTED_NATIVE_PATH} FILE_CONTENT)
		file (WRITE ${CMAKE_BINARY_DIR}/hal/${hal_filename} "
/****************************************************************************
** Hal file for ${hal_type}
**
** This file was genereted by the toolchain
**
** The original file is located here : \"${HAL_IMPLEMENTED_NATIVE_PATH}\"
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/
")
		file (APPEND ${CMAKE_BINARY_DIR}/hal/${hal_filename} "${FILE_CONTENT}")

		
		list(APPEND STM32F1_NEEDED_SYSTEM_FILES ${HAL_NATIVE_PATH})
		if (NOT (${HAL_IMPLEMENTED_NATIVE_PATH} STREQUAL ${HAL_NATIVE_PATH}))
			#message ("append : ${HAL_IMPLEMENTED_NATIVE_PATH}")
			list(APPEND STM32F1_NEEDED_SYSTEM_FILES ${HAL_IMPLEMENTED_NATIVE_PATH})
		endif()

	endif()
endmacro()

add_hal_files(HAL_IMPLEMENTED_LED		"led")
add_hal_files(HAL_IMPLEMENTED_CLOCK		"clock")
add_hal_files(HAL_IMPLEMENTED_UART		"uart")
add_hal_files(HAL_IMPLEMENTED_GPIO		"gpio")
add_hal_files(HAL_IMPLEMENTED_SPI		"spi")

################################################################################
# stm32f4 system headers
include_directories(${BASE_HAL_DIR})
include_directories(${SYSTEM_FILES_DIR})
include_directories(${STM32F1_ROOT_DIR}/system_files/STM32F10x_StdPeriph_Driver/inc/)
include_directories(${STM32F1_ROOT_DIR}/system_files)
include_directories(${STM32F1_ROOT_DIR}/../stm32fx/)

################################################################################
# stm32f4 system sources
set(STM32F1xx_StdPeriph_Driver		${STM32F1_ROOT_DIR}/system_files/STM32F10x_StdPeriph_Driver)
set(STM32F1_MISC_SOURCE				misc)
set(STM32F1_ADC_SOURCE				stm32f10x_adc)
set(STM32F1_BKP_SOURCE				stm32f10x_bkp)
set(STM32F1_CAN_SOURCE				stm32f10x_can)
set(STM32F1_CEC_SOURCE				stm32f10x_cec)
set(STM32F1_CRC_SOURCE				stm32f10x_crc)
set(STM32F1_DAC_SOURCE				stm32f10x_dac)
set(STM32F1_DBGMCU_SOURCE			stm32f10x_dbgmcu)
set(STM32F1_DMA_SOURCE				stm32f10x_dma)
set(STM32F1_EXTI_SOURCE				stm32f10x_exti)
set(STM32F1_FLASH_SOURCE			stm32f10x_flash)
set(STM32F1_FSMC_SOURCE				stm32f10x_fsmc)
set(STM32F1_GPIO_SOURCE				stm32f10x_gpio)
set(STM32F1_I2C_SOURCE				stm32f10x_i2c)
set(STM32F1_IWDG_SOURCE				stm32f10x_iwdg)
set(STM32F1_PWR_SOURCE				stm32f10x_pwr)
set(STM32F1_RCC_SOURCE				stm32f10x_rcc)
set(STM32F1_RTC_SOURCE				stm32f10x_rtc)
set(STM32F1_SDIO_SOURCE				stm32f10x_sdio)
set(STM32F1_SPI_SOURCE				stm32f10x_spi)
set(STM32F1_TIM_SOURCE				stm32f10x_tim)
set(STM32F1_USART_SOURCE			stm32f10x_usart)
set(STM32F1_WWDG_SOURCE				stm32f10x_wwdg)
################################################################################

################################################################################
# stm32f4 system sources list
set(STM32F1_SYSTEM_SOURCES	STM32F1_MISC_SOURCE		
							STM32F1_ADC_SOURCE		
							STM32F1_BKP_SOURCE		
							STM32F1_CAN_SOURCE		
							STM32F1_CEC_SOURCE		
							STM32F1_CRC_SOURCE		
							STM32F1_DAC_SOURCE		
							STM32F1_DBGMCU_SOURCE	
							STM32F1_DMA_SOURCE		
							STM32F1_EXTI_SOURCE		
							STM32F1_FLASH_SOURCE	
							STM32F1_FSMC_SOURCE		
							STM32F1_GPIO_SOURCE		
							STM32F1_I2C_SOURCE		
							STM32F1_IWDG_SOURCE		
							STM32F1_PWR_SOURCE		
							STM32F1_RCC_SOURCE		
							STM32F1_RTC_SOURCE		
							STM32F1_SDIO_SOURCE		
							STM32F1_SPI_SOURCE		
							STM32F1_TIM_SOURCE		
							STM32F1_USART_SOURCE	
							STM32F1_WWDG_SOURCE)
																																																																																																																																																

################################################################################
# add sources requested by the user in the CMakeLists.txt
foreach(SYSTEM_SOURCE ${STM32F1_SYSTEM_SOURCES})
		list(APPEND STM32F1_NEEDED_SYSTEM_FILES ${STM32F1xx_StdPeriph_Driver}/src/${${SYSTEM_SOURCE}}.c)
		list(APPEND STM32F1_NEEDED_SYSTEM_FILES ${STM32F1xx_StdPeriph_Driver}/inc/${${SYSTEM_SOURCE}}.h)
endforeach()

# if user has requested some standard driver we must say it
list(LENGTH STM32F1_NEEDED_SYSTEM_FILES STM32F1_NEEDED_SYSTEM_FILES_LENGTH)
if (${STM32F1_NEEDED_SYSTEM_FILES_LENGTH} GREATER 0)
	add_definitions(-DUSE_STDPERIPH_DRIVER)
	include_directories(${CMAKE_SOURCE_DIR})
endif()
################################################################################

################################################################################
# just warn user if HSE is not set that default HSE value from ST std periph will be used
################################################################################
if (NOT HSE)
	message("No HSE is provide, so default HSE value will be used.")
else()
	add_definitions(-DHSE_VALUE=${HSE})
endif()

################################################################################
# find stm32 system file (CMSIS Cortex-M4 Device Peripheral Access Layer System Source File)
set (STM32F1_ACCESS_LAYER_SYSTEM_SOURCE_FILE  "${STM32F10x_ROOT_DIR}/system_files/system_stm32f10x.c")
################################################################################

################################################################################
# find STM32F4xx Devices vector table
set (STM32F1_DEVICE_VECTOR_TABLE_SOURCE_FILE  "${SYSTEM_FILES_DIR}/startup_stm32f10x_md_vl.s")
################################################################################


################################################################################
# find STM32F4xx Devices vector table
set (STM32F1_SYSCALL_SOURCE_FILE  "${STM32F1_ROOT_DIR}/../stm32fx/system_files/syscall.c")
################################################################################



# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(MCFLAGS "-mlittle-endian -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd")
SET(CMAKE_ASM_FLAGS "${MCFLAGS}")
SET(CMAKE_C_FLAGS "${MCFLAGS} -Wall -Wextra -Warray-bounds -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS "${MCFLAGS} -std=c++11 -Wall -Wextra -Warray-bounds -fno-builtin -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_ASM_FLAGS_DEBUG "-g")

SET(CMAKE_C_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_ASM_FLAGS_RELEASE "")

################################################################################
# find stm32_flash.ld linker script files
set (LDSCRIPT "${STM32F10x_ROOT_DIR}/system_files/stm32_flash.ld")
################################################################################

SET(CMAKE_CXX_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs")
SET(CMAKE_C_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs")

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

ENABLE_LANGUAGE(ASM)


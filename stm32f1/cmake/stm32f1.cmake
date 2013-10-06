INCLUDE(CMakeForceCompiler)

function(add_executable ...)
	_add_executable(${ARGV}		${STM32F1_NEEDED_SYSTEM_FILES}
								${STM32F1_ACCESS_LAYER_SYSTEM_SOURCE_FILE}
								${STM32F1_DEVICE_VECTOR_TABLE_SOURCE_FILE}
								${STM32F1_SYSCALL_SOURCE_FILE}
								${STM32F1_ROOT_DIR}/hal/hal_stm32f1_led.cpp
								${STM32F1_ROOT_DIR}/hal/hal_stm32f1_clock.cpp
								#${STM32F1_ROOT_DIR}/system_files/core_cm3.c
							)
endfunction()

set (STM32F1_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

SET(CMAKE_CROSSCOMPILING TRUE) 
# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Generic)

################################################################################

set (SYSTEM_FILES_DIR "${CMAKE_CURRENT_LIST_DIR}/../system_files")

################################################################################

configure_file(${CMAKE_CURRENT_LIST_DIR}/../../hal/clock.hpp ${CMAKE_BINARY_DIR}/hal/clock.hpp COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../hal/hal_stm32f1_led.hpp ${CMAKE_BINARY_DIR}/hal/led.hpp COPYONLY)
include_directories(${CMAKE_BINARY_DIR})

include (arm-none-eabi-gcc)

################################################################################
# stm32f4 system headers


include_directories(${CMAKE_CURRENT_LIST_DIR}/../../hal/)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../hal/)
include_directories(${SYSTEM_FILES_DIR})
include_directories(${SYSTEM_FILES_DIR}/STM32F10x_StdPeriph_Driver/inc/)

################################################################################
# stm32f4 system sources
set(STM32F1xx_StdPeriph_Driver		${SYSTEM_FILES_DIR}/STM32F10x_StdPeriph_Driver/src)
set(STM32F1_MISC_SOURCE				${STM32F1xx_StdPeriph_Driver}/misc.c)
set(STM32F1_ADC_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_adc.c)
set(STM32F1_BKP_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_bkp.c)
set(STM32F1_CAN_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_can.c)
set(STM32F1_CEC_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_cec.c)
set(STM32F1_CRC_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_crc.c)
set(STM32F1_DAC_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_dac.c)
set(STM32F1_DBGMCU_SOURCE			${STM32F1xx_StdPeriph_Driver}/stm32f10x_dbgmcu.c)
set(STM32F1_DMA_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_dma.c)
set(STM32F1_EXTI_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_exti.c)
set(STM32F1_FLASH_SOURCE			${STM32F1xx_StdPeriph_Driver}/stm32f10x_flash.c)
set(STM32F1_FSMC_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_fsmc.c)
set(STM32F1_GPIO_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_gpio.c)
set(STM32F1_I2C_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_i2c.c)
set(STM32F1_IWDG_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_iwdg.c)
set(STM32F1_PWR_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_pwr.c)
set(STM32F1_RCC_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_rcc.c)
set(STM32F1_RTC_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_rtc.c)
set(STM32F1_SDIO_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_sdio.c)
set(STM32F1_SPI_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_spi.c)
set(STM32F1_TIM_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_tim.c)
set(STM32F1_USART_SOURCE			${STM32F1xx_StdPeriph_Driver}/stm32f10x_usart.c)
set(STM32F1_WWDG_SOURCE				${STM32F1xx_StdPeriph_Driver}/stm32f10x_wwdg.c)
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
		list(APPEND STM32F1_NEEDED_SYSTEM_FILES ${${SYSTEM_SOURCE}})
endforeach()

# if user has requested some standard driver we must say it
list(LENGTH STM32F1_NEEDED_SYSTEM_FILES STM32F1_NEEDED_SYSTEM_FILES_LENGTH)
if (${STM32F1_NEEDED_SYSTEM_FILES_LENGTH} GREATER 0)
	add_definitions(-DUSE_STDPERIPH_DRIVER)
	include_directories(${CMAKE_SOURCE_DIR})
endif()
################################################################################




################################################################################
# find stm32 system file (CMSIS Cortex-M4 Device Peripheral Access Layer System Source File)
set (STM32F1_ACCESS_LAYER_SYSTEM_SOURCE_FILE  "${SYSTEM_FILES_DIR}/system_stm32f10x.c")
################################################################################


################################################################################
# find STM32F4xx Devices vector table
set (STM32F1_DEVICE_VECTOR_TABLE_SOURCE_FILE  "${SYSTEM_FILES_DIR}/startup_stm32f10x_md_vl.s")
################################################################################


################################################################################
# find STM32F4xx Devices vector table
set (STM32F1_SYSCALL_SOURCE_FILE  "${SYSTEM_FILES_DIR}/syscall.c")
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
set (LDSCRIPT "${CMAKE_CURRENT_LIST_DIR}/../system_files/stm32_flash.ld")
################################################################################

SET(CMAKE_CXX_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs")
SET(CMAKE_C_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs")

set (GDBINIT_CONTENT

"define reload
	kill
	monitor jtag_reset
	load
end

target extended-remote localhost:4242
load
")

file (WRITE ${CMAKE_BINARY_DIR}/.gdbinit ${GDBINIT_CONTENT})

ENABLE_LANGUAGE(ASM)



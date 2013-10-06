INCLUDE(CMakeForceCompiler)

function(add_executable ...)
	_add_executable(${ARGV}		${STM32F4_NEEDED_SYSTEM_FILES}
								${STM32F4_ACCESS_LAYER_SYSTEM_SOURCE_FILE}
								${STM32F4_DEVICE_VECTOR_TABLE_SOURCE_FILE}
								${STM32F4_SYSCALL_SOURCE_FILE}
								${STM32F4_ROOT_DIR}/hal/hal_stm32f4_clock.cpp
								${STM32F4_ROOT_DIR}/hal/hal_stm32f4_led.cpp
							)
endfunction()

set (STM32F4_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

SET(CMAKE_CROSSCOMPILING TRUE) 
# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Generic)

################################################################################

set (SYSTEM_FILES_DIR "${CMAKE_CURRENT_LIST_DIR}/../system_files")

################################################################################
# copy hal files to binary dir
configure_file(${CMAKE_CURRENT_LIST_DIR}/../hal/hal_stm32f4_gpio.hpp ${CMAKE_BINARY_DIR}/hal/gpio.hpp COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../hal/hal_stm32f4_spi.hpp ${CMAKE_BINARY_DIR}/hal/spi.hpp COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../hal/hal_stm32f4_uart.hpp ${CMAKE_BINARY_DIR}/hal/uart.hpp COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../../hal/clock.hpp ${CMAKE_BINARY_DIR}/hal/clock.hpp COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../hal/hal_stm32f4_led.hpp ${CMAKE_BINARY_DIR}/hal/led.hpp COPYONLY)
include_directories(${CMAKE_BINARY_DIR})

################################################################################
# cross compilation tools
include (arm-none-eabi-gcc)


################################################################################
# stm32f4 system headers
include_directories(${CMAKE_CURRENT_LIST_DIR}/../../hal/)
include_directories(${SYSTEM_FILES_DIR})
include_directories(${SYSTEM_FILES_DIR}/STM32F4xx_StdPeriph_Driver/inc/)
include_directories(${SYSTEM_FILES_DIR}/CMSIS/)
include_directories("${STM32F4_ROOT_DIR}/../stm32fx/")


################################################################################
# stm32f4 system sources
set(STM32F4xx_StdPeriph_Driver		${SYSTEM_FILES_DIR}/STM32F4xx_StdPeriph_Driver/src)
set(STM32F4_MISC_SOURCE				${STM32F4xx_StdPeriph_Driver}/misc.c)
set(STM32F4_ADC_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_adc.c)
set(STM32F4_CAN_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_can.c)
set(STM32F4_CRC_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_crc.c)
set(STM32F4_CRYP_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_cryp.c)
set(STM32F4_CRYP_AES_SOURCE			${STM32F4xx_StdPeriph_Driver}/stm32f4xx_cryp_aes.c)
set(STM32F4_CRYP_DES_SOURCE			${STM32F4xx_StdPeriph_Driver}/stm32f4xx_cryp_des.c)
set(STM32F4_CRYP_TDES_SOURCE		${STM32F4xx_StdPeriph_Driver}/stm32f4xx_cryp_tdes.c)
set(STM32F4_DAC_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_dac.c)
set(STM32F4_DBGMCU_SOURCE			${STM32F4xx_StdPeriph_Driver}/stm32f4xx_dbgmcu.c)
set(STM32F4_DCMI_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_dcmi.c)
set(STM32F4_DMA_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_dma.c)
set(STM32F4_EXTI_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_exti.c)
set(STM32F4_FLASH_SOURCE			${STM32F4xx_StdPeriph_Driver}/stm32f4xx_flash.c)
set(STM32F4_FSMC_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_fsmc.c)
set(STM32F4_GPIO_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_gpio.c)
set(STM32F4_HASH_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_hash.c)
set(STM32F4_MD5_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_hash_md5.c)
set(STM32F4_SHA1_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_hash_sha1.c)
set(STM32F4_I2C_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_i2c.c)
set(STM32F4_IWDG_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_iwdg.c)
set(STM32F4_PWR_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_pwr.c)
set(STM32F4_RCC_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_rcc.c)
set(STM32F4_RNG_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_rng.c)
set(STM32F4_RTC_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_rtc.c)
set(STM32F4_STDIO_SOURCE			${STM32F4xx_StdPeriph_Driver}/stm32f4xx_sdio.c)
set(STM32F4_SPI_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_spi.c)
set(STM32F4_SYSCFG_SOURCE			${STM32F4xx_StdPeriph_Driver}/stm32f4xx_syscfg.c)
set(STM32F4_TIM_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_tim.c)
set(STM32F4_USART_SOURCE			${STM32F4xx_StdPeriph_Driver}/stm32f4xx_usart.c)
set(STM32F4_WWDG_SOURCE				${STM32F4xx_StdPeriph_Driver}/stm32f4xx_wwdg.c)
################################################################################

################################################################################
# stm32f4 system sources list
set(STM32F4_SYSTEM_SOURCES	STM32F4_MISC_SOURCE
							STM32F4_ADC_SOURCE		
							STM32F4_CAN_SOURCE		
							STM32F4_CRC_SOURCE		
							STM32F4_CRYP_SOURCE		
							STM32F4_CRYP_AES_SOURCE	
							STM32F4_CRYP_DES_SOURCE	
							STM32F4_CRYP_TDES_SOURCE
							STM32F4_DAC_SOURCE		
							STM32F4_DBGMCU_SOURCE	
							STM32F4_DCMI_SOURCE		
							STM32F4_DMA_SOURCE		
							STM32F4_EXTI_SOURCE		
							STM32F4_FLASH_SOURCE	
							STM32F4_FSMC_SOURCE		
							STM32F4_GPIO_SOURCE		
							STM32F4_HASH_SOURCE		
							STM32F4_MD5_SOURCE		
							STM32F4_SHA1_SOURCE		
							STM32F4_I2C_SOURCE		
							STM32F4_IWDG_SOURCE		
							STM32F4_PWR_SOURCE		
							STM32F4_RCC_SOURCE		
							STM32F4_RNG_SOURCE		
							STM32F4_RTC_SOURCE		
							STM32F4_STDIO_SOURCE	
							STM32F4_SPI_SOURCE		
							STM32F4_SYSCFG_SOURCE	
							STM32F4_TIM_SOURCE		
							STM32F4_USART_SOURCE	
							STM32F4_WWDG_SOURCE)



################################################################################
# add sources requested by the user in the CMakeLists.txt
foreach(SYSTEM_SOURCE ${STM32F4_SYSTEM_SOURCES})
		list(APPEND STM32F4_NEEDED_SYSTEM_FILES ${${SYSTEM_SOURCE}})
endforeach()

# if user has requested some standard driver we must say it
list(LENGTH STM32F4_NEEDED_SYSTEM_FILES STM32F4_NEEDED_SYSTEM_FILES_LENGTH)
if (${STM32F4_NEEDED_SYSTEM_FILES_LENGTH} GREATER 0)
	add_definitions(-DUSE_STDPERIPH_DRIVER)
	include_directories(${CMAKE_SOURCE_DIR})
endif()
################################################################################




################################################################################
# find stm32 system file (CMSIS Cortex-M4 Device Peripheral Access Layer System Source File)
set (STM32F4_ACCESS_LAYER_SYSTEM_SOURCE_FILE  "${SYSTEM_FILES_DIR}/system_stm32f4xx.c")
################################################################################


################################################################################
# find STM32F4xx Devices vector table
set (STM32F4_DEVICE_VECTOR_TABLE_SOURCE_FILE  "${SYSTEM_FILES_DIR}/startup_stm32f4xx.s")
################################################################################


################################################################################
# find STM32F4xx Devices vector table
set (STM32F4_SYSCALL_SOURCE_FILE  "${STM32F4_ROOT_DIR}/../stm32fx/system_files/syscall.c")
################################################################################

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(MCFLAGS "-mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16")
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




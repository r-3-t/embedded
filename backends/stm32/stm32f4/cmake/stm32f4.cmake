INCLUDE(CMakeForceCompiler)

set (STM32F4_ROOT_DIR		"${CMAKE_CURRENT_LIST_DIR}/..")

# hal files for stm32f100
set (HAL_IMPLEMENTED_LED 			${STM32F4_ROOT_DIR}/hal/hal_stm32f4_led.hpp)
set (HAL_IMPLEMENTED_CLOCK			${BASE_HAL_DIR}/clock.hpp)
set (HAL_IMPLEMENTED_UART			${STM32F4_ROOT_DIR}/hal/hal_stm32f4_uart.hpp)
set (HAL_IMPLEMENTED_GPIO			${STM32F4_ROOT_DIR}/hal/hal_stm32f4_gpio.hpp)
set (HAL_IMPLEMENTED_SPI			${STM32F4_ROOT_DIR}/hal/hal_stm32f4_spi.hpp)

list (APPEND MCU_HAL_FILES_SOURCES	${STM32F4_ROOT_DIR}/hal/hal_stm32f4_led.cpp
									${STM32F4_ROOT_DIR}/hal/hal_stm32f4_clock.cpp)

################################################################################

set (SYSTEM_FILES_DIR "${CMAKE_CURRENT_LIST_DIR}/../system_files")

################################################################################
# stm32f4 system headers
include_directories(${SYSTEM_FILES_DIR})
include_directories(${SYSTEM_FILES_DIR}/STM32F4xx_StdPeriph_Driver/inc/)
include_directories(${SYSTEM_FILES_DIR}/CMSIS/)
include_directories("${STM32F4_ROOT_DIR}/../generic_code/stm32fx/")


################################################################################
# stm32f4 system sources
set(STM32F4xx_StdPeriph_Driver		${SYSTEM_FILES_DIR}/STM32F4xx_StdPeriph_Driver)
set(STM32F4_MISC_SOURCE				misc)
set(STM32F4_ADC_SOURCE				stm32f4xx_adc)
set(STM32F4_CAN_SOURCE				stm32f4xx_can)
set(STM32F4_CRC_SOURCE				stm32f4xx_crc)
set(STM32F4_CRYP_SOURCE				stm32f4xx_cryp)
set(STM32F4_CRYP_AES_SOURCE			stm32f4xx_cryp_aes)
set(STM32F4_CRYP_DES_SOURCE			stm32f4xx_cryp_des)
set(STM32F4_CRYP_TDES_SOURCE		stm32f4xx_cryp_tdes)
set(STM32F4_DAC_SOURCE				stm32f4xx_dac)
set(STM32F4_DBGMCU_SOURCE			stm32f4xx_dbgmcu)
set(STM32F4_DCMI_SOURCE				stm32f4xx_dcmi)
set(STM32F4_DMA_SOURCE				stm32f4xx_dma)
set(STM32F4_EXTI_SOURCE				stm32f4xx_exti)
set(STM32F4_FLASH_SOURCE			stm32f4xx_flash)
set(STM32F4_FSMC_SOURCE				stm32f4xx_fsmc)
set(STM32F4_GPIO_SOURCE				stm32f4xx_gpio)
set(STM32F4_HASH_SOURCE				stm32f4xx_hash)
set(STM32F4_MD5_SOURCE				stm32f4xx_hash_md5)
set(STM32F4_SHA1_SOURCE				stm32f4xx_hash_sha1)
set(STM32F4_I2C_SOURCE				stm32f4xx_i2c)
set(STM32F4_IWDG_SOURCE				stm32f4xx_iwdg)
set(STM32F4_PWR_SOURCE				stm32f4xx_pwr)
set(STM32F4_RCC_SOURCE				stm32f4xx_rcc)
set(STM32F4_RNG_SOURCE				stm32f4xx_rng)
set(STM32F4_RTC_SOURCE				stm32f4xx_rtc)
set(STM32F4_STDIO_SOURCE			stm32f4xx_sdio)
set(STM32F4_SPI_SOURCE				stm32f4xx_spi)
set(STM32F4_SYSCFG_SOURCE			stm32f4xx_syscfg)
set(STM32F4_TIM_SOURCE				stm32f4xx_tim)
set(STM32F4_USART_SOURCE			stm32f4xx_usart)
set(STM32F4_WWDG_SOURCE				stm32f4xx_wwdg)
################################################################################

################################################################################
# stm32f4 system sources list
set(STM32F4_SYSTEM_SOURCES	STM32F4_MISC_SOURCE
							STM32F4_ADC_SOURCE		
							STM32F4_CAN_SOURCE		
							STM32F4_CRC_SOURCE		
							STM32F4_CRYP_SOURCE		
							STM32F4_DAC_SOURCE		
							STM32F4_DBGMCU_SOURCE	
							STM32F4_DCMI_SOURCE		
							STM32F4_DMA_SOURCE		
							STM32F4_EXTI_SOURCE		
							STM32F4_FLASH_SOURCE	
							STM32F4_FSMC_SOURCE		
							STM32F4_GPIO_SOURCE		
							STM32F4_HASH_SOURCE				
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
		list(APPEND MCU_SYSTEM_FILES_SOURCES ${STM32F4xx_StdPeriph_Driver}/src/${${SYSTEM_SOURCE}}.c)
		list(APPEND MCU_SYSTEM_FILES_HEADERS ${STM32F4xx_StdPeriph_Driver}/inc/${${SYSTEM_SOURCE}}.h)
endforeach()
list (APPEND MCU_SYSTEM_FILES_SOURCES	${STM32F4xx_StdPeriph_Driver}/src/${STM32F4_CRYP_AES_SOURCE}.c
										${STM32F4xx_StdPeriph_Driver}/src/${STM32F4_CRYP_DES_SOURCE}.c
										${STM32F4xx_StdPeriph_Driver}/src/${STM32F4_CRYP_TDES_SOURCE}.c
										${STM32F4xx_StdPeriph_Driver}/src/${STM32F4_MD5_SOURCE}.c
										${STM32F4xx_StdPeriph_Driver}/src/${STM32F4_SHA1_SOURCE}.c)
add_definitions(-DUSE_STDPERIPH_DRIVER)

################################################################################

################################################################################
# find stm32 system file (CMSIS Cortex-M4 Device Peripheral Access Layer System Source File)
list(APPEND MCU_SYSTEM_FILES_SOURCES  "${SYSTEM_FILES_DIR}/system_stm32f4xx.c")
################################################################################


################################################################################
# find STM32F4xx Devices vector table
list(APPEND MCU_SYSTEM_FILES_SOURCES "${SYSTEM_FILES_DIR}/startup_stm32f4xx.s")
################################################################################


################################################################################
# find STM32F4xx Devices vector table
list(APPEND MCU_SYSTEM_FILES_SOURCES "${STM32F4_ROOT_DIR}/../generic_code/stm32fx/system_files/syscall.c")
################################################################################

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

SET(MCFLAGS "-mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16")

set (_RAM_ORIGIN			0x20000000)
set (_RAM_SIZE				128K)
set (_FLASH_ORIGIN			0x08000000)
set (_FLASH_SIZE			1024K)
set (_MIN_STACK_SIZE		0x2000)
set (_MIN_HEAP_SIZE			0x8000)
set (EXTRAM_MEMORY_AREA 	"CCMRAM (rw)     : ORIGIN = 0x10000000, LENGTH = 64K")
set (EXTRAM_MEMORY_SECTION	
".ccmram (NOLOAD):
{
	. = ALIGN(4);
	_ccm_ram_begin = .;
	*(.ccmram)
	*(.ccmram*)
	. = ALIGN(4);
	_ccm_ram_end = .;
} > CCMRAM")
configure_file(${CMAKE_CURRENT_LIST_DIR}/../../../generic_code/linker_script.ld ${CMAKE_BINARY_DIR}/)
set (LDSCRIPT "${CMAKE_BINARY_DIR}/linker_script.ld")


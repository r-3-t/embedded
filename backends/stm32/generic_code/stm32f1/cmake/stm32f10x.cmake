
list(APPEND MCU_HAL_FILES_SOURCES ${STM32F1_BOARD_SPECIFIC_FILES})
list(APPEND MCU_HAL_FILES_SOURCES ${STM32F1_ROOT_DIR}/hal/hal_stm32f1_clock.cpp)

################################################################################

set (SYSTEM_FILES_DIR "${STM32F10x_ROOT_DIR}/system_files")

################################################################################
# stm32f4 system headers
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
add_definitions(-DUSE_STDPERIPH_DRIVER)

foreach(SYSTEM_SOURCE ${STM32F1_SYSTEM_SOURCES})
		list(APPEND STM32F1_SYSTEM_FILES_SOURCES ${STM32F1xx_StdPeriph_Driver}/src/${${SYSTEM_SOURCE}}.c)
		list(APPEND STM32F1_SYSTEM_FILES_HEADERS ${STM32F1xx_StdPeriph_Driver}/inc/${${SYSTEM_SOURCE}}.h)
endforeach()

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
list(APPEND STM32F1_SYSTEM_FILES_SOURCES  "${STM32F10x_ROOT_DIR}/system_files/system_stm32f10x.c")
################################################################################

################################################################################
# find STM32F4xx Devices vector table
list(APPEND STM32F1_SYSTEM_FILES_SOURCES  "${SYSTEM_FILES_DIR}/startup_stm32f10x_md_vl.s")
################################################################################

################################################################################
# find STM32F4xx Devices vector table
list(APPEND STM32F1_SYSTEM_FILES_SOURCES  "${STM32F1_ROOT_DIR}/../stm32fx/system_files/syscall.c")
################################################################################


set (MCU_SYSTEM_FILES_SOURCES	${STM32F1_SYSTEM_FILES_SOURCES})
set (MCU_SYSTEM_FILES_HEADERS	${STM32F1_SYSTEM_FILES_HEADERS})


SET(MCFLAGS "-mlittle-endian -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd")
set (LDSCRIPT "${STM32F10x_ROOT_DIR}/system_files/stm32_flash.ld")

include (${CMAKE_CURRENT_LIST_DIR}/../../stm32fx/cmake/stm32fx.cmake)


add_definitions(-D'assert_param\(expr\)=\(\(void\)0\)')
set (STM32F1_STD_PERIPH_PATH		${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/)
set (STM32F1_STD_PERIPH_DRIVER		${STM32F1_STD_PERIPH_PATH}/STM32F10x_StdPeriph_Driver/)


set(STM_STD_LIB_FILES 	${STM32F1_STD_PERIPH_DRIVER}/src/misc.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_adc.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_bkp.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_can.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_cec.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_crc.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_dac.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_dbgmcu.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_dma.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_exti.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_flash.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_fsmc.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_gpio.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_i2c.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_iwdg.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_pwr.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_rcc.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_rtc.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_sdio.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_spi.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_tim.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_usart.c
						${STM32F1_STD_PERIPH_DRIVER}/src/stm32f10x_wwdg.c

						${STM32F1_STD_PERIPH_DRIVER}/inc/misc.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_adc.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_bkp.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_can.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_cec.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_crc.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_dac.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_dbgmcu.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_dma.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_exti.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_flash.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_fsmc.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_gpio.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_i2c.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_iwdg.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_pwr.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_rcc.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_rtc.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_sdio.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_spi.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_tim.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_usart.h
						${STM32F1_STD_PERIPH_DRIVER}/inc/stm32f10x_wwdg.h

						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.h

						
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/CoreSupport/core_cm3.c
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/CoreSupport/core_cm3.h
						)

################################################################################
################################ STM32F103 #####################################
################################################################################
add_mcu_lib(stm32f103 	${STM_STD_LIB_FILES}
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s
						)
target_compile_definitions(stm32f103 PUBLIC -DSTM32F10X_MD)
#add_mcu_hal(hal_stm32f103 stm32f103 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)

################################################################################
################################ STM32F100 #####################################
################################################################################
add_mcu_lib(stm32f100 	${STM_STD_LIB_FILES}
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md_vl.s
						)
target_compile_definitions(stm32f100 PUBLIC -DSTM32F10X_MD_VL)
#add_mcu_hal(hal_stm32f100 stm32f100 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)


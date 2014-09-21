add_definitions(-D'assert_param\(expr\)=\(\(void\)0\)')
set(STM32F4_STD_PERIPH_PATH ${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F4xx_DSP_StdPeriph_Lib_V1.3.0/Libraries/)
set(STM_STD_LIB_FILES 	${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/misc.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c

						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/misc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_crc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dac.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dbgmcu.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma2d.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_exti.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fmc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fsmc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_gpio.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_i2c.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_iwdg.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_ltdc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_pwr.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rcc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rtc.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sai.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sdio.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_spi.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_syscfg.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_tim.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_usart.h
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_wwdg.h

						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/arm_common_tables.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/arm_const_structs.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/arm_math.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_cm0.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_cm0plus.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_cm3.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_cm4.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_cm4_simd.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_cmFunc.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_cmInstr.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_sc000.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/core_sc300.h

						${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c

						)

################################################################################
################################ STM32F407 #####################################
################################################################################
add_mcu_lib(stm32f407 	${STM_STD_LIB_FILES}
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f40xx.s
						)
target_compile_definitions(stm32f407 PUBLIC -DSTM32F40_41xxx) 
target_include_directories(stm32f407 PUBLIC ${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/
											${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Include/
											${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/) 
#target_compile_definitions(stm32f407 PUBLIC -DSTM32F427_437xx) 
#target_compile_definitions(stm32f407 PUBLIC -DSTM32F401xx) 
#add_mcu_hal(hal_stm32f103 stm32f103 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)


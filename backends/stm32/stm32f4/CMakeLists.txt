add_definitions(-D'assert_param\(expr\)=\(\(void\)0\)')
set(STM32F4_STD_PERIPH_PATH ${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F4xx_DSP_StdPeriph_Lib_V1.3.0/Libraries/)
set(STM_STD_LIB_PATHS 	${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/src/
						${STM32F4_STD_PERIPH_PATH}/STM32F4xx_StdPeriph_Driver/inc/
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Include/
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Include/
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Source/Templates/
						)

################################################################################
################################ STM32F407 #####################################
################################################################################
add_mcu_lib(stm32f407 	${STM_STD_LIB_PATHS}
						${STM32F4_STD_PERIPH_PATH}/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f40xx.s
						)
target_compile_definitions(stm32f407 PUBLIC -DSTM32F40_41xxx) 
#target_compile_definitions(stm32f407 PUBLIC -DSTM32F427_437xx) 
#target_compile_definitions(stm32f407 PUBLIC -DSTM32F401xx) 
#add_mcu_hal(hal_stm32f103 stm32f103 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)


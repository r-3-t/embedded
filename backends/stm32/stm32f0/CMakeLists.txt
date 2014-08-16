add_definitions(-D'assert_param\(expr\)=\(\(void\)0\)')
set(STM_STD_LIB_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/STM32F0xx_StdPeriph_Driver/src
						${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/STM32F0xx_StdPeriph_Driver/inc
						${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/CMSIS/Device/ST/STM32F0xx/Include/
						${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/CMSIS/Include
						${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c
						)
add_mcu_lib(stm32f051 	${STM_STD_LIB_PATHS}
						${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F0xx_StdPeriph_Lib_V1.3.1/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/TrueSTUDIO/startup_stm32f051.s
						)
#target_compile_definitions(stm32f051 PUBLIC -DSTM32F051)


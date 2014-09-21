add_mcu_hal(hal_stm32f407 stm32f407 ${CMAKE_CURRENT_LIST_DIR}/hal ${CMAKE_CURRENT_LIST_DIR}/hal)
target_include_directories(hal_stm32f407 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
												${CMAKE_CURRENT_LIST_DIR}/stm32f4/system_files/STM32F4xx_DSP_StdPeriph_Lib_V1.3.0/Libraries/STM32F4xx_StdPeriph_Driver/inc
												${CMAKE_CURRENT_LIST_DIR}/stm32f4/system_files/STM32F4xx_DSP_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/Device/ST/STM32F4xx/Include/
												${CMAKE_CURRENT_LIST_DIR}/stm32f4/system_files/STM32F4xx_DSP_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/Include
												$<TARGET_PROPERTY:pinout,INCLUDE_DIRECTORIES>)
target_compile_definitions(hal_stm32f407 PUBLIC -DSTM32F40_41xxx) 

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/stm32f4/ ${CMAKE_CURRENT_BINARY_DIR}/stm32f4/)

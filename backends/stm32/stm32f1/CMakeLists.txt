add_definitions(-D'assert_param\(expr\)=\(\(void\)0\)')
set(STM32F1_STD_PERIPH_PATH ${CMAKE_CURRENT_SOURCE_DIR}/system_files/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/)
set(STM_STD_LIB_PATHS 	${STM32F1_STD_PERIPH_PATH}/STM32F10x_StdPeriph_Driver/src/
						${STM32F1_STD_PERIPH_PATH}/STM32F10x_StdPeriph_Driver/inc/
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/CoreSupport/
						)

add_mcu_lib(stm32f103 	${STM_STD_LIB_PATHS}
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s
						)
target_compile_definitions(stm32f103 PUBLIC -DSTM32F10X_MD)
add_mcu_hal(hal_stm32f103 stm32f103 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)
target_include_directories(hal_stm32f103 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

add_mcu_lib(stm32f100 	${STM_STD_LIB_PATHS}
						${STM32F1_STD_PERIPH_PATH}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md_vl.s
						)
target_compile_definitions(stm32f100 PUBLIC -DSTM32F10X_MD_VL)
add_mcu_hal(hal_stm32f100 stm32f100 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)
target_include_directories(hal_stm32f100 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

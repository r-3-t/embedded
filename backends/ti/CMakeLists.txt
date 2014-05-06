include_directories(include/)

set(TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/stellaris/system_files/)
set(TI_STELLARIS_LIBRARY_PATHS 	${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/stellaris/driverlib/
								${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/stellaris/
								${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/
								${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/stellaris/inc/
						)
add_mcu_lib(lm4f120xl 	${TI_STELLARIS_LIBRARY_PATHS})

target_compile_definitions(lm4f120xl PUBLIC -Dgcc)

add_mcu_hal(hal_lm4f120xl lm4f120xl ${CMAKE_CURRENT_SOURCE_DIR}/stellaris/hal ${CMAKE_CURRENT_SOURCE_DIR}/stellaris/hal)

target_include_directories(hal_lm4f120xl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

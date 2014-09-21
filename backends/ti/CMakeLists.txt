include_directories(include/)

set(TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/stellaris/system_files/)

set(TI_STELLARIS_LIBRARY_FILES 	#${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/stellaris/driverlib/
								#${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/stellaris/

								${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/syscall.c
								${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/startup_lm4f120.c

								#${TI_STELLARIS_PERIPH_DRIVER_LIBRARY_PATH}/stellaris/inc/
						)

register_mcu(lm4f120xl)
set (project_lm4f120xl ${CMAKE_CURRENT_SOURCE_DIR}/project_lm4f120xl.cmake CACHE INTERNAL "")


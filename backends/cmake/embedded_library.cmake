if (_EMBEDDED_LIBRARY)
	return()
endif()
set (_EMBEDDED_LIBRARY on CACHE STRING "_EMBEDDED_LIBRARY")

include (compile_flag_helper)

# whatever is the CMAKE_BUILD_TYPE we force the system files to be compiled in release mode
set_compile_flags_release_config(MCU_SYSTEM_FILES_SOURCES)


# by default the hal is compiled with the release flags even in debug mode
if(DEBUG_HAL)
	set_compile_flags_current_config(MCU_HAL_FILES_SOURCES)
else()
	set_compile_flags_release_config(MCU_HAL_FILES_SOURCES)
endif()

include_directories(${BASE_HAL_DIR}/)
include_directories(${HAL_DIR}/)
include_directories(${TARGET_INCLUDE_DIRECTORIES})

add_library(embedded 		${MCU_HAL_FILES_SOURCES}
							${MCU_SYSTEM_FILES_HEADERS}
							${MCU_SYSTEM_FILES_SOURCES})

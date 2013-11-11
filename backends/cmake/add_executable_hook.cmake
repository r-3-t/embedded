if (_ADD_EXECUTABLE_HOOK)
	return()
endif()
set (_ADD_EXECUTABLE_HOOK on PARENT_SCOPE)

# save the default debug/release flags
SET(SAVE_CMAKE_C_FLAGS_DEBUG 		${CMAKE_C_FLAGS_DEBUG})
SET(SAVE_CMAKE_CXX_FLAGS_DEBUG 		${CMAKE_CXX_FLAGS_DEBUG})
SET(SAVE_CMAKE_ASM_FLAGS_DEBUG 		${CMAKE_ASM_FLAGS_DEBUG})
SET(SAVE_CMAKE_C_FLAGS_RELEASE 		${CMAKE_C_FLAGS_RELEASE})
SET(SAVE_CMAKE_CXX_FLAGS_RELEASE 	${CMAKE_CXX_FLAGS_RELEASE})
SET(SAVE_CMAKE_ASM_FLAGS_RELEASE 	${CMAKE_ASM_FLAGS_RELEASE})

# clear the specific debug / release flags
set( CMAKE_C_FLAGS_DEBUG			"")
set( CMAKE_CXX_FLAGS_DEBUG			"")
set( CMAKE_ASM_FLAGS_DEBUG			"")
set( CMAKE_C_FLAGS_RELEASE			"")
set( CMAKE_CXX_FLAGS_RELEASE		"")
set( CMAKE_ASM_FLAGS_RELEASE		"")

include (compile_flag_helper)

function(add_executable ...)

	# whatever is the CMAKE_BUILD_TYPE we force the system files to be compiled in release mode
	set_compile_flags(	MCU_SYSTEM_FILES_SOURCES
						SAVE_CMAKE_C_FLAGS_RELEASE
						SAVE_CMAKE_CXX_FLAGS_RELEASE
						SAVE_CMAKE_ASM_FLAGS_RELEASE)

	# get the build type in upper case
	string (TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)

	# by default the hal is compiled with the release flags even in debug mode
	if(DEBUG_HAL)
		set_compile_flags(	MCU_HAL_FILES_SOURCES
							SAVE_CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UPPER}
							SAVE_CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}
							SAVE_CMAKE_ASM_FLAGS_${CMAKE_BUILD_TYPE_UPPER})
	else()
		set_compile_flags(	MCU_HAL_FILES_SOURCES
							SAVE_CMAKE_C_FLAGS_RELEASE
							SAVE_CMAKE_CXX_FLAGS_RELEASE
							SAVE_CMAKE_ASM_FLAGS_RELEASE)
	endif()

	# get the files list given buy add_executable (we remove the eecutable name)
	set (LIST_SOURCES_FILE ${ARGV})
	list (REMOVE_AT LIST_SOURCES_FILE 0)

	# the the compile flags accordingly to the cmake_build_type
	set_compile_flags(	LIST_SOURCES_FILE
						SAVE_CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UPPER}
						SAVE_CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}
						SAVE_CMAKE_ASM_FLAGS_${CMAKE_BUILD_TYPE_UPPER})

	_add_executable(${ARGV} 	${MCU_HAL_FILES_SOURCES}
								${MCU_SYSTEM_FILES_HEADERS}
								${MCU_SYSTEM_FILES_SOURCES})

	list (GET ARGV 0 _executable_name)
	add_dependencies(${_executable_name} _stm32f10x_core_library)
endfunction()


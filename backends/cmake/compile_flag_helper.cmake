if (_COMPILE_FLAGS)
	return()
endif()
set (_COMPILE_FLAGS on CACHE STRING "_COMPILE_FLAGS")


# save the default debug/release flags
SET(SAVE_CMAKE_C_FLAGS_DEBUG 		${CMAKE_C_FLAGS_DEBUG}
					 CACHE STRING "SAVE_CMAKE_C_FLAGS_DEBUG")
SET(SAVE_CMAKE_CXX_FLAGS_DEBUG 		${CMAKE_CXX_FLAGS_DEBUG}
					 CACHE STRING "SAVE_CMAKE_CXX_FLAGS_DEBUG")
SET(SAVE_CMAKE_ASM_FLAGS_DEBUG 		${CMAKE_ASM_FLAGS_DEBUG}
					 CACHE STRING "SAVE_CMAKE_ASM_FLAGS_DEBUG")
SET(SAVE_CMAKE_C_FLAGS_RELEASE 		${CMAKE_C_FLAGS_RELEASE}
					 CACHE STRING "SAVE_CMAKE_C_FLAGS_RELEASE")
SET(SAVE_CMAKE_CXX_FLAGS_RELEASE 	${CMAKE_CXX_FLAGS_RELEASE}
					 CACHE STRING "SAVE_CMAKE_CXX_FLAGS_RELEASE")
SET(SAVE_CMAKE_ASM_FLAGS_RELEASE 	${CMAKE_ASM_FLAGS_RELEASE}
					 CACHE STRING "SAVE_CMAKE_ASM_FLAGS_RELEASE")

# clear the specific debug / release flags
set( CMAKE_C_FLAGS_DEBUG			""
					 CACHE STRING "CMAKE_C_FLAGS_DEBUG" FORCE)
set( CMAKE_CXX_FLAGS_DEBUG			""
					 CACHE STRING "CMAKE_CXX_FLAGS_DEBUG" FORCE)
set( CMAKE_ASM_FLAGS_DEBUG			""
					 CACHE STRING "CMAKE_ASM_FLAGS_DEBUG" FORCE)
set( CMAKE_C_FLAGS_RELEASE			""
					 CACHE STRING "CMAKE_C_FLAGS_RELEASE" FORCE)
set( CMAKE_CXX_FLAGS_RELEASE		""
					 CACHE STRING "CMAKE_CXX_FLAGS_RELEASE" FORCE)
set( CMAKE_ASM_FLAGS_RELEASE		""
					 CACHE STRING "CMAKE_ASM_FLAGS_RELEASE" FORCE)

function (set_compile_flags file_list c_compile_flag cxx_compile_flag asm_compile_flag)

	foreach (file ${${file_list}})
		get_filename_component(file_ext ${file} EXT)
		set (COMPILE_FLAGS "")
		if (${file_ext} MATCHES ".*\\.cpp$")
			set (COMPILE_FLAGS	${${cxx_compile_flag}})
		elseif (${file_ext} MATCHES ".*\\.c$")
			set (COMPILE_FLAGS	${${c_compile_flag}})
		elseif (${file_ext} MATCHES ".*\\.s$")
			set (COMPILE_FLAGS	${${asm_compile_flag}})
		endif()

		if (COMPILE_FLAGS)
			set_source_files_properties(${file} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
		endif()
	endforeach()

endfunction()

function (set_compile_flags_current_config file_list)
	# get the build type in upper case
	string (TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)

	set_compile_flags (${file_list} SAVE_CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UPPER}
									SAVE_CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}
									SAVE_CMAKE_ASM_FLAGS_${CMAKE_BUILD_TYPE_UPPER})
endfunction()

function (set_compile_flags_release_config file_list)
	set_compile_flags (${file_list} SAVE_CMAKE_C_FLAGS_RELEASE
									SAVE_CMAKE_CXX_FLAGS_RELEASE
									SAVE_CMAKE_ASM_FLAGS_RELEASE)
endfunction()

if (_ADD_EXECUTABLE_HOOK)
	return()
endif()
set (_ADD_EXECUTABLE_HOOK on CACHE STRING "add_executable hook")

include (compile_flag_helper)

function(add_executable ...)
	# get the files list given buy add_executable (we remove the eecutable name)
	set (LIST_SOURCES_FILE ${ARGV})
	list (REMOVE_AT LIST_SOURCES_FILE 0)

	# the the compile flags accordingly to the cmake_build_type
	set_compile_flags_current_config (LIST_SOURCES_FILE)

	_add_executable(${ARGV})
endfunction()


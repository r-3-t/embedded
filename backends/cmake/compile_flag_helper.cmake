if (_COMPILE_FLAGS)
	return()
endif()


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
		else ()
			message ("ignoring file : ${file}")
		endif()

		if (COMPILE_FLAGS)
			set_source_files_properties(${file} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
			#message ("setting compile flag (${COMPILE_FLAGS}) for '${file}'")
		endif()
	endforeach()

endfunction()

set (_COMPILE_FLAGS on)

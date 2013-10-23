if (_SUPPORTED_ARCHITECTURE_INCLUDED)
	return()
endif()
set (_SUPPORTED_ARCHITECTURE_INCLUDED on)

# This is the root dir of all supported mcu
list (APPEND SUPPORTED_MCU_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../stm32
									${CMAKE_CURRENT_LIST_DIR}/../ti)

# helper to get available architecture
function (get_available_architecture arch_list)
	foreach (mcu_root_dir ${SUPPORTED_MCU_ROOT_DIR})
		file(GLOB sub_dir_for_current_mcu ${mcu_root_dir}/*)
		list (APPEND SUB_DIRECTORIES ${sub_dir_for_current_mcu})
	endforeach()

	foreach (DIRECTORY ${SUB_DIRECTORIES})

		if (IS_DIRECTORY ${DIRECTORY})

			get_filename_component(SUB_DIR_NAME ${DIRECTORY} NAME)

			if (IS_DIRECTORY ${DIRECTORY}/cmake)
				
				if (EXISTS ${DIRECTORY}/cmake/${SUB_DIR_NAME}.cmake)
					list (APPEND TEMP_LIST ${SUB_DIR_NAME})
				endif()

			endif()

		endif()

	endforeach()

	set (${arch_list} ${TEMP_LIST} PARENT_SCOPE)

endfunction()

# print on stdout the available architectures
function (show_available_arch)

	get_available_architecture(SUPPORTED_ARCHITECTURE)

	message ("supported arch : ${SUPPORTED_ARCHITECTURE}")

	list (LENGTH SUPPORTED_ARCHITECTURE ARCHITECTURE_COUNT)

	if (${ARCHITECTURE_COUNT} EQUAL 0)
		message (FATAL_ERROR "There is no available architecture")
	endif()

	message ("Found ${ARCHITECTURE_COUNT} architecture(s) :")
	foreach (ARCH ${SUPPORTED_ARCHITECTURE})
		message ("\t- ${ARCH}")
	endforeach()

endfunction()

function (get_cmake_path_for_arch arch cmake_path)

	foreach (mcu_root_dir ${SUPPORTED_MCU_ROOT_DIR})
		file(GLOB sub_dir_for_current_mcu ${mcu_root_dir}/*)
		list (APPEND SUB_DIRECTORIES ${sub_dir_for_current_mcu})
	endforeach()

	foreach (DIRECTORY ${SUB_DIRECTORIES})
		if (EXISTS ${DIRECTORY}/cmake/${arch}.cmake)
			set (${cmake_path} ${DIRECTORY}/cmake/${arch}.cmake PARENT_SCOPE)
			return()
		endif()
	endforeach()

endfunction()
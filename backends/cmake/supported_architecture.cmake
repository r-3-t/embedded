

# This is the root dir of all supported mcu
set (SUPPORTED_MCU_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../stm32)

# helper to get available architecture
function (get_available_architecture arch_list)
	file(GLOB SUB_DIRECTORIES ${SUPPORTED_MCU_ROOT_DIR}/*)

	foreach (DIRECTORY ${SUB_DIRECTORIES})

		if (IS_DIRECTORY ${DIRECTORY})

			get_filename_component(SUB_DIR_NAME ${DIRECTORY} NAME)

			if (IS_DIRECTORY ${DIRECTORY}/cmake)
				
				if (EXISTS ${DIRECTORY}/cmake/${SUB_DIR_NAME}.cmake)
					list (APPEND ${arch_list} ${SUB_DIR_NAME})
				endif()

			endif()

		endif()

	endforeach()

endfunction()

# print on stdout the available architectures
function (show_available_arch)

	get_available_architecture(SUPPORTED_ARCHITECTURE)


	list (LENGTH SUPPORTED_ARCHITECTURE ARCHITECTURE_COUNT)

	if (${ARCHITECTURE_COUNT} EQUAL 0)
		message (FATAL_ERROR "There is no available architecture")
	endif()

	message ("Found ${ARCHITECTURE_COUNT} architecture(s) :")
	foreach (ARCH ${SUPPORTED_ARCHITECTURE})
		message ("\t- ${ARCH}")
	endforeach()

endfunction()


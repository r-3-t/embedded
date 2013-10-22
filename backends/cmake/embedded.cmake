if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE Release)
endif()

# This is the root dir of all supported mcu
set (SUPPORTED_MCU_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../stm32)

# this is the hal base folder (located at the very top of the project)
set (BASE_HAL_DIR			"${CMAKE_CURRENT_LIST_DIR}/../../hal/")

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

# if the user has not given a arch : print the available arch and return 
if (NOT arch)
	show_available_arch()
	message (FATAL_ERROR "Please run cmake again with option -Darch=<architecture>")
	return()
endif()

# if the given arch is not supported, return
if (NOT EXISTS ${SUPPORTED_MCU_ROOT_DIR}/${arch}/cmake/${arch}.cmake)
	show_available_arch()
	message (FATAL_ERROR "${arch} is not a valid architecure")
	return()
endif()

# the architecture file must :
#    * set the implemented hal file thanks to the variables :
#        * set (HAL_IMPLEMENTED_LED 			********.hpp)
#        * set (HAL_IMPLEMENTED_CLOCK			********.hpp)
#        * set (HAL_IMPLEMENTED_UART			********.hpp)
#        * set (HAL_IMPLEMENTED_GPIO			********.hpp)
#        * set (HAL_IMPLEMENTED_SPI				********hpp)
#        * set (HAL_IMPLEMENTED_PINOUT			********.hpp)
#        * set the MCU_HAL_FILES_SOURCES variable (which must contain all .cpp hal files)
#    * set the MCU_SYSTEM_FILES_SOURCES and MCU_SYSTEM_FILES_HEADERS variables. These files are those given by the board vendors
#    * set the MCFLAGS (e.g "-mlittle-endian -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd")
#    * set the LDSCRIPT (e.g. "xxx/yyyy/zzzzz/stm32_flash.ld")
include (${SUPPORTED_MCU_ROOT_DIR}/${arch}/cmake/${arch}.cmake)

# set the hal thanks to the preceding include file
include(copy_hal_files_helper)

# include the arm-none-eabi-gcc which set the compiler
include (arm-none-eabi-gcc)

# hook add executable to append the system ans hal files
include (add_executable_hook)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../backends/cmake/)

project (pinout)

include (supported_architecture)

# this is the hal base folder (located at the very top of the project)
set (BASE_HAL_DIR			"${CMAKE_CURRENT_LIST_DIR}/../../hal/")


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



include (${SUPPORTED_MCU_ROOT_DIR}/${arch}/cmake/${arch}.cmake)

if (NOT HAL_IMPLEMENTED_PINOUT_CPP)
	message (FATAL_ERROR "Architecture ${arch} doest not support pinout")
	return()
endif()


if (NOT EXISTS ${HAL_IMPLEMENTED_PINOUT_CPP})
	message (" ::: ${HAL_IMPLEMENTED_PINOUT_CPP}")
	message (FATAL_ERROR ">> Architecture ${arch} doest not support pinout")
	return()
endif()

configure_file(${CMAKE_CURRENT_LIST_DIR}/../../hal/pinout.hpp ${CMAKE_BINARY_DIR} COPY_ONLY)
include_directories(${CMAKE_BINARY_DIR})

add_definitions(-std=c++11)
if (APPLE)
	add_definitions(-stdlib=libc++)
	SET(CMAKE_CXX_LINK_FLAGS "-std=c++11 -stdlib=libc++")
endif()

add_executable (${PROJECT_NAME}	main.cpp ${HAL_IMPLEMENTED_PINOUT_CPP} )

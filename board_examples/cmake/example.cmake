
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../backends/cmake/)
include(embedded)

if (PROJECT_DRIVERS)
	foreach (driver ${PROJECT_DRIVERS})
		if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/../../drivers/${driver})
			include_directories(${CMAKE_CURRENT_LIST_DIR}/../../drivers/${driver}/)
			file (GLOB cpp_driver_files ${CMAKE_CURRENT_LIST_DIR}/../../drivers/${driver}/*.cpp)
			file (GLOB hpp_driver_files ${CMAKE_CURRENT_LIST_DIR}/../../drivers/${driver}/*.hpp)
			list (APPEND PROJECT_SOURCES ${cpp_driver_files} ${hpp_driver_files})
		endif()
	endforeach()
endif()

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf		${PROJECT_SOURCES})

ADD_CUSTOM_TARGET(${CMAKE_PROJECT_NAME}.bin ALL DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)

add_custom_command (TARGET ${CMAKE_PROJECT_NAME}.elf
					POST_BUILD
					COMMAND arm-none-eabi-size $<TARGET_FILE:${CMAKE_PROJECT_NAME}.elf>)

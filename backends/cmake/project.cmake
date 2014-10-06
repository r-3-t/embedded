set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/)

#configure compiler
include(arm-none-eabi-gcc)

#common compile flags
set(COMMON_COMPILE_FLAGS "-O0 -g -Werror -Wno-error=cpp -Wextra -Warray-bounds -ffunction-sections -fdata-sections")
#set(COMMON_COMPILE_FLAGS "-Os -Werror -Wextra -Warray-bounds -ffunction-sections -fdata-sections")
#-u _printf_float
set(COMMON_LINK_FLAGS "-Wl,--gc-sections --specs=nano.specs -u _printf_float")

#load all mcus
include(mcus)

#selected mcu
if (mcu)
	string(TOUPPER ${mcu} MCU)
endif(mcu)

#build linker script
set (_FLASH_ORIGIN		${${MCU}_FLASH_ORIGIN})
set (_RAM_ORIGIN		${${MCU}_RAM_ORIGIN})
set (_RAM_SIZE			${${MCU}_RAM_SIZE})
set (_FLASH_SIZE		${${MCU}_FLASH_SIZE})
set (_MIN_STACK_SIZE		${${MCU}_MIN_STACK_SIZE})
set (_MIN_HEAP_SIZE		${${MCU}_MIN_HEAP_SIZE})

configure_file(${CMAKE_CURRENT_LIST_DIR}/../common/linker_script.ld ${CMAKE_BINARY_DIR}/)
set (LDSCRIPT "${CMAKE_BINARY_DIR}/linker_script.ld")

#GDB / OpenOCD
set (GDBINIT_CONTENT
"
target remote localhost:3333
monitor reset init
")

file (WRITE ${CMAKE_BINARY_DIR}/.gdbinit ${GDBINIT_CONTENT})
file (WRITE ${CMAKE_BINARY_DIR}/openocd.cfg ${${MCU}_OPENOCDCFG_CONTENT})

#provide hal interface files
include_directories(${CMAKE_CURRENT_LIST_DIR}/../../hal/)

function (register_mcu mcu_name)
	#add MCU to list of supported MCUs
	set_property(GLOBAL APPEND PROPERTY MCU_LIBS ${mcu_name})
endfunction (register_mcu mcu_name)

function (add_mcu_lib mcu_lib_name)
	list(REMOVE_AT ARGV 0)
	set(sources ${ARGV})

	#add all sources for this MCU
	foreach (source ${sources})
		if (IS_DIRECTORY ${source})
			file(GLOB directory_source_files ${source}/*)
			LIST(APPEND source_files ${directory_source_files})
			LIST(APPEND directories_to_include ${source})
		else(IS_DIRECTORY ${source})
			LIST(APPEND source_files ${source})
		endif(IS_DIRECTORY ${source})
	endforeach(source)

	#add MCU target
	add_library(${mcu_lib_name} OBJECT ${source_files})

	#add previously found directories to includes
	target_include_directories(${mcu_lib_name} PUBLIC ${directories_to_include})

	string(TOUPPER ${mcu_lib_name} MCU_LIB_NAME)

	#add needed flags for this MCU
	set_target_properties(${mcu_lib_name} PROPERTIES COMPILE_FLAGS ${${MCU_LIB_NAME}_COMPILE_FLAGS})

endfunction(add_mcu_lib)

function (add_mcu_hal mcu_hal_name mcu_lib_name source_path header_path)
	file(GLOB source_files ${source_path}/*)
	file(GLOB header_files ${header_path}/*.h*)

	add_library(${mcu_hal_name} OBJECT ${source_files} ${header_files})

	foreach(header ${header_files})
		LIST(APPEND include_headers -include${header})
	endforeach(header)

	target_include_directories(${mcu_hal_name} PUBLIC ${header_path})

	string(TOUPPER ${mcu_lib_name} MCU_LIB_NAME)

	target_compile_options(${mcu_hal_name} PUBLIC ${include_headers})

	set_target_properties(${mcu_hal_name} PROPERTIES COMPILE_FLAGS ${${MCU_LIB_NAME}_COMPILE_FLAGS})

	#target_link_libraries(${mcu_hal_name} pinout)

	#target_link_libraries(${mcu_hal_name} ${mcu_lib_name})

endfunction(add_mcu_hal)

#add all avaible MCUs
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../backends/ ${CMAKE_CURRENT_BINARY_DIR}/backends/)

function(show_available_mcus)

	get_property(MCU_LIBS GLOBAL PROPERTY MCU_LIBS)
	message(STATUS "Available MCUs :")
	foreach(mcu_lib ${MCU_LIBS})
		message(STATUS "${mcu_lib}")
	endforeach(mcu_lib ${MCU_LIBS})

endfunction(show_available_mcus)

function (build_project project_name)
	if (NOT mcu)
		show_available_mcus()
		message(FATAL_ERROR "No MCU selected ! Use -Dmcu=")
		return()
	endif(NOT mcu)

	get_property(MCU_LIBS GLOBAL PROPERTY MCU_LIBS)
	list (FIND MCU_LIBS ${mcu} IsMcuExists)
	if (IsMcuExists EQUAL -1)		
		message(FATAL_ERROR "Invalid MCU selected !!! Please selct one in : ${MCU_LIBS}")
		return()
	endif(IsMcuExists EQUAL -1)


	if (NOT EXISTS ${project_${mcu}})
		message (FATAL_ERROR "'backend '${mcu}' does not provide a project_${mcu} variable that contains the file to create ${mcu} library' ('${project_${mcu}}')")
	endif()

	# call the mcu cmake file
	include(${project_${mcu}})

	list(REMOVE_AT ARGV 0)
	set(source_files ${ARGV})

	add_executable(${project_name} ${source_files} $<TARGET_OBJECTS:syscall> $<TARGET_OBJECTS:error> $<TARGET_OBJECTS:hal_${mcu}> $<TARGET_OBJECTS:${mcu}> $<TARGET_OBJECTS:pinout>)
	target_link_libraries(${project_name}  ${${MCU}_LINK_FLAGS} -T${LDSCRIPT})

	include_directories($<TARGET_PROPERTY:pinout,INCLUDE_DIRECTORIES>)
	include_directories($<TARGET_PROPERTY:${mcu},INCLUDE_DIRECTORIES>)
	#include_directories($<TARGET_PROPERTY:hal_${mcu},INCLUDE_DIRECTORIES>)

	target_compile_options(${project_name} PUBLIC $<TARGET_PROPERTY:hal_${mcu},COMPILE_OPTIONS>)
	target_compile_definitions(${project_name} PUBLIC $<TARGET_PROPERTY:hal_${mcu},COMPILE_DEFINITIONS>)

	#TODO: process automaticaly	
	set_target_properties(${project_name} pinout syscall error PROPERTIES COMPILE_FLAGS ${${MCU}_COMPILE_FLAGS})

	#Templates
	math(EXPR NUM_LED "${${MCU}_NUM_LED} - 1")
	message (STATUS "NUM_LED : ${NUM_LED}")
	foreach (led_number RANGE ${NUM_LED})
		message (STATUS "Add led ${led_number}")
		list(APPEND MCU_TEMPLATE LED${led_number}_PORT=${${MCU}_LED${led_number}_PORT};LED${led_number}_PIN=${${MCU}_LED${led_number}_PIN};)
	endforeach()
	list(APPEND MCU_TEMPLATE BUTTON0_PORT=${${MCU}_BUTTON0_PORT};BUTTON0_PIN=${${MCU}_BUTTON0_PIN})
	list(APPEND MCU_TEMPLATE DEFAULT_UART=${${MCU}_DEFAULT_UART};DEFAULT_TIMER=${${MCU}_DEFAULT_TIMER})

	target_compile_definitions(${project_name} PUBLIC ${MCU_TEMPLATE})

	add_custom_command (TARGET ${project_name} POST_BUILD COMMAND arm-none-eabi-size $<TARGET_FILE:${project_name}>)

endfunction(build_project)

function (build_library library_name)
	if (NOT mcu)
		show_available_mcus()
		message(FATAL_ERROR "No MCU selected ! Use -Dmcu=")
		return()
	endif(NOT mcu)

	list(REMOVE_AT ARGV 0)
	set(source_files ${ARGV})

	add_library(${library_name} OBJECT ${source_files})

	#TODO: process automaticaly	
	set_target_properties(${library_name} PROPERTIES COMPILE_FLAGS ${${MCU}_COMPILE_FLAGS})

	#Templates
	math(EXPR NUM_LED "${${MCU}_NUM_LED} - 1")
	message (STATUS "NUM_LED : ${NUM_LED}")
	foreach (led_number RANGE ${NUM_LED})
		message (STATUS "Add led ${led_number}")
		list(APPEND MCU_TEMPLATE LED${led_number}_PORT=${${MCU}_LED${led_number}_PORT};LED${led_number}_PIN=${${MCU}_LED${led_number}_PIN};)
	endforeach()
	list(APPEND MCU_TEMPLATE BUTTON0_PORT=${${MCU}_BUTTON0_PORT};BUTTON0_PIN=${${MCU}_BUTTON0_PIN})
	list(APPEND MCU_TEMPLATE DEFAULT_UART=${${MCU}_DEFAULT_UART};DEFAULT_TIMER=${${MCU}_DEFAULT_TIMER})

	target_compile_definitions(${library_name} PUBLIC ${MCU_TEMPLATE})

endfunction(build_library)

#add optional arduino frontend
#include(${CMAKE_CURRENT_LIST_DIR}/../../frontends/arduino/arduino.cmake)

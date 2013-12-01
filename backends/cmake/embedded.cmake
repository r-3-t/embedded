if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE Release)
endif()

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
get_cmake_path_for_arch(${arch} arch_cmake_path)
if (NOT EXISTS ${arch_cmake_path})
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
#        * set (HAL_IMPLEMENTED_EXTINT			********.hpp)
#        * set (HAL_IMPLEMENTED_PWM			********.hpp)
#        * set (HAL_IMPLEMENTED_TIMER			********.hpp)
#        * set (HAL_IMPLEMENTED_SPI				********hpp)
#        * set (HAL_IMPLEMENTED_PINOUT			********.hpp)
#        * set the MCU_HAL_FILES_SOURCES variable (which must contain all .cpp hal files)
#    * set the MCU_SYSTEM_FILES_SOURCES and MCU_SYSTEM_FILES_HEADERS variables. These files are those given by the board vendors
#    * set the MCFLAGS (e.g "-mlittle-endian -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd")
#    * set the LDSCRIPT (e.g. "xxx/yyyy/zzzzz/stm32_flash.ld")
include (${arch_cmake_path})

# set the hal thanks to the preceding include file
include(copy_hal_files_helper)

# include the arm-none-eabi-gcc which set the compiler
include (arm-none-eabi-gcc)

# hook add executable to append the system ans hal files
include (add_executable_hook)

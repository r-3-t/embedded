#if (_ARM_NONE_EABI_GCC)
#	return()
#endif()
#set (_ARM_NONE_EABI_GCC on CACHE STRING "_ARM_NONE_EABI_GCC")

INCLUDE(CMakeForceCompiler)

if (NOT MCFLAGS)
	message("MCFLAGS is not set, abort ....")
endif()

if (NOT LDSCRIPT)
	message("LDSCRIPT is not set, abort ....")
endif()

################################################################################
# cross compilation tools
find_program(CROSS_GCC_FULL_PATH "arm-none-eabi-gcc")
get_filename_component(CROSS_COMPIL_TOOLS ${CROSS_GCC_FULL_PATH} PATH)
if (NOT EXISTS ${CROSS_COMPIL_TOOLS})
	message (FATAL_ERROR "Can't find cross compilation tool chain")
endif()

SET(CPREF				${CROSS_COMPIL_TOOLS}/arm-none-eabi)
SET(CMAKE_C_COMPILER	${CPREF}-gcc CACHE STRING "arm-none-eabi-gcc")
SET(CMAKE_CXX_COMPILER	${CPREF}-g++ CACHE STRING "arm-none-eabi-g++")
SET(AS					"${CROSS_COMPIL_TOOLS}/arm-none-eabi-gcc -x -assembler-with-cpp"  CACHE STRING "arm-none-eabi-as")
SET(CMAKE_AR			${CPREF}-ar CACHE STRING "arm-none-eabi-ar")
SET(CMAKE_LD			${CPREF}-ld CACHE STRING "arm-none-eabi-ld")
SET(NM					${CPREF}-nm CACHE STRING "arm-none-eabi-nm")
SET(OBJCOPY				${CPREF}-objcopy CACHE STRING "arm-none-eabi-objcopy")
SET(OBJDUMP				${CPREF}-objdump CACHE STRING "arm-none-eabi-objdump")
SET(READELF				${CPREF}-readelf CACHE STRING "arm-none-eabi-readelf")
SET(CMAKE_RANLIB		${CPREF}-ranlib CACHE STRING "arm-none-eabi-ranlib")

CMAKE_FORCE_C_COMPILER(${CPREF}-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(${CPREF}-g++ GNU)
################################################################################

#fix '-rdynamic' cmake 2.8.9 bug
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" CACHE STRING "CMAKE_SHARED_LIBRARY_LINK_C_FLAGS")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" CACHE STRING "CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS")

# here is the target environment is located
SET(CMAKE_FIND_ROOT_PATH	${CROSS_COMPIL_TOOLS})
include_directories(${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/)
include_directories(${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/c++/4.7.4)

if (NOT OPTIM_LEVEL)
	set (OPTIM_LEVEL "3")
endif()

if (NOT DO_NOT_USE_LTO)
	set (COMPIL_FLAGS_LTO "-flto")
	set (LINK_FLAGS_LTO "-O${OPTIM_LEVEL} -flto")
endif()

SET(CMAKE_ASM_FLAGS "${MCFLAGS}"  CACHE STRING "CMAKE_ASM_FLAGS" FORCE)
SET(CMAKE_C_FLAGS "${MCFLAGS} -Wall -Wextra -Warray-bounds -ffunction-sections -fdata-sections"
					 CACHE STRING "CMAKE_C_FLAGS" FORCE)
SET(CMAKE_CXX_FLAGS "${MCFLAGS} -std=c++11 -Wall -Wextra -Warray-bounds -fno-builtin -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections"
					 CACHE STRING "CMAKE_CXX_FLAGS" FORCE)

SET(CMAKE_C_FLAGS_DEBUG "-O1 -g"
					 CACHE STRING "CMAKE_C_FLAGS_DEBUG" FORCE)
SET(CMAKE_CXX_FLAGS_DEBUG "-O1 -g"
					 CACHE STRING "CMAKE_CXX_FLAGS_DEBUG" FORCE)
SET(CMAKE_ASM_FLAGS_DEBUG "-g"
					 CACHE STRING "CMAKE_ASM_FLAGS_DEBUG" FORCE)

SET(CMAKE_C_FLAGS_RELEASE "-O${OPTIM_LEVEL} ${COMPIL_FLAGS_LTO}"
					 CACHE STRING "CMAKE_C_FLAGS_RELEASE" FORCE)
SET(CMAKE_CXX_FLAGS_RELEASE "-O${OPTIM_LEVEL} ${COMPIL_FLAGS_LTO}"
					 CACHE STRING "CMAKE_CXX_FLAGS_RELEASE" FORCE)
SET(CMAKE_ASM_FLAGS_RELEASE ""
					 CACHE STRING "CMAKE_ASM_FLAGS_RELEASE" FORCE)

SET(CMAKE_CXX_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs ${LINK_FLAGS_LTO}"
					 CACHE STRING "CMAKE_CXX_LINK_FLAGS" FORCE)
SET(CMAKE_C_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs ${LINK_FLAGS_LTO}"
					 CACHE STRING "CMAKE_C_LINK_FLAGS" FORCE)


SET(CMAKE_CROSSCOMPILING TRUE
					 CACHE STRING "CMAKE_CROSSCOMPILING")
SET(CMAKE_SYSTEM_NAME Generic
					 CACHE STRING "CMAKE_SYSTEM_NAME")
ENABLE_LANGUAGE(ASM)




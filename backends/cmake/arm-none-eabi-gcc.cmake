INCLUDE(CMakeForceCompiler)

################################################################################
# cross compilation tools
find_program(CROSS_GCC_FULL_PATH "arm-none-eabi-gcc")
get_filename_component(CROSS_COMPIL_TOOLS ${CROSS_GCC_FULL_PATH} PATH)
if (NOT EXISTS ${CROSS_COMPIL_TOOLS})
	message (FATAL_ERROR "Can't find cross compilation tool chain")
endif()



SET(CPREF				${CROSS_COMPIL_TOOLS}/arm-none-eabi)
SET(CMAKE_C_COMPILER	${CPREF}-gcc CACHE STRING "arm-none-eabi-gcc" FORCE)
SET(CMAKE_CXX_COMPILER	${CPREF}-g++ CACHE STRING "arm-none-eabi-g++" FORCE)
SET(AS					"${CROSS_COMPIL_TOOLS}/arm-none-eabi-gcc -x -assembler-with-cpp"  CACHE STRING "arm-none-eabi-as")
SET(CMAKE_AR			${CPREF}-ar CACHE STRING "arm-none-eabi-ar" FORCE)
SET(CMAKE_LD			${CPREF}-ld CACHE STRING "arm-none-eabi-ld" FORCE)
SET(NM					${CPREF}-nm CACHE STRING "arm-none-eabi-nm" FORCE)
SET(OBJCOPY				${CPREF}-objcopy CACHE STRING "arm-none-eabi-objcopy" FORCE)
SET(OBJDUMP				${CPREF}-objdump CACHE STRING "arm-none-eabi-objdump" FORCE)
SET(READELF				${CPREF}-readelf CACHE STRING "arm-none-eabi-readelf" FORCE)
SET(CMAKE_RANLIB		${CPREF}-ranlib CACHE STRING "arm-none-eabi-ranlib" FORCE)

CMAKE_FORCE_C_COMPILER(${CPREF}-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(${CPREF}-g++ GNU)
################################################################################

#fix '-rdynamic' cmake 2.8.9 bug
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


# here is the target environment is located
SET(CMAKE_FIND_ROOT_PATH	${CROSS_COMPIL_TOOLS})
include_directories(${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/)
file(GLOB _CPP_INCLUDE_DIR_ ${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/c++/*)
include_directories(${_CPP_INCLUDE_DIR_})

if (NOT OPTIM_LEVEL)
	set (OPTIM_LEVEL "3")
endif()

if (NOT DO_NOT_USE_LTO)
	set (COMPIL_FLAGS_LTO "-flto")
	set (LINK_FLAGS_LTO "-O${OPTIM_LEVEL} -flto")
endif()

SET(CMAKE_CXX_FLAGS "-std=c++11 -fno-builtin -fno-rtti -fno-exceptions")

SET(CMAKE_C_FLAGS_DEBUG "-g"
					 CACHE STRING "CMAKE_C_FLAGS_DEBUG" FORCE)
SET(CMAKE_CXX_FLAGS_DEBUG "-g"
					 CACHE STRING "CMAKE_CXX_FLAGS_DEBUG" FORCE)
SET(CMAKE_ASM_FLAGS_DEBUG "-g"
					 CACHE STRING "CMAKE_ASM_FLAGS_DEBUG" FORCE)

ENABLE_LANGUAGE(ASM)




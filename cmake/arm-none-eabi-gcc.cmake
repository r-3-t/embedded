
################################################################################
# cross compilation tools
find_program(CROSS_GCC_FULL_PATH "arm-none-eabi-gcc")
get_filename_component(CROSS_COMPIL_TOOLS ${CROSS_GCC_FULL_PATH} PATH)
if (EXISTS ${CROSS_COMPIL_TOOLS})
	message ("Cross compilation tools found at : ${CROSS_COMPIL_TOOLS}")
else()
	message (FATAL_ERROR "Can't find cross compilation tool chain")
endif()

SET(CPREF				${CROSS_COMPIL_TOOLS}/arm-none-eabi)
SET(CMAKE_C_COMPILER	${CPREF}-gcc)
SET(CMAKE_CXX_COMPILER	${CPREF}-g++)
SET(AS					"${CROSS_COMPIL_TOOLS}/arm-none-eabi-gcc -x -assembler-with-cpp")
SET(AR					${CPREF}-ar)
SET(LD					${CPREF}-ld)
SET(NM					${CPREF}-nm)
SET(OBJCOPY				${CPREF}-objcopy)
SET(OBJDUMP				${CPREF}-objdump)
SET(READELF				${CPREF}-readelf)

CMAKE_FORCE_C_COMPILER(${CPREF}-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(${CPREF}-g++ GNU)
################################################################################



# here is the target environment is located
SET(CMAKE_FIND_ROOT_PATH	${CROSS_COMPIL_TOOLS})
include_directories(${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/)
include_directories(${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/c++/4.7.4)

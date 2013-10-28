

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
if (EXISTS ${CROSS_COMPIL_TOOLS})
	message ("Cross compilation tools found at : ${CROSS_COMPIL_TOOLS}")
else()
	message (FATAL_ERROR "Can't find cross compilation tool chain")
endif()

SET(CPREF				${CROSS_COMPIL_TOOLS}/arm-none-eabi)
SET(CMAKE_C_COMPILER	${CPREF}-gcc)
SET(CMAKE_CXX_COMPILER	${CPREF}-g++)
SET(AS					"${CROSS_COMPIL_TOOLS}/arm-none-eabi-gcc -x -assembler-with-cpp")
SET(CMAKE_AR			${CPREF}-ar)
SET(CMAKE_LD			${CPREF}-ld)
SET(NM					${CPREF}-nm)
SET(OBJCOPY				${CPREF}-objcopy)
SET(OBJDUMP				${CPREF}-objdump)
SET(READELF				${CPREF}-readelf)
SET(CMAKE_RANLIB		${CPREF}-ranlib)

CMAKE_FORCE_C_COMPILER(${CPREF}-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(${CPREF}-g++ GNU)
################################################################################

#fix '-rdynamic' cmake 2.8.9 bug
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# here is the target environment is located
SET(CMAKE_FIND_ROOT_PATH	${CROSS_COMPIL_TOOLS})
include_directories(${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/)
include_directories(${CROSS_COMPIL_TOOLS}/../arm-none-eabi/include/c++/4.7.4)

if (NOT OPTIM_LEVEL)
	set (OPTIM_LEVEL "3")
endif()

if (USE_LTO)
	set (COMPIL_FLAGS_LTO "-flto")
	set (LINK_FLAGS_LTO "-O${OPTIM_LEVEL} -flto")
endif()

SET(CMAKE_ASM_FLAGS "${MCFLAGS}")
SET(CMAKE_C_FLAGS "${MCFLAGS} -Wall -Wextra -Warray-bounds -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS "${MCFLAGS} -std=c++11 -Wall -Wextra -Warray-bounds -fno-builtin -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "-O1 -g")
SET(CMAKE_CXX_FLAGS_DEBUG "-O1 -g")
SET(CMAKE_ASM_FLAGS_DEBUG "-g")

SET(CMAKE_C_FLAGS_RELEASE "-O${OPTIM_LEVEL} ${COMPIL_FLAGS_LTO}")
SET(CMAKE_CXX_FLAGS_RELEASE "-O${OPTIM_LEVEL} ${COMPIL_FLAGS_LTO}")
SET(CMAKE_ASM_FLAGS_RELEASE "")

SET(CMAKE_CXX_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs ${LINK_FLAGS_LTO}")
SET(CMAKE_C_LINK_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,--gc-sections --specs=nano.specs ${LINK_FLAGS_LTO}")


SET(CMAKE_CROSSCOMPILING TRUE) 
SET(CMAKE_SYSTEM_NAME Generic)
ENABLE_LANGUAGE(ASM)


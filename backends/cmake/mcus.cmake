######################################################################
########################### STM32F051 ################################
######################################################################
#compile flags for targets
set(STM32F051_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m0")
set(STM32F051_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m0")

#linker script
set (STM32F051_FLASH_ORIGIN			0x08000000)
set (STM32F051_RAM_ORIGIN			0x20000000)
set (STM32F051_RAM_SIZE				8K)
set (STM32F051_FLASH_SIZE			64K)
set (STM32F051_MIN_STACK_SIZE			0x800)
set (STM32F051_MIN_HEAP_SIZE			0x800)

set (STM32F051_OPENOCDCFG_CONTENT
"
source [find board/stm32f0discovery.cfg]
")


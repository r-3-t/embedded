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

######################################################################
########################### STM32F103 ################################
######################################################################
#compile flags for targets
set(STM32F103_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m3")
set(STM32F103_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m3")

#linker script
set (STM32F103_FLASH_ORIGIN			0x08000000)
set (STM32F103_RAM_ORIGIN			0x20000000)
set (STM32F103_RAM_SIZE				20K)
set (STM32F103_FLASH_SIZE			64K)
set (STM32F103_MIN_STACK_SIZE			0x800)
set (STM32F103_MIN_HEAP_SIZE			0x800)

set (STM32F103_OPENOCDCFG_CONTENT
"
interface ft2232
ft2232_device_desc \"USB<=>JTAG&RS232\"
ft2232_layout jtagkey
ft2232_vid_pid 0x1457 0x5118

source [find target/stm32f1x.cfg]

#jtag_rclk 1500

gdb_breakpoint_override hard

#reset_config trst_and_srst srst_pulls_trst srst_gates_jtag
reset_config trst_and_srst separate

")

######################################################################
########################### STM32F100 ################################
######################################################################
#compile flags for targets
set(STM32F100_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m3")
set(STM32F100_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m3")

#linker script
set (STM32F100_FLASH_ORIGIN			0x08000000)
set (STM32F100_RAM_ORIGIN			0x20000000)
set (STM32F100_RAM_SIZE				8K)
set (STM32F100_FLASH_SIZE			128K)
set (STM32F100_MIN_STACK_SIZE			0x800)
set (STM32F100_MIN_HEAP_SIZE			0x800)

set (STM32F100_OPENOCDCFG_CONTENT
"
source [find board/stm32vldiscovery.cfg]
")

######################################################################
########################### LM4F120XL ################################
######################################################################
#compile flags for targets
set(LM4F120XL_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m4 -DPART_LM4F120H5QR")
set(LM4F120XL_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m4")

#linker script
set (LM4F120XL_FLASH_ORIGIN			0x00000000)
set (LM4F120XL_RAM_ORIGIN			0x20000000)
set (LM4F120XL_RAM_SIZE				32K)
set (LM4F120XL_FLASH_SIZE			256K)
set (LM4F120XL_MIN_STACK_SIZE			0x800)
set (LM4F120XL_MIN_HEAP_SIZE			0x800)

set (LM4F120XL_OPENOCDCFG_CONTENT
"
source [find board/ek-lm4f120xl.cfg]
")

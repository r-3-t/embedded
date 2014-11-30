######################################################################
########################### STM32F051 ################################
######################################################################
#compile flags for targets
set(STM32F051_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m0 -DSTM32F0XX")
set(STM32F051_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m0")

#linker script
set (STM32F051_FLASH_ORIGIN			0x08000000)
set (STM32F051_RAM_ORIGIN			0x20000000)
set (STM32F051_RAM_SIZE				8K)
set (STM32F051_FLASH_SIZE			64K)
set (STM32F051_MIN_STACK_SIZE			0x800)
set (STM32F051_MIN_HEAP_SIZE			0x800)

#template
set (STM32F051_NUM_LED				1)
set (STM32F051_LED0_PORT			3)
set (STM32F051_LED0_PIN				8)
set (STM32F051_BUTTON0_PORT			1)
set (STM32F051_BUTTON0_PIN			0)
set (STM32F051_DEFAULT_UART			1)
set (STM32F051_DEFAULT_TIMER			2)

set (STM32F051_OPENOCDCFG_CONTENT
"
source [find board/stm32f0discovery.cfg]
")

######################################################################
########################### STM32F103 ################################
######################################################################
#compile flags for targets
set(STM32F103_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m3 -DSTM32F1XX")
set(STM32F103_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m3")

#linker script
set (STM32F103_FLASH_ORIGIN			0x08000000)
set (STM32F103_RAM_ORIGIN			0x20000000)
set (STM32F103_RAM_SIZE				20K)
set (STM32F103_FLASH_SIZE			64K)
set (STM32F103_MIN_STACK_SIZE			0x800)
set (STM32F103_MIN_HEAP_SIZE			0x800)

#template
set (STM32F103_NUM_LED				1)
set (STM32F103_LED0_PORT			1)
set (STM32F103_LED0_PIN				0)
set (STM32F103_BUTTON0_PORT			2)
set (STM32F103_BUTTON0_PIN			0)
set (STM32F103_DEFAULT_UART			1)
set (STM32F103_DEFAULT_TIMER			2)

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
set(STM32F100_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m3 -DSTM32F1XX")
set(STM32F100_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m3")

#linker script
set (STM32F100_FLASH_ORIGIN			0x08000000)
set (STM32F100_RAM_ORIGIN			0x20000000)
set (STM32F100_RAM_SIZE				8K)
set (STM32F100_FLASH_SIZE			128K)
set (STM32F100_MIN_STACK_SIZE			0x800)
set (STM32F100_MIN_HEAP_SIZE			0x800)

#template
set (STM32F100_NUM_LED				1)
set (STM32F100_LED0_PORT			3)
set (STM32F100_LED0_PIN				8)
set (STM32F100_BUTTON0_PORT			1)
set (STM32F100_BUTTON0_PIN			0)
set (STM32F100_DEFAULT_UART			1)
set (STM32F100_DEFAULT_TIMER			2)

set (STM32F100_OPENOCDCFG_CONTENT
"
source [find board/stm32vldiscovery.cfg]
")

######################################################################
########################### STM32F407 ################################
######################################################################
#compile flags for targets
set(STM32F407_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -mthumb -mcpu=cortex-m4 -DSTM32F4XX -DHSE_VALUE=8000000")
set(STM32F407_LINK_FLAGS "${COMMON_LINK_FLAGS} -mthumb -mcpu=cortex-m4")

#linker script
set (STM32F407_FLASH_ORIGIN			0x08000000)
set (STM32F407_RAM_ORIGIN			0x20000000)
set (STM32F407_RAM_SIZE				128K)
set (STM32F407_FLASH_SIZE			1024K)
set (STM32F407_MIN_STACK_SIZE			0x800)
set (STM32F407_MIN_HEAP_SIZE			0x800)

#template
set (STM32F407_NUM_LED				4)
set (STM32F407_LED0_PORT			4)
set (STM32F407_LED0_PIN				15)
set (STM32F407_LED1_PORT			4)
set (STM32F407_LED1_PIN				14)
set (STM32F407_LED2_PORT			4)
set (STM32F407_LED2_PIN				13)
set (STM32F407_LED3_PORT			4)
set (STM32F407_LED3_PIN				12)
set (STM32F407_BUTTON0_PORT			1)
set (STM32F407_BUTTON0_PIN			0)
set (STM32F407_DEFAULT_UART			2)
set (STM32F407_DEFAULT_TIMER			2)

set (STM32F407_OPENOCDCFG_CONTENT
"
source [find board/stm32f4discovery.cfg]
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
set (LM4F120XL_DEFAULT_TIMER			1)

#template
set (LM4F120XL_NUM_LED				1)
set (LM4F120XL_LED0_PORT			6)
set (LM4F120XL_LED0_PIN				1)
set (LM4F120XL_BUTTON0_PORT			6)
set (LM4F120XL_BUTTON0_PIN			4)
set (LM4F120XL_DEFAULT_UART			1)
set (LM4F120XL_DEFAULT_TIMER			1)

set (LM4F120XL_OPENOCDCFG_CONTENT
"
source [find board/ek-lm4f120xl.cfg]
")

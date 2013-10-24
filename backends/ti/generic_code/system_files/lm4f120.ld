/* Entry Point */
ENTRY(Reset_Handler)

/* Check heap and stack allocated size during link */
_Heap_Size = 0x800;      /* required amount of heap  */
_Min_Stack_Size = 0x800; /* required amount of stack */

/* MEMORIES */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256k
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32k
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  /* Put interrupt vectors first in start of Flash */
  .isr_vector :
  {
  	_stext = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* Next, put code */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH


   .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
    .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
    } >FLASH

  .ARM.attributes 0 : { *(.ARM.attributes) }

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array*))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* And put data */
  /* start of initialized data */
  _sidata = .;

  /* Initialized data at copied from Flash (@ _sidata) to RAM (_sdata) */
  .data : AT ( _sidata )
  {
    . = ALIGN(4);
    _data = .; /* start of data is named _data or _sdata */
    _sdata = .;
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .;
  } >RAM

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    _bss = .;			/* start of bss is named _bss or _sbss */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap section, used to check that there is enough RAM left */
  .heap (NOLOAD):
   {
     _heap = . ;
     . = ALIGN(4);
     . = . + _Heap_Size;  /* define _Heap_Size at the start of the link file */
     . = ALIGN(4);
     _eheap = . ;
   } > RAM

  /*  stack section, used to check that there is enough RAM left */
  .chek_stack (NOLOAD):
  {
    . = ALIGN(4);
    . += _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }
}


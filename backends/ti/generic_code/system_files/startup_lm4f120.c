//*****************************************************************************
//
// startup_gcc.c - Startup code for use with GNU tools.
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************

#include "inc/hw_nvic.h"
#include "inc/hw_types.h"


//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void Reset_Handler(void);
static void NmiHandler(void);
static void HardFaultHandler(void);
static void DefaultHandler(void);

//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);


//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
extern int _estack;
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void*)&_estack,                               // The initial stack pointer
    Reset_Handler,                               // The reset handler
    NmiHandler,                                  // The NMI handler
    HardFaultHandler,                               // The hard fault handler
    DefaultHandler,                      // The MPU fault handler
    DefaultHandler,                      // The bus fault handler
    DefaultHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultHandler,                      // SVCall handler
    DefaultHandler,                      // Debug monitor handler
    0,                                      // Reserved
    DefaultHandler,                      // The PendSV handler
    DefaultHandler,                      // The SysTick handler
    DefaultHandler,                      // GPIO Port A
    DefaultHandler,                      // GPIO Port B
    DefaultHandler,                      // GPIO Port C
    DefaultHandler,                      // GPIO Port D
    DefaultHandler,                      // GPIO Port E
    DefaultHandler,                      // UART0 Rx and Tx
    DefaultHandler,                      // UART1 Rx and Tx
    DefaultHandler,                      // SSI0 Rx and Tx
    DefaultHandler,                      // I2C0 Master and Slave
    DefaultHandler,                      // PWM Fault
    DefaultHandler,                      // PWM Generator 0
    DefaultHandler,                      // PWM Generator 1
    DefaultHandler,                      // PWM Generator 2
    DefaultHandler,                      // Quadrature Encoder 0
    DefaultHandler,                      // ADC Sequence 0
    DefaultHandler,                      // ADC Sequence 1
    DefaultHandler,                      // ADC Sequence 2
    DefaultHandler,                      // ADC Sequence 3
    DefaultHandler,                      // Watchdog timer
    DefaultHandler,                      // Timer 0 subtimer A
    DefaultHandler,                      // Timer 0 subtimer B
    DefaultHandler,                      // Timer 1 subtimer A
    DefaultHandler,                      // Timer 1 subtimer B
    DefaultHandler,                      // Timer 2 subtimer A
    DefaultHandler,                      // Timer 2 subtimer B
    DefaultHandler,                      // Analog Comparator 0
    DefaultHandler,                      // Analog Comparator 1
    DefaultHandler,                      // Analog Comparator 2
    DefaultHandler,                      // System Control (PLL, OSC, BO)
    DefaultHandler,                      // FLASH Control
    DefaultHandler,                      // GPIO Port F
    DefaultHandler,                      // GPIO Port G
    DefaultHandler,                      // GPIO Port H
    DefaultHandler,                      // UART2 Rx and Tx
    DefaultHandler,                      // SSI1 Rx and Tx
    DefaultHandler,                      // Timer 3 subtimer A
    DefaultHandler,                      // Timer 3 subtimer B
    DefaultHandler,                      // I2C1 Master and Slave
    DefaultHandler,                      // Quadrature Encoder 1
    DefaultHandler,                      // CAN0
    DefaultHandler,                      // CAN1
    DefaultHandler,                      // CAN2
    DefaultHandler,                      // Ethernet
    DefaultHandler,                      // Hibernate
    DefaultHandler,                      // USB0
    DefaultHandler,                      // PWM Generator 3
    DefaultHandler,                      // uDMA Software Transfer
    DefaultHandler,                      // uDMA Error
    DefaultHandler,                      // ADC1 Sequence 0
    DefaultHandler,                      // ADC1 Sequence 1
    DefaultHandler,                      // ADC1 Sequence 2
    DefaultHandler,                      // ADC1 Sequence 3
    DefaultHandler,                      // I2S0
    DefaultHandler,                      // External Bus Interface 0
    DefaultHandler,                      // GPIO Port J
    DefaultHandler,                      // GPIO Port K
    DefaultHandler,                      // GPIO Port L
    DefaultHandler,                      // SSI2 Rx and Tx
    DefaultHandler,                      // SSI3 Rx and Tx
    DefaultHandler,                      // UART3 Rx and Tx
    DefaultHandler,                      // UART4 Rx and Tx
    DefaultHandler,                      // UART5 Rx and Tx
    DefaultHandler,                      // UART6 Rx and Tx
    DefaultHandler,                      // UART7 Rx and Tx
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultHandler,                      // I2C2 Master and Slave
    DefaultHandler,                      // I2C3 Master and Slave
    DefaultHandler,                      // Timer 4 subtimer A
    DefaultHandler,                      // Timer 4 subtimer B
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultHandler,                      // Timer 5 subtimer A
    DefaultHandler,                      // Timer 5 subtimer B
    DefaultHandler,                      // Wide Timer 0 subtimer A
    DefaultHandler,                      // Wide Timer 0 subtimer B
    DefaultHandler,                      // Wide Timer 1 subtimer A
    DefaultHandler,                      // Wide Timer 1 subtimer B
    DefaultHandler,                      // Wide Timer 2 subtimer A
    DefaultHandler,                      // Wide Timer 2 subtimer B
    DefaultHandler,                      // Wide Timer 3 subtimer A
    DefaultHandler,                      // Wide Timer 3 subtimer B
    DefaultHandler,                      // Wide Timer 4 subtimer A
    DefaultHandler,                      // Wide Timer 4 subtimer B
    DefaultHandler,                      // Wide Timer 5 subtimer A
    DefaultHandler,                      // Wide Timer 5 subtimer B
    DefaultHandler,                      // FPU
    DefaultHandler,                      // PECI 0
    DefaultHandler,                      // LPC 0
    DefaultHandler,                      // I2C4 Master and Slave
    DefaultHandler,                      // I2C5 Master and Slave
    DefaultHandler,                      // GPIO Port M
    DefaultHandler,                      // GPIO Port N
    DefaultHandler,                      // Quadrature Encoder 2
    DefaultHandler,                      // Fan 0
    0,                                      // Reserved
    DefaultHandler,                      // GPIO Port P (Summary or P0)
    DefaultHandler,                      // GPIO Port P1
    DefaultHandler,                      // GPIO Port P2
    DefaultHandler,                      // GPIO Port P3
    DefaultHandler,                      // GPIO Port P4
    DefaultHandler,                      // GPIO Port P5
    DefaultHandler,                      // GPIO Port P6
    DefaultHandler,                      // GPIO Port P7
    DefaultHandler,                      // GPIO Port Q (Summary or Q0)
    DefaultHandler,                      // GPIO Port Q1
    DefaultHandler,                      // GPIO Port Q2
    DefaultHandler,                      // GPIO Port Q3
    DefaultHandler,                      // GPIO Port Q4
    DefaultHandler,                      // GPIO Port Q5
    DefaultHandler,                      // GPIO Port Q6
    DefaultHandler,                      // GPIO Port Q7
    DefaultHandler,                      // GPIO Port R
    DefaultHandler,                      // GPIO Port S
    DefaultHandler,                      // PWM 1 Generator 0
    DefaultHandler,                      // PWM 1 Generator 1
    DefaultHandler,                      // PWM 1 Generator 2
    DefaultHandler,                      // PWM 1 Generator 3
    DefaultHandler                       // PWM 1 Fault
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

extern void __libc_init_array();

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
Reset_Handler(void)
{
    unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pulSrc = &_etext;
    for(pulDest = &_data; pulDest < &_edata; )
    {
        *pulDest++ = *pulSrc++;
    }

    //
    // Zero fill the bss segment.
    //
    __asm("    ldr     r0, =_bss\n"
          "    ldr     r1, =_ebss\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    //
    // Enable the floating-point unit.  This must be done here to handle the
    // case where main() uses floating-point and the function prologue saves
    // floating-point registers (which will fault if floating-point is not
    // enabled).  Any configuration of the floating-point unit using DriverLib
    // APIs must be done here prior to the floating-point unit being enabled.
    //
    // Note that this does not use DriverLib since it might not be included in
    // this project.
    //
    HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) &
                         ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) |
                        NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);


    // Call static constructors
    __libc_init_array();

    //
    // Call the application's entry point.
    //
    main();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiHandler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
HardFaultHandler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
DefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

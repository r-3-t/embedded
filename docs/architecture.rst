Architecture
============

This library provides an abstraction for several board (stm32f0, stm32f1, stm32f4, ti, ...).
This page explains the architecture of the project.

File and Folder structure
-------------------------

::

    |-- backends                            :   This is the main folder, It contains the abstraction
                                                layer for each mcu and the cmake scripts
    |   |-- CMakeLists.txt                  :   This script include cmake scripts of each supported architecture
    |   |-- cmake
    |   |   |-- arm-none-eabi-gcc.cmake     :   force cmake to use the arm-none-eabi-* binaries
    |   |   |-- mcus.cmake                  :   describe board characteristics and some common port DEFAULT_UART ...
    |   |   `-- project.cmake               :   contains the main function : build_project
    |   |-- common
    |   |   |-- CMakeLists.txt
    |   |   |-- error.c
    |   |   |-- include
    |   |   |   `-- error.h
    |   |   |-- linker_script.ld
    |   |   |-- pinout
    |   |   |   |-- CMakeLists.txt
    |   |   |   |-- Pinout.cpp
    |   |   |   |-- Pinout.hpp
    |   |   |   `-- PinoutInterface.hpp
    |   |   `-- syscall.c
    |   |-- stm32
    |   |   |-- CMakeLists.txt
    |   |   |-- hal
    |   |   |-- include
    |   |   |-- project_stm32f051.cmake
    |   |   |-- project_stm32f100.cmake
    |   |   |-- project_stm32f103.cmake
    |   |   |-- project_stm32f407.cmake
    |   |   |-- stm32f0
    |   |   |   |-- CMakeLists.txt
    |   |   |   `-- system_files
    |   |   |-- stm32f1
    |   |   |   |-- CMakeLists.txt
    |   |   |   `-- system_files
    |   |   `-- stm32f4
    |   |       |-- CMakeLists.txt
    |   |       |-- hal
    |   |       |   |-- hal_stm32f4_led.cpp
    |   |       |   |-- hal_stm32f4_led.hpp
    |   |       |   `-- hal_stm32f4_spi.hpp
    |   |       `-- system_files
    |   `-- ti
    |       |-- CMakeLists.txt
    |       |-- include
    |       |-- project_lm4f120xl.cmake
    |       `-- stellaris
    |           |-- cmake
    |           |   `-- tix.cmake
    |           |-- hal
    |           `-- system_files
    |               |-- startup_lm4f120.c
    |               |-- stellaris
    |               `-- syscall.c
    |-- board_examples
    |   |-- CMakeLists.txt
    |   |-- arduino_blink
    |   |-- arduino_mpu6050
    |   |-- arduino_serial
    |   |-- arduino_wire
    |   |-- cmake
    |   |-- extint
    |   |-- heap
    |   |-- i2c
    |   |-- leds
    |   |-- pinout
    |   |-- pwm
    |   |-- rf24
    |   |-- spi
    |   |-- timer
    |   |-- uart
    |   `-- zigbee
    |-- components-docs
    |   `-- xbee.pdf
    |-- docs
    |-- drivers
    |   |-- arduino
    |   `-- zigbee
    |-- frontends
    |   `-- arduino
    |-- hal
    |   |-- ClockInterface.hpp
    |   |-- ExtintInterface.hpp
    |   |-- GpioInterface.hpp
    |   |-- I2cInterface.hpp
    |   |-- LedInterface.hpp
    |   |-- PwmInterface.hpp
    |   |-- SpiInterface.hpp
    |   |-- TimerInterface.hpp
    |   |-- UartInterface.hpp
    |   |-- WirelessInterface.hpp
    |   `-- types.hpp
    `- tools
        |-- pinout
        `-- terminal

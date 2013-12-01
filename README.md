embedded
========

prerequisite
------------

* [cmake](http://cmake.org) must be installed on your system
* [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded) must be installed on your system

supported board and MCU
-----------------------

* STM32VLDISCOVERY
* STM32F4DISCOVERY
* STM32F103 
* LM4F120XL

examples
-------- 

* stm32f103
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/leds/ -DCMAKE_BUILD_TYPE=Debug -Darch=stm32f103
```
    
* stm32f100
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/leds/ -DCMAKE_BUILD_TYPE=Debug -Darch=stm32f1OO
```

* stm32f4
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/leds/ -DCMAKE_BUILD_TYPE=Debug -Darch=stm32f4
```

* lm4f120xl
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/gpio/ -DCMAKE_BUILD_TYPE=Debug -Darch=lm4f120xl
```

Options
-------- 

* OPTIM_SPEED

You can select the optimization level by adding "-DOPTIM_LEVEL=2" on your cmake command line. (default is 3).
This option only work in release mode.


* LTO

You can enable LTO (Link Time Optimization, see http://gcc.gnu.org/onlinedocs/gccint/LTO.html ) by adding "-DUSE_LTO=on" on your cmake command line.
Beware that this function is still highly experimental, and may not work with your code (or with the backend/frontend you selected)

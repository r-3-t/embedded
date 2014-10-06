How To Begin
============

prerequisite
------------

* [cmake](http://cmake.org) must be installed on your system
* [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded) must be installed on your system
*  git clone https://github.com/r-3-t/embedded.git/
*  git submodule init
*  git submodule update

supported board and MCU
-----------------------

* STM32F0DISCOVERY
* STM32VLDISCOVERY
* STM32F4DISCOVERY
* STM32F103
* LM4F120XL

examples
-------- 

* stm32f051
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/pinout/ -DCMAKE_BUILD_TYPE=Debug -Dmcu=stm32f051
```

* stm32f100
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/pinout/ -DCMAKE_BUILD_TYPE=Debug -Dmcu=stm32f1OO
```

* stm32f103
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/pinout/ -DCMAKE_BUILD_TYPE=Debug -Dmcu=stm32f103
```
    
* stm32f407
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/pinout/ -DCMAKE_BUILD_TYPE=Debug -Dmcu=stm32f407
```

* lm4f120xl
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/pinout/ -DCMAKE_BUILD_TYPE=Debug -Dmcu=lm4f120xl
```

Options
-------- 

* OPTIM_SPEED (TO REDO)

You can select the optimization level by adding "-DOPTIM_LEVEL=2" on your cmake command line. (default is 3).
This option only work in release mode.


* LTO (TO REDO)

You can enable LTO (Link Time Optimization, see http://gcc.gnu.org/onlinedocs/gccint/LTO.html ) by adding "-DUSE_LTO=on" on your cmake command line.
Beware that this function is still highly experimental, and may not work with your code (or with the backend/frontend you selected)

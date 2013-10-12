embedded
========

prerequisite
------------

* [cmake](http://cmake.org) must be installed on your system
* [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded) must be installed on your system

supported board
---------------


examples
-------- 

* stm32f103
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/leds/ -DCMAKE_BUILD_TYPE=Debug -Darch=stm32f1O3
```
    
* stm32f100
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/leds/ -DCMAKE_BUILD_TYPE=Debug -Darch=stm32f1OO
```

* stm32f4
```
r-3-t:build_dir$ rm -rf * && cmake  <path_to_dev>/board_examples/leds/ -DCMAKE_BUILD_TYPE=Debug -Darch=stm32f4
```


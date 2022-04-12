README
======


STM32 and LibOpenCM3 template project
---------------------------------

This repository provides a simple CMake project for easier reuse.
It can be used with every processor which is supported by LibOpenCM3. Therefore one needs to edit the CMakeLists.txt and the linker file. However, the files provided in this project are set up to work with the STM32F1 "Blue Pill" Board (with a STM32F103c8).
Moreover, there is a cmake file to support the STM32F4 Discovery board.


New to embedded projects?
-------------------------

The series of articles from Chris Lalancette might be useful for you:
  - [Developing STM32 microcontroller code on Linux (Part 1 of 8, introduction)](https://clalance.blogspot.de/2014/01/developing-stm32-microcontroller-code.html)
  - [Developing STM32 microcontroller code on Linux (Part 2 of 8, building the cross-compiler)](https://clalance.blogspot.de/2014/01/developing-stm32-microcontroller-code_6.html)
  - [Developing STM32 microcontroller code on Linux (Part 3 of 8, building gdb)](https://clalance.blogspot.de/2014/01/developing-stm32-microcontroller-code_8.html)
  - [Developing STM32 microcontroller code on Linux (Part 4 of 8, building openocd)](https://clalance.blogspot.de/2014/01/developing-stm32-microcontroller-code_9.html)
  - [Developing STM32 microcontroller code on Linux (Part 5 of 8, building libopencm3)](https://clalance.blogspot.de/2014/01/developing-stm32-microcontroller-code_10.html)
  - [Developing STM32 microcontroller code on Linux (Part 6 of 8, building and linking STM32 programs)](https://clalance.blogspot.de/2014/01/developing-stm32-microcontroller-code_13.html)
  - [Developing STM32 microcontroller code on Linux (Part 7 of 8, building and running a simple STM32 program)](https://clalance.blogspot.de/2014/01/developing-stm32-microcontroller-code_15.html)

For C++ on embedded projects see [Practical Guide to Bare Metal C++](https://arobenko.gitbooks.io/bare_metal_cpp/content/) or the [PDF - Practical Guide to Bare Metal C++](other/bare_metal_cpp.pdf).
Also [Modern C++ in embedded systems](https://www.embedded.com/design/programming-languages-and-tools/4438660/Modern-C--in-embedded-systems---Part-1--Myth-and-Reality#).
And [C++ in Embedded Systemen: Lessons Learned! (german)](https://www.embedded-software-engineering.de/c-in-embedded-systemen-lessons-learned-a-653915/).

External libraries
----------------

External libraries used in this project
  - [LibOpenCM3](http://libopencm3.org/) ([github](https://github.com/libopencm3/libopencm3))
  - [FreeRTOS](https://www.freertos.org/)


Prerequisites
-------------
Same prerequisites as for [LibOpenCM3](https://libopencm3.org/).

Building requires Python (Some code is generated) and [pcpp](https://pypi.org/project/pcpp/).

**For Ubuntu/Fedora:**

 - An arm-none-eabi/arm-elf toolchain.

**For Windows:**

 Download and install:

 - msys - http://sourceforge.net/projects/mingw/files/MSYS/Base/msys-core/msys-1.0.11/MSYS-1.0.11.exe
 - Python - http://www.python.org/ftp/python/2.7/python-2.7.msi (any 2.7 release)
 - arm-none-eabi/arm-elf toolchain (for example this one https://launchpad.net/gcc-arm-embedded)

Run msys shell and set the path without standard Windows paths, so Windows programs such as 'find' won't interfere:

    export PATH="/c//Python27:/c/ARMToolchain/bin:/usr/local/bin:/usr/bin:/bin"


Building
--------
From root directory:

    $ git submodule update --init
    $ mkdir debug
    $ cd debug
    $ cmake -DCMAKE_BUILD_TYPE=Debug ../ #(only needs to be run once, if one wants to use debug build. otherwise use "Release")
    $ make

Make targets:
  - libopencm3 (builds LibOpenCM3)
  - openocd (runs openocd - may need some tuning if you don't use a stm32f4)
  - flash (flashes elf to controller - may need some tuning if you don't use a stm32f4)

Flashing
--------

There is no flashing target at the moment. You want to use openocd to do that.

Structure
---------

There are 4 different folders:
  - include
  - libs
  - other
  - src

The include folder holds all of your include files.  
The src folder holds all of your sources.  
The libs folder holds all the external libraries.  
The other folder holds some scripts or binaries to make your life easier.

Defines
------

CMakefile defines some preprocessor defines depending on the settings.
The defines are:
  - DEBUG (compiled as debug build)
  - NDEBUG (compiled in release build)

Fine-tuning the build
---------------------

To fine tune the build one needs to edit the cmake files.
See the cmake files for comments on how to tweak your build.


Start own project with this one as base
---------------------------------------

Using a STM32F4 Discovery or the STM32F407VGT6: you just need to edit CMakeLists.txt to use the stm32f407vg.cmake, the stm32f407 library and add your custom sources and includes.
The .cmake files create link libraries with the name of the processor by default. For a "stm32f407vg" this would be: "stm32f407vg", "stm32f407vg_freertos" and "stm32f407vg_freertoslts".
Using a Bluepill Board: just add your sources and includes.

Other Platform/CPU:
You need to edit the following cmake files:
  - add a processor.cmake in cmakes folder
  - CmakeLists.txt
  - maybe create a toolchain file



License
-------

All libraries are licensed under their own License. Visit their projects to see the licenses.

If not stated otherwise in the file, the  code is released under the terms of the GNU General
Public License (GPL), version 3 or later.

See COPYING.GPL3 and COPYING.LGPL3 for details.

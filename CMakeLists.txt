cmake_minimum_required(VERSION 3.9)

#name project. binary is called like the project name
project(stm32f4-discovery-sample VERSION 1.0.0 DESCRIPTION "description")

#check if we cross compile
IF(NOT CMAKE_CROSSCOMPILING)
  message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=/PATH/TO/TOOLCHAIN_FILE .")
ENDIF(NOT CMAKE_CROSSCOMPILING)

#set suffix to elf
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

#add custom targets for openocd. first one runs openocd and second one flashes to controller
add_custom_target(openocd openocd -f ${CMAKE_SOURCE_DIR}/other/utils/openocd/jlink.cfg -s ${CMAKE_SOURCE_DIR}/other/utils/openocd)
add_custom_target(flash openocd -f ${CMAKE_SOURCE_DIR}/other/utils/openocd/jlink.cfg -s ${CMAKE_SOURCE_DIR}/other/utils/openocd -c "flash_stm32f4 $<TARGET_FILE:${PROJECT_NAME}>")

#add LibOpenCM3
set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/lib/libopencm3)
add_custom_target(libopencm3 CFLAGS="-flto" make WORKING_DIRECTORY ${LIBOPENCM3_DIR})
include_directories(${LIBOPENCM3_DIR}/include)
link_directories(${LIBOPENCM3_DIR}/lib)
#set the preprocessor definition for LibOpenCM3
add_definitions(-DSTM32F4)
#set the library of LibOpenCM3 to use
set(LIBOPENCM3_LIB opencm3_stm32f4)

#setup the gcc flags
set(MCU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -mcpu=cortex-m4")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS} -std=c11 -Wall -Wextra -fdata-sections -ffunction-sections -flto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU_FLAGS} -std=c++17 -Wall -Wextra -fdata-sections -ffunction-sections -flto -fno-rtti -fno-exceptions")
#setup
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32f4-discovery.ld)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT} -Wl,--gc-sections -flto -nostartfiles")

#if we run in debug, define the DEBUG preprocessor define and debug optimization
# !!! sysview does not run without optimization !!!!
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g3 -ggdb3 -Os")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -g3 -ggdb3 -Os")

#if we run in release set following flags:
# !!! sysview does not run without optimization !!!!
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")

#adds executable
add_executable(${PROJECT_NAME} "")
#define source files
target_sources(${PROJECT_NAME} PRIVATE
  "src/main.cpp"
  "src/config/clock.cpp"
  "src/config/gpio.cpp"
  "src/tasks/mytasks.cpp"
  "src/tasks/init.cpp"
  "src/tasks/ledblink.cpp"
)
#define the include directories
target_include_directories(${PROJECT_NAME} PUBLIC "inc")
#define the linked libraries
target_link_libraries(${PROJECT_NAME} ${LIBOPENCM3_LIB} c m nosys)

#include freertos
#dont forget to check freertos.cmake if you change the microcontroller
include(freertos.cmake)
target_link_libraries(${PROJECT_NAME} freertos)

#include Segger Sysview
#must be included after freertos due to dependency to freertos lib
include(sysview.cmake)
target_link_libraries(${PROJECT_NAME} sysview)

#inlcude utils, view binary size and export to hex file
include(utils.cmake)
firmware_size(${PROJECT_NAME})
generate_object(${PROJECT_NAME} .hex ihex)

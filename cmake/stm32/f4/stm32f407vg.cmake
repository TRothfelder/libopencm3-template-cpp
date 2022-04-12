set(libopencm3_TARGET stm32/f4) #only compile libopencm3 library for target
set(libopencm3_LIB libopencm3_stm32f4.a) #set linked libopencm3 library
set(libopencm3_MCU stm32f407vg) #set mcu 
set(MCU_FLAGS -static -nostartfiles -fno-common -mcpu=cortex-m3 -mtune=cortex-m3 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16)

set(libopencm3_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/libopencm3)
set(libopencm3_LDSCRIPT ${libopencm3_SOURCE_DIR}/ld/linker.ld.S)

# create a target to build libopencm3 -- only for the target we need
add_custom_target(libopencm3 make CFLAGS="-flto" TARGETS=${libopencm3_TARGET} WORKING_DIRECTORY ${libopencm3_SOURCE_DIR})

execute_process(
  COMMAND ${libopencm3_SOURCE_DIR}/scripts/genlink.py ${libopencm3_SOURCE_DIR}/ld/devices.data ${libopencm3_MCU} DEFS
  OUTPUT_VARIABLE LIBOPENCM3_DEFINES
)
separate_arguments(LIBOPENCM3_DEFINES UNIX_COMMAND ${LIBOPENCM3_DEFINES}) 

execute_process(
  COMMAND pcpp -o ${CMAKE_BINARY_DIR}/${libopencm3_MCU}.ld ${LIBOPENCM3_DEFINES} --line-directive --compress ${libopencm3_LDSCRIPT}
)



add_library(${libopencm3_MCU} STATIC IMPORTED)
set_property(TARGET ${libopencm3_MCU} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${libopencm3_SOURCE_DIR}/include)
set_property(TARGET ${libopencm3_MCU} PROPERTY IMPORTED_LOCATION ${libopencm3_SOURCE_DIR}/lib/${libopencm3_LIB})
add_dependencies(${libopencm3_MCU} libopencm3)
target_link_directories(${libopencm3_MCU} INTERFACE ${libopencm3_SOURCE_DIR}/lib)

#setup the gcc flags
target_compile_definitions(${libopencm3_MCU} INTERFACE ${LIBOPENCM3_DEFINES})
target_compile_options(${libopencm3_MCU} INTERFACE ${MCU_FLAGS})
target_link_options(${libopencm3_MCU} INTERFACE ${MCU_FLAGS} -T ${CMAKE_BINARY_DIR}/${libopencm3_MCU}.ld)



add_library(${libopencm3_MCU}_freertos STATIC "")
set(FREERTOS_DIR ${CMAKE_SOURCE_DIR}/libs/FreeRTOSv202112.00/FreeRTOS/Source)
set(FREERTOS_PORT ARM_CM4F)
set(FREERTOS_COMPILER GCC)
set(FREERTOS_HEAPMANAGER heap_4)
file(GLOB FREERTOS_SRC
    ${FREERTOS_DIR}/*.c
    ${FREERTOS_DIR}/portable/${FREERTOS_COMPILER}/${FREERTOS_PORT}/*.c
    ${FREERTOS_DIR}/portable/${FREERTOS_COMPILER}/${FREERTOS_PORT}/*.S
    ${FREERTOS_DIR}/portable/MemMang/${FREERTOS_HEAPMANAGER}.c
)
target_sources(${libopencm3_MCU}_freertos
    PRIVATE
        ${FREERTOS_SRC}
        src/freertos/freertosHooks.c
)
target_include_directories(${libopencm3_MCU}_freertos PUBLIC include/freertos)
target_include_directories(${libopencm3_MCU}_freertos PUBLIC ${FREERTOS_DIR}/include)
target_include_directories(${libopencm3_MCU}_freertos PUBLIC ${FREERTOS_DIR}/portable/${FREERTOS_COMPILER}/${FREERTOS_PORT})
target_compile_options(${libopencm3_MCU}_freertos PUBLIC ${MCU_FLAGS})
target_link_libraries(${libopencm3_MCU}_freertos ${libopencm3_MCU})



add_library(${libopencm3_MCU}_freertoslts STATIC "")
set(FREERTOSLTS_DIR ${CMAKE_SOURCE_DIR}/libs/FreeRTOSv202012.04-LTS/FreeRTOS/FreeRTOS-Kernel)
set(FREERTOSLTS_PORT ARM_CM4F)
set(FREERTOSLTS_COMPILER GCC)
set(FREERTOSLTS_HEAPMANAGER heap_4)
file(GLOB FREERTOSLTS_SRC
    ${FREERTOSLTS_DIR}/*.c
    ${FREERTOSLTS_DIR}/portable/${FREERTOSLTS_COMPILER}/${FREERTOSLTS_PORT}/*.c
    ${FREERTOSLTS_DIR}/portable/${FREERTOSLTS_COMPILER}/${FREERTOSLTS_PORT}/*.S
    ${FREERTOSLTS_DIR}/portable/MemMang/${FREERTOSLTS_HEAPMANAGER}.c
)
target_sources(${libopencm3_MCU}_freertoslts
    PRIVATE
        ${FREERTOSLTS_SRC}
        src/freertos/freertosHooks.c
)
target_include_directories(${libopencm3_MCU}_freertoslts PUBLIC include/freertos)
target_include_directories(${libopencm3_MCU}_freertoslts PUBLIC ${FREERTOSLTS_DIR}/include)
target_include_directories(${libopencm3_MCU}_freertoslts PUBLIC ${FREERTOSLTS_DIR}/portable/${FREERTOSLTS_COMPILER}/${FREERTOSLTS_PORT})
target_compile_options(${libopencm3_MCU}_freertoslts PUBLIC ${MCU_FLAGS})
target_link_libraries(${libopencm3_MCU}_freertoslts ${libopencm3_MCU})

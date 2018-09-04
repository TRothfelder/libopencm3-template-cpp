#uncomment the version you want to compile in
#set(FREERTOS_DIR lib/FreeRTOSv9)
#set(FREERTOS_DIR lib/FreeRTOSv9_patched)
#set(FREERTOS_DIR lib/FreeRTOSv10.0.1)
set(FREERTOS_DIR lib/FreeRTOSv10.0.1_patched)

#setup FreeRTOS port, compiler and heapmanager
set(FREERTOS_PORT ARM_CM4F)
set(FREERTOS_COMPILER GCC)
set(FREERTOS_HEAPMANAGER heap_4)


add_library(freertos STATIC "")

#if you dont need the heapmanager you propably can remove it here
file(GLOB FREERTOS_SRC
    "${FREERTOS_DIR}/Source/*.c"
    "${FREERTOS_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_PORT}/*.c"
    "${FREERTOS_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_PORT}/*.S"
    "${FREERTOS_DIR}/Source/portable/MemMang/${FREERTOS_HEAPMANAGER}.c"
)

target_sources(freertos
    PRIVATE
        ${FREERTOS_SRC}
        "src/freertos/freertosHooks.c"
)

target_include_directories(freertos PUBLIC "${FREERTOS_DIR}/Source/include")
target_include_directories(freertos PUBLIC "inc/freertos")
target_include_directories(freertos PUBLIC "${FREERTOS_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_PORT}")

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_TOOLCHAIN_FILE cmake/toolchain-arm-none-eabi-gcc.cmake)

project(cmake_cpp_template VERSION 0.1.0 LANGUAGES CXX C ASM)

include(cmake/stm32/f1/stm32f103c8.cmake)
set(FIRMWARE_FILE_NAME firmware)
file(GLOB_RECURSE FIRMWARE_SRC
    src/*.c
    src/*.cpp
)
add_executable(${FIRMWARE_FILE_NAME} ${FIRMWARE_SRC})
target_link_libraries(${FIRMWARE_FILE_NAME} stm32f103c8_freertos)
target_include_directories(${FIRMWARE_FILE_NAME} PRIVATE include)
target_link_options(${FIRMWARE_FILE_NAME} PRIVATE
  -flto
  -Wl,--gc-sections
  -Wl,-Map=${FIRMWARE_FILE_NAME}.map
  -Wl,--print-memory-usage
)
target_compile_options(${FIRMWARE_FILE_NAME} PRIVATE
  --specs=nosys.specs 
  -flto
  -Wall 
  -Wextra 
  -fdata-sections 
  -ffunction-sections 
  $<$<COMPILE_LANGUAGE:CXX>:
    -fno-rtti
    -fno-exceptions
  >
  $<$<CONFIG:Debug>:
    -O0
    -g3 
    -ggdb
  >
  $<$<CONFIG:Release>:
    -Os
    -g0
  >
)
target_compile_definitions(${FIRMWARE_FILE_NAME} PRIVATE
  $<$<CONFIG:Debug>:
    DEBUG
  >
  $<$<CONFIG:Release>:
    NDEBUG
  >
)
#--specs=nano.specs --Wno-psabi
#--Wnp-psabi better as pragma


#stm32_add_flash_targets(phase_remote)

add_custom_command(TARGET ${FIRMWARE_FILE_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${FIRMWARE_FILE_NAME}>)

add_custom_command(TARGET ${FIRMWARE_FILE_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${FIRMWARE_FILE_NAME}>
    ${FIRMWARE_FILE_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${FIRMWARE_FILE_NAME}>
    ${FIRMWARE_FILE_NAME}.bin)

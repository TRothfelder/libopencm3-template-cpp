set(SYSVIEW_DIR lib/SEGGER)

add_library(sysview STATIC "")


file(GLOB SYSVIEW_SRC
    ${SYSVIEW_DIR}/*.c
    src/segger/*.c
)

target_sources(sysview
    PRIVATE
        ${SYSVIEW_SRC}
)

target_include_directories(sysview PUBLIC ${SYSVIEW_DIR})
target_include_directories(sysview PUBLIC inc/segger)
add_definitions(-DSEGGER_SYSVIEW_USE)
if(TARGET freertos)
  target_link_libraries(sysview freertos)
  target_link_libraries(freertos sysview)
endif(TARGET freertos)

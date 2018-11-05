#file ( WRITE  "${CMAKE_BINARY_DIR}/gdbinit" "mon reset halt\n")
#file ( APPEND "${CMAKE_BINARY_DIR}/gdbinit" "mon wait_halt\n")
#file ( APPEND "${CMAKE_BINARY_DIR}/gdbinit" "mon flash protect 0 0 11 off\n")
#file ( APPEND "${CMAKE_BINARY_DIR}/gdbinit" "mon flash write_image ")
#file ( APPEND "${CMAKE_BINARY_DIR}/gdbinit" $<TARGET_FILE:${PROJECT_NAME}>)

set(GDBINITFILE ${CMAKE_SOURCE_DIR}/gdbinit_generated)
add_custom_command(
        #TARGET ${PROJECT_NAME} POST_BUILD
        OUTPUT ${GDBINITFILE}
		COMMAND echo set verbose on > ${GDBINITFILE}
        COMMAND echo define target hookpost-remote >> ${GDBINITFILE}
		COMMAND echo mon init >> ${GDBINITFILE}
		COMMAND echo mon sleep 200 >> ${GDBINITFILE}
		COMMAND echo mon reset halt >> ${GDBINITFILE}
        COMMAND echo mon wait_halt >> ${GDBINITFILE}
		#COMMAND echo mon stm32f2x unlock 0 >> ${GDBINITFILE}
		#COMMAND echo mon mww 0x40023C08 0x08192A3B >> ${GDBINITFILE}
		#COMMAND echo mon mww 0x40023C08 0x4C5D6E7F >> ${GDBINITFILE}
		#COMMAND echo mon mww 0x40023C14 0x0fffaaed >> ${GDBINITFILE}
		COMMAND echo mon flash protect 0 0 11 off >> ${GDBINITFILE}
        COMMAND echo mon flash write_image erase $<TARGET_FILE:${PROJECT_NAME}> >> ${GDBINITFILE}
		COMMAND echo end >> ${GDBINITFILE}
        VERBATIM
        )

add_custom_target(create-gdbinit ALL DEPENDS ${GDBINITFILE})

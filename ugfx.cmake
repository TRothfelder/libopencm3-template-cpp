set(UGFX_DIR lib/ugfx)

#set specific driver files, copy the srcs and includes from the driver makefile
set(UGFX_SRC_DRIVERS ${UGFX_DIR}/drivers/gdisp/ILI9341/gdisp_lld_ILI9341.c)
set(UGFX_INC_DRIVERS ${UGFX_DIR}/drivers/gdisp/ILI9341)

add_library(ugfx STATIC "")

SET(UGFX_SRC_GFX ${UGFX_DIR}/src/gfx.c)

SET(UGFX_SRC_GOS ${UGFX_DIR}/src/gos/gos_chibios.c
          ${UGFX_DIR}/src/gos/gos_freertos.c
          ${UGFX_DIR}/src/gos/gos_win32.c
          ${UGFX_DIR}/src/gos/gos_linux.c
          ${UGFX_DIR}/src/gos/gos_osx.c
          ${UGFX_DIR}/src/gos/gos_raw32.c
          ${UGFX_DIR}/src/gos/gos_ecos.c
          ${UGFX_DIR}/src/gos/gos_rawrtos.c
          ${UGFX_DIR}/src/gos/gos_arduino.c
          ${UGFX_DIR}/src/gos/gos_cmsis.c
          ${UGFX_DIR}/src/gos/gos_nios.c
          ${UGFX_DIR}/src/gos/gos_zephyr.c
          ${UGFX_DIR}/src/gos/gos_x_threads.c
          ${UGFX_DIR}/src/gos/gos_x_heap.c)

SET(UGFX_SRC_GDRIVER ${UGFX_DIR}/src/gdriver/gdriver.c)

SET(UGFX_SRC_GQUEUE ${UGFX_DIR}/src/gqueue/gqueue.c)

SET(UGFX_SRC_GDISP ${UGFX_DIR}/src/gdisp/gdisp.c
    			${UGFX_DIR}/src/gdisp/gdisp_fonts.c
    			${UGFX_DIR}/src/gdisp/gdisp_pixmap.c
    			${UGFX_DIR}/src/gdisp/gdisp_image.c
    			${UGFX_DIR}/src/gdisp/gdisp_image_native.c
    			${UGFX_DIR}/src/gdisp/gdisp_image_gif.c
    			${UGFX_DIR}/src/gdisp/gdisp_image_bmp.c
    			${UGFX_DIR}/src/gdisp/gdisp_image_jpg.c
    			${UGFX_DIR}/src/gdisp/gdisp_image_png.c)

SET(UGFX_SRC_MCUFONT ${UGFX_DIR}/src/gdisp/mcufont/mf_encoding.c
          ${UGFX_DIR}/src/gdisp/mcufont/mf_font.c
          ${UGFX_DIR}/src/gdisp/mcufont/mf_justify.c
          ${UGFX_DIR}/src/gdisp/mcufont/mf_kerning.c
          ${UGFX_DIR}/src/gdisp/mcufont/mf_rlefont.c
          ${UGFX_DIR}/src/gdisp/mcufont/mf_bwfont.c
          ${UGFX_DIR}/src/gdisp/mcufont/mf_scaledfont.c
          ${UGFX_DIR}/src/gdisp/mcufont/mf_wordwrap.c)

SET(UGFX_SRC_GEVENT ${UGFX_DIR}/src/gevent/gevent.c)

SET(UGFX_SRC_GTIMER ${UGFX_DIR}/src/gtimer/gtimer.c)

SET(UGFX_SRC_GWIN ${UGFX_DIR}/src/gwin/gwin.c
    			${UGFX_DIR}/src/gwin/gwin_widget.c
    			${UGFX_DIR}/src/gwin/gwin_wm.c
    			${UGFX_DIR}/src/gwin/gwin_console.c
    			${UGFX_DIR}/src/gwin/gwin_graph.c
    			${UGFX_DIR}/src/gwin/gwin_button.c
    			${UGFX_DIR}/src/gwin/gwin_slider.c
    			${UGFX_DIR}/src/gwin/gwin_checkbox.c
    			${UGFX_DIR}/src/gwin/gwin_image.c
    			${UGFX_DIR}/src/gwin/gwin_label.c
    			${UGFX_DIR}/src/gwin/gwin_radio.c
    			${UGFX_DIR}/src/gwin/gwin_list.c
    			${UGFX_DIR}/src/gwin/gwin_progressbar.c
    			${UGFX_DIR}/src/gwin/gwin_container.c
    			${UGFX_DIR}/src/gwin/gwin_frame.c
    			${UGFX_DIR}/src/gwin/gwin_tabset.c
    			${UGFX_DIR}/src/gwin/gwin_gl3d.c
    			${UGFX_DIR}/src/gwin/gwin_keyboard.c
    			${UGFX_DIR}/src/gwin/gwin_keyboard_layout.c
    			${UGFX_DIR}/src/gwin/gwin_textedit.c)

SET(UGFX_SRC_GINPUT ${UGFX_DIR}/src/ginput/ginput.c
    			${UGFX_DIR}/src/ginput/ginput_mouse.c
    			${UGFX_DIR}/src/ginput/ginput_keyboard.c
    			${UGFX_DIR}/src/ginput/ginput_keyboard_microcode.c
    			${UGFX_DIR}/src/ginput/ginput_toggle.c
    			${UGFX_DIR}/src/ginput/ginput_dial.c)

SET(UGFX_SRC_GADC ${UGFX_DIR}/src/gadc/gadc.c)

SET(UGFX_SRC_GAUDIO ${UGFX_DIR}/src/gaudio/gaudio.c)

SET(UGFX_SRC_GMISC ${UGFX_DIR}/src/gmisc/gmisc.c
    			${UGFX_DIR}/src/gmisc/gmisc_arrayops.c
    			${UGFX_DIR}/src/gmisc/gmisc_matrix2d.c
    			${UGFX_DIR}/src/gmisc/gmisc_trig.c
    			${UGFX_DIR}/src/gmisc/gmisc_hittest.c)

SET(UGFX_SRC_GFILE ${UGFX_DIR}/src/gfile/gfile.c
            ${UGFX_DIR}/src/gfile/gfile_fs_native.c
            ${UGFX_DIR}/src/gfile/gfile_fs_ram.c
            ${UGFX_DIR}/src/gfile/gfile_fs_rom.c
            ${UGFX_DIR}/src/gfile/gfile_fs_fatfs.c
            ${UGFX_DIR}/src/gfile/gfile_fs_petitfs.c
            ${UGFX_DIR}/src/gfile/gfile_fs_mem.c
            ${UGFX_DIR}/src/gfile/gfile_fs_chibios.c
            ${UGFX_DIR}/src/gfile/gfile_fs_strings.c
            ${UGFX_DIR}/src/gfile/gfile_printg.c
            ${UGFX_DIR}/src/gfile/gfile_scang.c
            ${UGFX_DIR}/src/gfile/gfile_stdio.c
            ${UGFX_DIR}/src/gfile/gfile_fatfs_wrapper.c
            ${UGFX_DIR}/src/gfile/gfile_fatfs_diskio_chibios.c
            ${UGFX_DIR}/src/gfile/gfile_petitfs_wrapper.c
            ${UGFX_DIR}/src/gfile/gfile_petitfs_diskio_chibios.c)

SET(UGFX_SRC_GTRANS ${UGFX_DIR}/src/gtrans/gtrans.c)

target_sources(ugfx
    PRIVATE
      ${UGFX_SRC_GFX}
      ${UGFX_SRC_GOS}
      ${UGFX_SRC_GDRIVER}
      ${UGFX_SRC_GQUEUE}
      ${UGFX_SRC_GDISP}
      ${UGFX_SRC_MCUFONT}
      ${UGFX_SRC_GEVENT}
      ${UGFX_SRC_GTIMER}
      ${UGFX_SRC_GWIN}
      ${UGFX_SRC_GINPUT}
      ${UGFX_SRC_GADC}
      ${UGFX_SRC_GAUDIO}
      ${UGFX_SRC_GMISC}
      ${UGFX_SRC_GFILE}
      ${UGFX_SRC_GTRANS}
      ${UGFX_SRC_DRIVERS}
)

target_include_directories(ugfx PUBLIC "inc/ugfx")
target_include_directories(ugfx PUBLIC "${UGFX_DIR}")
target_include_directories(ugfx PUBLIC "${UGFX_DIR}/3rdparty/tinygl-0.4-ugfx/include")
target_include_directories(ugfx PUBLIC "${UGFX_INC_DRIVERS}")

if(TARGET freertos)
  target_link_libraries(ugfx freertos)
endif(TARGET freertos)

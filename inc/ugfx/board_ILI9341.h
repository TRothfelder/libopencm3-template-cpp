/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

#define LED_PORT	GPIOB
#define CS_PORT     GPIOD
#define RESET_PORT  GPIOD
#define DNC_PORT    GPIOD
#define LED_PAD		GPIO10
#define CS_PAD      GPIO6
#define RESET_PAD   GPIO5
#define DNC_PAD 	GPIO4

static GFXINLINE void init_board(GDisplay *g) {
	(void) g;
	//Set pins.
	gpio_set(CS_PORT, CS_PAD);
	gpio_set(RESET_PORT, RESET_PAD);
	gpio_set(DNC_PORT, DNC_PAD);
	gpio_set(LED_PORT, LED_PAD);
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	(void) state;
	state ? gpio_clear(RESET_PORT, RESET_PAD) : gpio_set(RESET_PORT, RESET_PAD);
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	(void) percent;
	// TODO: can probably pwm this
	if(percent) {
		// turn back light on
		gpio_set(LED_PORT, LED_PAD);
	} else {
		// turn off
		gpio_clear(LED_PORT, LED_PAD);
	}
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
	gpio_clear(CS_PORT, CS_PAD);
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
	gpio_set(CS_PORT, CS_PAD);
}

static GFXINLINE void write_index(GDisplay *g, uint16_t index) {
	(void) g;
	(void) index;
	gpio_clear(DNC_PORT, DNC_PAD);
	spi_xfer(SPI1, index);
	gpio_set(DNC_PORT, DNC_PAD);
}

static GFXINLINE void write_data(GDisplay *g, uint16_t data) {
	(void) g;
	(void) data;
	spi_xfer(SPI1, data);
}

static GFXINLINE void setreadmode(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay *g) {
	(void) g;
}

static GFXINLINE uint16_t read_data(GDisplay *g) {
	(void) g;
	return spi_read(SPI1);
}

#endif /* _GDISP_LLD_BOARD_H */

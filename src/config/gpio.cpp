/*
 * gpio.c
 *
 *  Created on: 27.05.2018
 *      Author: kt
 */
extern "C" {
	#include <libopencm3/stm32/rcc.h>
	#include <libopencm3/stm32/gpio.h>
}

#include "config/gpio.hpp"

void Gpio::setup( void ) {
	// For LED on D12
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);

	/* Set GPIO12-15 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

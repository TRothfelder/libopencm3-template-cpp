/*
 * clock.c
 *
 *  Created on: 27.05.2018
 *      Author: kt
 */
extern "C" {
	#include <libopencm3/stm32/rcc.h>
	#include <libopencm3/cm3/systick.h>
}

#include "config/clock.hpp"

void setupClock(void) {
	//setup clock
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
	/* 168MHz / 8 => 21000000 counts per second */
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
	/* 21000000/21000 = 1000 overflows per second - every 1ms one interrupt */
	/* SysTick interrupt every N clock pulses: set reload to N-1 */
	systick_set_reload(20999);
	systick_interrupt_enable();
	/* Start counting. */
	systick_counter_enable();

}

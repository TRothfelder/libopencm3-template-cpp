/*
 * clock.c
 *
 *  Created on: 27.05.2018
 *      Author: kt
 */
#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif
	#include <libopencm3/stm32/rcc.h>
	#include <libopencm3/cm3/systick.h>
  #include <libopencm3/cm3/scb.h>
#ifdef __cplusplus
}
#endif

#include "config/clock.hpp"

void Clock::setup( void ) {
  rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
}


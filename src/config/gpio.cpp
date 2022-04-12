/*
 * gpio.c
 *
 *  Created on: 27.05.2018
 *      Author: kt
 */

#ifdef __cplusplus
extern "C" {
#endif
	#include <libopencm3/stm32/rcc.h>
	#include <libopencm3/stm32/gpio.h>
#ifdef __cplusplus 
}
#endif

#include "config/gpio.hpp"

#define LED_PORT GPIOC
#define RCC_LED_PORT RCC_GPIOC
#define LED_PIN GPIO13

void Gpio::setup( void ) {
  rcc_periph_clock_enable(RCC_LED_PORT);
  gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN);
  gpio_clear(LED_PORT, LED_PIN);
}

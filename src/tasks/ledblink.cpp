/*
 * ledblink.c
 *
 *  Created on: 23.05.2018
 *      Author: kt
 */
extern "C" {
	#include "FreeRTOS.h"
	#include "task.h"

	#include <libopencm3/stm32/gpio.h>

	#if defined(SEGGER_SYSVIEW_USE)
		#include "SEGGER_SYSVIEW.h"
	#endif //SEGGER_SYSVIEW_USE
}

#include "tasks/ledblink.hpp"

xTaskHandle ledblinkTaskHandle = NULL;

void ledblink_task(void *arg) {
	//unsigned istr;
	(void)arg;

	for (;;) {
		gpio_toggle(GPIOD,GPIO13 | GPIO15);
		#if defined(DEBUG)
			gpio_toggle(GPIOD, GPIO12 | GPIO14);
		#endif
		#if defined(SEGGER_SYSVIEW_USE)
			SEGGER_SYSVIEW_Print("Ledblink task executed.");
		#endif
		vTaskDelay(250 / portTICK_RATE_MS);
	}
}

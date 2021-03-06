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

#include "tasks/mytasks.hpp"

void MyTasks::ledblink(void *arg) {
	//unsigned istr;
	freertosArgs_t *args = (freertosArgs_t *) arg;

	uint32_t port = *( uint32_t *) args->args[0];
	uint16_t gpio = *( uint16_t *) args->args[1];

	for (;;) {
		gpio_toggle(port, gpio);
		#if defined(DEBUG)
			gpio_toggle(port, gpio << 1); /* GPIO12 is uint16_t */ /* GPIOD is uint32_t */
		#endif
		#if defined(SEGGER_SYSVIEW_USE)
			SEGGER_SYSVIEW_Print("Ledblink task executed.");
		#endif
		vTaskDelay(500 / portTICK_RATE_MS);
	}
}

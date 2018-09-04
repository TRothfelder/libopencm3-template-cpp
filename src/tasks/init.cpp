extern "C" {
	#include "FreeRTOS.h"
	#include "task.h"

	#include <libopencm3/stm32/gpio.h>
}

#include "tasks/init.hpp"
#include "tasks/ledblink.hpp"

xTaskHandle initTaskHandle = NULL;

void init_task(void *arg) {
	(void)arg;

	xTaskCreate(ledblink_task,"LEDBLINK",100,NULL,configMAX_PRIORITIES-1, &ledblinkTaskHandle);

	vTaskDelay(10000 / portTICK_RATE_MS);
	gpio_toggle(GPIOD,GPIO14);
	vTaskDelete( initTaskHandle );
	initTaskHandle = NULL;
}

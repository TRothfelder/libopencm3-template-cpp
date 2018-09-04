extern "C" {
	#include "FreeRTOS.h"
	#include "task.h"

	#if defined(SEGGER_SYSVIEW_USE)
		#include "SEGGER_SYSVIEW.h"
	#endif //SEGGER_SYSVIEW_USE

	#include <libopencm3/stm32/gpio.h>
}

#include "tasks/mytasks.hpp"

uint16_t led1 = GPIO12;
uint16_t led2 = GPIO14;

void MyTasks::init( void *arg ) {
	( void ) arg;

	xTaskCreate(&MyTasks::ledblink,"LEDBLINK1",100,&led1,configMAX_PRIORITIES-1, &tasks.ledblinkTaskHandle1);
	#if defined(SEGGER_SYSVIEW_USE)
		SEGGER_SYSVIEW_Print("LEDBLINK1 task created.");
	#endif

	vTaskDelay(250 / portTICK_RATE_MS);

	xTaskCreate(&MyTasks::ledblink,"LEDBLINK2",100,&led2,configMAX_PRIORITIES-1, &tasks.ledblinkTaskHandle2);
	#if defined(SEGGER_SYSVIEW_USE)
		SEGGER_SYSVIEW_Print("LEDBLINK2 task created.");
	#endif

	vTaskDelay(10000 / portTICK_RATE_MS);
	vTaskDelete( MyTasks::initTaskHandle );
	MyTasks::initTaskHandle = NULL;
}

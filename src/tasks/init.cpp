extern "C" {
	#include "FreeRTOS.h"
	#include "task.h"

	#if defined(SEGGER_SYSVIEW_USE)
		#include "SEGGER_SYSVIEW.h"
	#endif //SEGGER_SYSVIEW_USE

	#include "gfx.h"

	#include <libopencm3/stm32/gpio.h>
}

#include "tasks/mytasks.hpp"

const uint16_t led1io = GPIO12;
const uint32_t led1Port = GPIOD;
freertosArgs_t args1 = {
	.count = 2,
	.args = {
		(void *) &led1Port,
		(void *) &led1io,
	},
};

const uint16_t led2io = GPIO14;
const uint32_t led2Port = GPIOD;
freertosArgs_t args2 = {
	.count = 2,
	.args = {
		(void *) &led2Port,
		(void *) &led2io,
	},
};

void MyTasks::init( void *arg ) {
	( void ) arg;

	//unsigned istr;
	(void)arg;
	coord_t		width, height;
	coord_t		i, j;

	gfxInit();
	// Code Here
	// Get the screen size
	gdispSetOrientation(GDISP_ROTATE_270);
	width = gdispGetWidth();
	height = gdispGetHeight();
	gdispDrawBox(10, 10, width/2, height/2, Yellow);
	gdispFillArea(width/2, height/2, width/2-10, height/2-10, Blue);
	gdispDrawLine(5, 30, width-50, height-40, Red);
	for(i = 5, j = 0; i < width && j < height; i += 7, j += i/20)
			gdispDrawPixel(i, j, White);

	xTaskCreate(&MyTasks::ledblink,"LEDBLINK1",100,( void* )&args1,configMAX_PRIORITIES-1, &tasks.ledblinkTaskHandle1);
	#if defined(SEGGER_SYSVIEW_USE)
		SEGGER_SYSVIEW_Print("LEDBLINK1 task created.");
	#endif

	vTaskDelay(250 / portTICK_RATE_MS);

	xTaskCreate(&MyTasks::ledblink,"LEDBLINK2",100,( void* )&args2,configMAX_PRIORITIES-1, &tasks.ledblinkTaskHandle2);
	#if defined(SEGGER_SYSVIEW_USE)
		SEGGER_SYSVIEW_Print("LEDBLINK2 task created.");
	#endif

	vTaskDelay(10000 / portTICK_RATE_MS);
	vTaskDelete( MyTasks::initTaskHandle );
	MyTasks::initTaskHandle = NULL;
}

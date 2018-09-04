#include "FreeRTOS.h"
#include "task.h"

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ) {
	( void ) xTask;
	( void ) pcTaskName;
	for(;;);	// Loop forever here..
}

/*
void vApplicationIdleHook( void ) {
	for(;;);	// Loop forever here..
}

void vApplicationMallocFailedHook(void) {
	for(;;);	// Loop forever here..
}

void vApplicationTickHook( void ) {
	for(;;);	// Loop forever here..
}
*/

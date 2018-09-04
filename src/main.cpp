/* SIMPLE LED task demo:
 * Fri Mar 24 22:45:55 2017	Warren Gay Ve3WWG
 *
 * 1) The LED on PC13 is on/off by USB control messages.
 * 2) Bulk endpoint messages are received (EP 0x02)
 * 3) Case inverted message is echoed back on EP 0x83.
 */
extern "C"{
	#include "FreeRTOS.h"
	#include "task.h"

	#if defined(SEGGER_SYSVIEW_USE)
		#include "SEGGER_SYSVIEW.h"
	#endif //SEGGER_SYSVIEW_USE
}

//#include "tasks/init.hpp"
#include "config/clock.hpp"
#include "config/gpio.hpp"
#include "tasks/mytasks.hpp"

/*
 * Main program:
 */
extern "C" int main(void) {
  Clock::setup();
  Gpio::setup();

	#if defined(SEGGER_SYSVIEW_USE)
		SEGGER_SYSVIEW_Conf();
	#endif
	xTaskCreate(MyTasks::init,"INIT",3096,NULL,0, &MyTasks::initTaskHandle);

	vTaskStartScheduler();

	for (;;); // Should never get here
	return 0;
}

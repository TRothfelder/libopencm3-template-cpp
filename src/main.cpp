/* SIMPLE LED task demo:
 * Fri Mar 24 22:45:55 2017	Warren Gay Ve3WWG
 *
 * 1) The LED on PC13 is on/off by USB control messages.
 * 2) Bulk endpoint messages are received (EP 0x02)
 * 3) Case inverted message is echoed back on EP 0x83.
 */
#ifdef __cplusplus
extern "C" {
#endif
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "FreeRTOS.h"
#include "task.h"
#ifdef __cplusplus
}
#endif

//#include "tasks/init.hpp"
#include "config/clock.hpp"
#include "config/gpio.hpp"


void blinky(void *args) {
  (void) args;
  for (;;) {
    gpio_toggle(GPIOC, GPIO13);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

/*
 * Main program:
 */
extern "C" int main(void) {
  Clock::setup();
  Gpio::setup();

	xTaskCreate(blinky,"INIT",1000,NULL,1, NULL);

	vTaskStartScheduler();

  for (;;){
  }// Should never get here

	return 0;
}

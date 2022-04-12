#ifdef __cplusplus
extern "C" {
#endif
#include "FreeRTOS.h"
#include "task.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/scb.h>
#ifdef __cplusplus
}
#endif

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

void vPortSetupTimerInterrupt( void ) {
    /* Calculate the constants required to configure the tick interrupt. */
    #if ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
            xMaximumPossibleSuppressedTicks = portMAX_24_BIT_NUMBER / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
    #endif /* configUSE_TICKLESS_IDLE */
	
	/* 72MHz / 8 => 9 000 000 counts per second */
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
	/* 9 000 000/ 9 000 = 1000 overflows per second - every 1ms one interrupt */
	/* SysTick interrupt every N clock pulses: set reload to N-1 */
  const uint32_t reload_val = (configCPU_CLOCK_HZ) / 8 / (configSYSTICK_CLOCK_HZ) - 1 ;
  systick_set_reload(reload_val);
  systick_clear();
	systick_interrupt_enable();
  /* Start counting. */
	systick_counter_enable();
	scb_set_priority_grouping(SCB_AIRCR_PRIGROUP_GROUP16_NOSUB);
}

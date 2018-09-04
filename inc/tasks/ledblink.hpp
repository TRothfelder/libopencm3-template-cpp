/*
 * ledblink.h
 *
 *  Created on: 23.05.2018
 *      Author: kt
 */

#ifndef INC_TASKS_LEDBLINK_H_
#define INC_TASKS_LEDBLINK_H_

#include "FreeRTOS.h"
#include "task.h"

extern xTaskHandle ledblinkTaskHandle;
void ledblink_task(void *arg);

#endif /* INC_TASKS_LEDBLINK_H_ */

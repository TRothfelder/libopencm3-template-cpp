/*
 * init.h
 *
 *  Created on: 23.05.2018
 *      Author: kt
 */

#ifndef INC_TASKS_INIT_H_
#define INC_TASKS_INIT_H_

#include "FreeRTOS.h"
#include "task.h"


extern xTaskHandle initTaskHandle;
void init_task(void *arg);

#endif /* INC_TASKS_INIT_H_ */

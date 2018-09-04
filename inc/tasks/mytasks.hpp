/*
 * init.h
 *
 *  Created on: 23.05.2018
 *      Author: kt
 */

#ifndef INC_TASKS_MYTASKS_H_
#define INC_TASKS_MYTASKS_H_

extern "C" {
  #include "FreeRTOS.h"
  #include "task.h"
}

class MyTasks {
  public:
    static xTaskHandle initTaskHandle;
    static void init ( void *arg);

    xTaskHandle ledblinkTaskHandle1;
    xTaskHandle ledblinkTaskHandle2;
    static void ledblink ( void *arg);
};

extern MyTasks tasks;

#endif /* INC_TASKS_MYTASKS_H_ */

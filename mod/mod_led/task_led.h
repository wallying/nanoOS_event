/**
 * file:    task_led.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __TASK_LED_H__
#define __TASK_LED_H__


#include "os_api.h"


extern os_tcb task_led;
void task_ledEntry(os_event evt, void *data);


#endif /* __TASK_LED_H__ */


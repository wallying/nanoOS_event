/**
 * file:    Task_Main.h
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#ifndef __TASK_MAIN_H__
#define __TASK_MAIN_H__


#include "os_api.h"


extern os_tcb task_main;
void task_mainEntry(os_event evt, void *data);


#endif /* __TASK_MAIN_H__ */


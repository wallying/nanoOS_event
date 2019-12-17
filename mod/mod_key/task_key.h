/**
 * file:    task_key.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __TASK_KEY_H__
#define __TASK_KEY_H__


#include "os_api.h"


extern os_tcb task_key;
void task_keyEntry(os_event evt, void *data);


#endif /* __TASK_KEY_H__ */


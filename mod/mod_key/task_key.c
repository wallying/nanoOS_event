/**
 * file:    task_key.c
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#include "main.h"


os_tcb task_key;


/*----------------------------------------------------------------------------*/
void task_keyEntry(os_event evt, void *data)
{
    if (evt == OS_EVT_POLL) {

    } else if (evt == OS_EVT_INIT) {

    }
}



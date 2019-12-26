/**
 * file:    main.h
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#ifndef __MAIN_H__
#define __MAIN_H__


#include "os_api.h"


#include "task_main.h"


enum {
    USER_EVT_NONE = OS_EVT_MAX,

    LED_EVT_CHANGE,
    LED_EVT_UPDATE,

	KEY_EVT_SCAN,
    KEY_EVT_DOWN,
    KEY_EVT_UP,

};


void main_loop_callback(void);
void main_idle_callback(void);


#endif /*__MAIN_H__*/


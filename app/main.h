/**
 * file:    main.h
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#ifndef __MAIN_H__
#define __MAIN_H__


#include "os_api.h"
#include "bsp.h"

#include "task_main.h"
#include "mod_key/task_key.h"
#include "mod_led/task_led.h"

enum {
    USER_EVT_NONE = OS_EVT_MAX,

    KEY_EVT_DOWN,
    KEY_EVT_UP,

    LED_EVT_PROC,
    LED_EVT_FLASH,
};


void main_loop_callback(void);
void main_idle_callback(void);


#endif /*__MAIN_H__*/


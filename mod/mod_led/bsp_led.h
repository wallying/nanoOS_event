/**
 * file:    bsp_led.h
 * author:  wallying@foxmail.com
 * date:    2019-12-18
 **/


#ifndef __BSP_LED_H__
#define __BSP_LED_H__



#include "os_api.h"


typedef enum {
    LED_RED = 0,
//    LED_GREEN,
//    LED_BLUE,
//    LED_YELLOW,
//    LED_WHITE,
    LED_NUM,
} ledIdx_e;

typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_TOGGLE,
} ledCmd_e;


void bsp_ledInit(void);
void bsp_ledCtrl(ledIdx_e led, ledCmd_e cmd);


#endif /* __BSP_LED_H__ */



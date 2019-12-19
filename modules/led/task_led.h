/**
 * file:    task_led.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __TASK_LED_H__
#define __TASK_LED_H__


#include "os_api.h"


typedef enum {
    LED_KEEP_ON = 0,
    LED_KEEP_OFF,
    LED_ON_OFF,
    LED_OFF_ON,
} ledMode_e;

/* modified */
typedef enum {
    LED_PRIO_POWERUP = 0,
    LED_PRIO_CLEAR_BOND_INFO,
    LED_PRIO_LOW_BAT,
	LED_PRIO_LOWING_BAT,
    LED_PRIO_PAIR_SUCCESSED,
    LED_PRIO_PAIR_FAILED,
    LED_PRIO_FACTORY_RESET,
    LED_PRIO_PAIRING,
    LED_PRIO_MIC,
    LED_PRIO_BLE_KEY_PRESS,
    LED_PRIO_IR_KEY_PRESS,
    LED_PRIO_NUM,
    LED_PRIO_NONE = 0xFF,
} ledPrio_e;

typedef struct {
	ledMode_e mode;
	os_u8 cnt;
	os_u16 onTime;
	os_u16 offTime;
} ledParam_t;

typedef struct {
	ledPrio_e prio;
	ledMode_e mode;
	os_u8 cnt;
	os_u16 onTime;
	os_u16 offTime;
    os_u32 bitMap;
    os_u32 prevTime;
} ledProc_t;



extern os_tcb task_led;

void app_ledStart(ledIdx_e led, ledPrio_e prio);
void app_ledStop(ledIdx_e led, ledPrio_e prio);
void task_ledEntry(os_event evt, void *data);


#endif /* __TASK_LED_H__ */


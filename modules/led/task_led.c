/**
 * file:    task_led.c
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#include "main.h"


os_tcb task_led;

static ledProc_t ledProc[LED_NUM];
static const ledParam_t ledParam[LED_NUM][LED_PRIO_NUM] =
{
    /*LED_RED*/
    {
        {LED_ON_OFF,    1, 10000,    0}, //LED_PRIO_POWERUP
        {LED_ON_OFF,    3,  2500, 2500}, //LED_PRIO_CLEAR_BOND_INFO
        {LED_ON_OFF,    5,  3000, 3000}, //LED_PRIO_LOW_BAT
        {LED_ON_OFF, 0xFF,  5000, 5000}, //LED_PRIO_LOWING_BAT
        {LED_ON_OFF,    1, 10000,    0}, //LED_PRIO_PAIR_SUCCESSED
        {LED_ON_OFF,    3,  1000, 1000}, //LED_PRIO_PAIR_FAILED
        {LED_ON_OFF,    3,  3000, 3000}, //LED_PRIO_FACTORY_RESET
        {LED_ON_OFF, 0xFF,  3000, 3000}, //LED_PRIO_PAIRING
    	{LED_KEEP_ON,   0,     0,    0}, //LED_PRIO_MIC
        {LED_KEEP_ON,   0,     0,    0}, //LED_PRIO_BLE_KEY_PRESS
        {LED_ON_OFF, 0xFF,  1080, 1080}, //LED_PRIO_IR_KEY_PRESS
    },
};


static os_timer ledTimer;
static void ledTimerCB(void *param)
{
    os_event_post(&task_led, LED_EVT_UPDATE, NULL);
}


/*----------------------------------------------------------------------------*/
void app_ledInit(void)
{
    bsp_ledInit();

    for (os_u8 i = 0; i < LED_NUM; i++) {
        ledProc[i].prio = LED_PRIO_NONE;
        ledProc[i].bitMap = 0x00;
        bsp_ledCtrl((ledIdx_e)i, LED_OFF);
    }
}

void app_ledStart(ledIdx_e led, ledPrio_e prio)
{
	ledProc[led].bitMap |= (0x01 << prio);
	if (prio <= ledProc[led].prio) {
		ledProc[led].prio = LED_PRIO_NONE;
		os_event_post(&task_led, LED_EVT_CHANGE, NULL);
	}
}

void app_ledStop(ledIdx_e led, ledPrio_e prio)
{
	if (ledProc[led].bitMap & (0x01 << prio)) {
		ledProc[led].bitMap &= ~(0x01 << prio);
		if (prio <= ledProc[led].prio) {
			ledProc[led].prio = LED_PRIO_NONE;
			bsp_ledCtrl(led, LED_OFF);
			os_event_post(&task_led, LED_EVT_CHANGE, NULL);
		}
	}
}

/*----------------------------------------------------------------------------*/
static void ledUpdate(ledIdx_e led)
{
    ledProc[led].prevTime = os_time_get();
    if ((ledProc[led].cnt != 0x00) &&
        (ledProc[led].cnt != 0xFF)) {
        ledProc[led].cnt--;
    }

    if (ledProc[led].cnt) {
        os_event_post(&task_led, LED_EVT_UPDATE, NULL);
    } else {
        ledProc[led].bitMap &= ~(0x01 << ledProc[led].prio);
        ledProc[led].prio = LED_PRIO_NONE;
        bsp_ledCtrl(led, LED_OFF);
        os_event_post(&task_led, LED_EVT_CHANGE, NULL);
    }
}


static os_u16 ledFlashControl(ledIdx_e led)
{
    os_u32 time = os_time_get();
    os_u16 retTime = 0;

    if (ledProc[led].mode == LED_ON_OFF) {
        if (time < (ledProc[led].prevTime + ledProc[led].onTime)) {
            bsp_ledCtrl(led, LED_ON);
            retTime = ledProc[led].prevTime + ledProc[led].onTime -
                      time;
        } else if (time < (ledProc[led].prevTime + ledProc[led].onTime +
                           ledProc[led].offTime)) {
            bsp_ledCtrl(led, LED_OFF);
            retTime = ledProc[led].prevTime + ledProc[led].onTime +
                      ledProc[led].offTime - time;
        } else {
            ledUpdate(led);
        }
    } else if (ledProc[led].mode == LED_OFF_ON) {
        if (time < (ledProc[led].prevTime + ledProc[led].onTime)) {
            bsp_ledCtrl(led, LED_OFF);
            retTime = ledProc[led].prevTime + ledProc[led].onTime -
                      time;
        } else if (time < (ledProc[led].prevTime + ledProc[led].onTime +
                           ledProc[led].offTime)) {
            bsp_ledCtrl(led, LED_ON);
            retTime = ledProc[led].prevTime + ledProc[led].onTime +
                      ledProc[led].offTime - time;
        } else {
            ledUpdate(led);
        }
    }
    return retTime;
}


void task_ledEntry(os_event evt, void *data)
{
    if (evt == OS_EVT_INIT) {
        app_ledInit();
    }
    else if (evt == LED_EVT_CHANGE) {
        for (os_u8 i = 0; i < LED_NUM; i++) {
            for (os_u8 j = 0; j < LED_PRIO_NUM; j++) {
                if (ledProc[i].bitMap & (0x01 << j)) {
                    if (j < ledProc[i].prio) {
                        os_timer_stop(&ledTimer);
                        ledProc[i].prio = (ledPrio_e)j;
                        ledProc[i].mode = ledParam[i][j].mode;
                        ledProc[i].cnt = ledParam[i][j].cnt;
                        ledProc[i].onTime = ledParam[i][j].onTime;
                        ledProc[i].offTime = ledParam[i][j].offTime;
                        ledProc[i].prevTime = os_time_get();
                        os_event_post(&task_led, LED_EVT_UPDATE, NULL);
                    }
                    break;
                }
            }
        }
    }
    else if (evt == LED_EVT_UPDATE) {
        os_u8 needStartTimer = 0x00;
        os_u16 nextPollTime[LED_NUM] = {0};
        os_u16 tempMinTime = 0xFFFF;

        for (os_u8 i = 0; i < LED_NUM; i++) {
            if (ledProc[i].prio != LED_PRIO_NONE) {
                if (ledProc[i].mode == LED_KEEP_ON) {
                    bsp_ledCtrl((ledIdx_e)i, LED_ON);
                } else if (ledProc[i].mode == LED_KEEP_OFF) {
                    bsp_ledCtrl((ledIdx_e)i, LED_OFF);
                } else {
                    nextPollTime[i] = ledFlashControl((ledIdx_e)i);
                }
            }
        }
        for (os_u8 i = 0; i < LED_NUM; i++) {
            if ((nextPollTime[i]) && (nextPollTime[i] < tempMinTime)) {
                needStartTimer = 0x01;
                tempMinTime = nextPollTime[i];
            }
        }
        if (needStartTimer) {
            os_timer_start(&ledTimer, tempMinTime, ledTimerCB, NULL);
        }
    }
}



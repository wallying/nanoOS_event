/**
 * file:    task_main.c
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#include "main.h"


os_tcb task_main;

static os_u32 cbCnt = 0;
static os_timer cbTmr;


void cbTmr_CB(void *param)
{
    os_timer_restart(&cbTmr, 1000);

    cbCnt++;
    if (cbCnt == 100) {
        os_timer_stop(&cbTmr);
    }
}

/*----------------------------------------------------------------------------*/
void task_mainEntry(os_event evt, void *data)
{
    if (evt == OS_EVT_POLL) {

    } else if (evt == OS_EVT_INIT) {
        os_timer_start(&cbTmr, 1000, cbTmr_CB, &cbCnt);
    }
}



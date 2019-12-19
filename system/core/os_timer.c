/**
 * file:    os_timer.c
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 * brief:   os timer task
 **/


#include "os_api.h"


static os_tcb os_timer_task;
static os_timer *os_timer_list = NULL;


/*----------------------------------------------------------------------------*/
void os_timer_task_entry(os_event evt, void *data)
{
    if (evt == OS_EVT_POLL) {
        os_timer *srch = os_timer_list;
        for (; (srch != NULL) && (srch->tmo == 0); srch = srch->next) {
            os_timer_list = srch->next; /* first remove, then callback */
            srch->next = NULL;
            if (srch->func != NULL) {
                srch->func(srch->param);
            }
        }
    } else if (evt == OS_EVT_INIT) {
        os_timer_list = NULL;
    }
}


void os_timer_init(void)
{
    os_task_init(&os_timer_task, os_timer_task_entry, NULL);
}


void os_timer_update(os_time time)
{
    os_timer *srch = os_timer_list;
    for (; srch != NULL; srch = srch->next) {
        if (srch->tmo > time) {
            srch->tmo -= time;
        } else {
            srch->tmo = 0;
        }
    }

    if ((os_timer_list != NULL) && (os_timer_list->tmo == 0)) {
        os_task_poll(&os_timer_task, 0x01);
    }
}


/*----------------------------------------------------------------------------*/
static void os_timer_remove(os_timer *tmr)
{
    /* remove tmr from the os_timer_list */
    if (tmr == os_timer_list) {
        os_timer_list = tmr->next;
        tmr->next = NULL;
    } else {
        os_timer *srch = os_timer_list;
        for (; srch != NULL; srch = srch->next) {
            if (srch->next == tmr) {
                srch->next = tmr->next;
                tmr->next = NULL;
                break;
            }
        }
    }
}


static void os_timer_insert(os_timer *tmr)
{
    os_timer_remove(tmr);

    /* insert tmr into the os_timer_list */
    if (os_timer_list == NULL) {
        tmr->next = os_timer_list;
        os_timer_list = tmr;
    } else {
        os_timer *prev = NULL;
        os_timer *srch = os_timer_list;
        for (; srch != NULL; srch = srch->next) {
            if (srch->tmo >= tmr->tmo) {
                if (prev == NULL) {
                    /* tmr's timeout is min, add to os_timer_list head */
                    tmr->next = os_timer_list;
                    os_timer_list = tmr;
                } else {
                    /* add tmr to os_timer_list */
                    tmr->next = prev->next;
                    prev->next = tmr;
                }
                break;
            }
            prev = srch;
        }
        /* tmr's timeout is max, add to os_timer_list tail */
        if (srch == NULL) {
            tmr->next = prev->next;
            prev->next = tmr;
        }
    }
}



/*----------------------------------------------------------------------------*/

void os_timer_start(os_timer *tmr, os_time tmo, void (*func)(void *), void *param)
{
    if ((tmr == NULL) || (tmo == 0) || (func == NULL)) {
        return;
    }

    tmr->tmo = tmo;
    tmr->func = func;
    tmr->param = param;

    os_timer_insert(tmr);
}


void os_timer_restart(os_timer *tmr, os_time tmo)
{
    if (tmr != NULL) {
        tmr->tmo = tmo;
        os_timer_insert(tmr);
    }
}


void os_timer_stop(os_timer *tmr)
{
    if (tmr != NULL) {
        tmr->tmo = 0;
        tmr->func = NULL;
        tmr->param = NULL;
        os_timer_remove(tmr);
    }
}


os_u8 os_timer_pending(void)
{
    return (os_timer_list != NULL) ? 0x01 : 0x00;
}


os_time os_timer_timeout(void)
{
    return (os_timer_list != NULL) ? os_timer_list->tmo : 0;
}


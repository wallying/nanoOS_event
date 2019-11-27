/**
 * file:    os_core.c
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 * brief:   os_task.c
 *          os_event.c
 *          os_clock.c
 **/


#include "os_api.h"
#include "bsp.h"


#define OS_VERSION          (os_u16)(0x0101) /* V01.01 */


/* os state for task */
#define OS_STATE_DORMANT    (os_u8)(0x00)
#define OS_STATE_RUNNING    (os_u8)(0x80)


static os_cb os_loop_cb = NULL;
static os_cb os_idle_cb = NULL;

static os_tcb *os_task_list = NULL;

static volatile os_u8 os_event_poll = 0; /* just 0 or 1 */

typedef os_u16 os_evtn; /* os event number type */
static os_evtn os_event_idx = 0; /* read index of os_event_queue */
static os_evtn os_event_num = 0; /* number of event */

typedef struct {
    os_event evt;
    void *data;
    os_tcb *tcb;
} os_evtq; /* os event queue type */
static os_evtq os_event_queue[OS_CFG_EVENT_NUM_MAX];



/*----------------------------------------------------------------------------*/
void os_task_init(os_tcb *tcb, os_task task, void *data)
{
    if (tcb == NULL) {
        return;
    }

    os_tcb *prev = NULL;
    os_tcb *srch = os_task_list;
    for (; srch != NULL; srch = srch->next) {
        if (srch == tcb) {
            return; /* tcb is already in the os_task_lis */
        }
        prev = srch;
    }

    /* init task tcb */
    tcb->task = task;
    tcb->flag = 0x00;
    tcb->state = OS_STATE_RUNNING;

    /* insert tcb to the os_task_list tail */
    if (prev == NULL) {
        tcb->next = os_task_list;
        os_task_list = tcb;
    } else {
        tcb->next = prev->next;
        prev->next = tcb;
    }

    /* call tcb with OS_EVT_INIT */
    if (tcb->task != NULL) {
        tcb->task(OS_EVT_INIT, data);
    }
}



void os_task_exit(os_tcb *tcb, void *data)
{
    if (tcb == NULL) {
        return;
    }

    os_tcb *srch = os_task_list;
    for (; (srch != NULL) && (srch != tcb); srch = srch->next);
    if (srch == NULL) {
        return; /* tcb is not in the os_task_list */
    }

    /* tcb is in the os_task_list, call tcb with OS_EVT_EXIT */
    if (tcb->state != OS_STATE_DORMANT) {
        tcb->state = OS_STATE_DORMANT;
        if (tcb->task != NULL) {
            tcb->task(OS_EVT_EXIT, data);
        }
        tcb->task = NULL;
    }

    /* remove tcb from the os_task_list */
    if (tcb == os_task_list) {
        os_task_list = os_task_list->next;
        tcb->next = NULL;
    } else {
        for (srch = os_task_list; srch != NULL; srch = srch->next) {
            if (srch->next == tcb) {
                srch->next = tcb->next;
                tcb->next = NULL;
                break;
            }
        }
    }
}


void os_task_poll(os_tcb *tcb, os_flag flag)
{
    if ((tcb != NULL) && (tcb->state == OS_STATE_RUNNING)) {
        if (flag != 0x00) {
            tcb->flag |= flag;
            os_event_poll = 1;
        }
    }
}




/*----------------------------------------------------------------------------*/
static void os_task_call(os_tcb *tcb, os_event evt, void *data)
{
    if (tcb != NULL) {
        if (tcb->state == OS_STATE_RUNNING) {
            if (evt == OS_EVT_EXIT) {
                os_task_exit(tcb, data);
            } else {
                if (tcb->task != NULL) {
                    tcb->task(evt, data);
                }
            }
        }
    }
}



static void os_task_polling(void)
{
    static os_flag flag = 0x00;

    if (os_event_poll) {
        os_event_poll = 0;
        os_tcb *srch = os_task_list;
        for (; srch != NULL; srch = srch->next) {
            if (srch->flag) {
                flag = srch->flag;
                srch->flag = 0x00;
                srch->state = OS_STATE_RUNNING;
                if (srch->task != NULL) {
                    srch->task(OS_EVT_POLL, &flag);
                }
            }
        }
    }
}




/*---------------------------------------------------------------------------*/
void os_event_clear(void)
{
    os_event_idx = 0;
    os_event_num = 0;
}


void os_event_emit(os_tcb *tcb, os_event evt, void *data)
{
    os_task_call(tcb, evt, data);
}


os_err os_event_post(os_tcb *tcb, os_event evt, void *data)
{
    static os_evtn widx = 0; /* write index of os_event_queue */

    if (tcb == NULL) {
        return OS_ERR_NULL;
    }
    if (os_event_num == OS_CFG_EVENT_NUM_MAX) {
        return OS_ERR_FULL;
    }

    widx = (os_evtn)(os_event_idx + os_event_num) % OS_CFG_EVENT_NUM_MAX;
    os_event_queue[widx].evt = evt;
    os_event_queue[widx].data = data;
    os_event_queue[widx].tcb = tcb;
    ++os_event_num;

    return OS_ERR_NONE;
}


static void os_event_handle(void)
{
    static os_event evt = OS_EVT_NONE;
    static void *data = NULL;
    static os_tcb *receiver = NULL;

    if (os_event_num > 0) {
        evt = os_event_queue[os_event_idx].evt;
        data = os_event_queue[os_event_idx].data;
        receiver = os_event_queue[os_event_idx].tcb;

        os_event_idx = (os_event_idx + 1) % OS_CFG_EVENT_NUM_MAX;
        --os_event_num;

        if (receiver != NULL) {
            os_task_call(receiver, evt, data);
        }
    }
}



/*---------------------------------------------------------------------------*/
void os_timer_update(os_time time);

static volatile os_time os_sys_time = 0;

void os_clock_isr(void)
{
    os_sys_time++;

    os_timer_update(1);
}

void os_clock_update(void)
{
    static os_tick previous_tick = 0; /* must static */
    static os_tick residual_tick = 0; /* must static */
    static os_tick current_tick = 0;
    static os_tick elapsed_tick = 0;
    static os_time elapsed_time = 0;

    current_tick = os_tick_get();
    elapsed_tick = current_tick - previous_tick + residual_tick;
    if (current_tick != previous_tick) {
        elapsed_time = (elapsed_tick / OS_CFG_TIME_UINT);
        residual_tick = (elapsed_tick % OS_CFG_TIME_UINT);
        previous_tick = current_tick;

        if (elapsed_time) {
            os_sys_time += elapsed_time;

            os_timer_update(elapsed_time);
        }
    }
}


os_time os_time_get(void)
{
    return os_sys_time;
}




/*----------------------------------------------------------------------------*/
void os_init(os_cb loop, os_cb idle)
{
    os_loop_cb = loop;
    os_idle_cb = idle;

    os_task_list = NULL;

    os_event_idx = 0;
    os_event_num = 0;

    void os_timer_init(void);
    os_timer_init();
}


void os_start(void)
{
    while (1) {
        do {
            if (os_loop_cb) {
                os_loop_cb();
            }
            os_task_polling();
            os_event_handle();
        } while (os_event_num + os_event_poll);
        if (os_idle_cb) {
            os_idle_cb();
        }
    }
}

os_u16 os_version(void)
{
    return OS_VERSION;
}



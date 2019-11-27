/**
 * file:    os_api.h
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 * brief:
 **/


#ifndef __OS_API_H__
#define __OS_API_H__


#include "os_cfg.h"


/*============================================================================*/
/* os_type.h */

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef signed char os_s8;
typedef unsigned char os_u8;

typedef signed short os_s16;
typedef unsigned short os_u16;

typedef signed long os_s32;
typedef unsigned long os_u32;

typedef signed long long os_s64;
typedef unsigned long long os_u64;


/*============================================================================*/
/* os_cpu.h */

typedef os_u32 os_tick; /* determined by MCU hardware timer bit */

#define OS_INT_DISABLE()        //__disable_interrupt()
#define OS_INT_ENABLE()         //__enable_interrupt()

/* Implementation of the function should be completed by the user */
void os_clock_init(void);
os_tick os_tick_get(void);


/*============================================================================*/
/* os_core.h */

enum {
    OS_EVT_NONE = 0,
    OS_EVT_POLL,
    OS_EVT_INIT,
    OS_EVT_EXIT,
    OS_EVT_MAX,
};

typedef enum {
    OS_ERR_NONE = 0,
    OS_ERR_NULL,
    OS_ERR_FULL,
} os_err;

typedef os_u32 os_time;

typedef os_u8 os_flag; /* <os_u8>, os_u16, os_u32 */
typedef os_u8 os_event; /* max=255 */

typedef void (*os_cb)(void);
typedef void (*os_task)(os_event evt, void *data);

typedef struct _os_tcb {
    struct _os_tcb *next;
    os_task task;
    os_flag flag;
    os_u8 state;
} os_tcb;

typedef struct _os_timer {
    struct _os_timer *next;
    os_time tmo;
    void (*func)(void *);
    void *param;
} os_timer;


void os_init(os_cb loop, os_cb idle);
void os_start(void);
void os_clock_isr(void);
void os_clock_update(void);
os_time os_time_get(void);
os_u16 os_version(void);


void os_task_init(os_tcb *tcb, os_task task, void *data);
void os_task_exit(os_tcb *tcb, void *data);
void os_task_poll(os_tcb *tcb, os_flag flag);


void os_event_clear(void);
void os_event_emit(os_tcb *tcb, os_event evt, void *data);
os_err os_event_post(os_tcb *tcb, os_event evt, void *data);


void os_timer_start(os_timer *tmr, os_time tmo, void (*func)(void *), void *param);
void os_timer_restart(os_timer *tmr, os_time tmo);
void os_timer_stop(os_timer *tmr);


#endif /*__OS_API_H__*/


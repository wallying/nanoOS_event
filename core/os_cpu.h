/**
 * file:    os_cpu.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 * brief:
 **/


#ifndef __OS_CPU_H__
#define __OS_CPU_H__


#include "os_cfg.h"
#include "os_type.h"


typedef os_u32 os_tick; /* determined by MCU hardware timer bit */


#define OS_INT_DISABLE()        //irq_disable()
#define OS_INT_ENABLE()         //irq_enable()


/* Implementation of the function should be completed by the user */
void os_clock_init(void);
os_tick os_tick_get(void);



#endif /*__OS_CPU_H__*/


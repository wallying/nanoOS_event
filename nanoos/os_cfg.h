/**
 * file:    os_cfg.h
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#ifndef __OS_CFG_H__
#define __OS_CFG_H__


/*============================================================================*/
#define OS_CFG_EVENT_NUM_MAX        (32u) /* os_u16 */


/*============================================================================*/
/* os_clock_init() : os time clock frequency: 16MHz */
#define OS_TIME_CLOCK_HZ            (16000000)
#define OS_CFG_TIME_UINT            (OS_TIME_CLOCK_HZ/1000)


#endif /* __OS_CFG_H__ */


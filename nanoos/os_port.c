/**
 * file:    os_port.c
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 * brief:   os port template file.
 **/


#include "os_api.h"
#include "bsp.h"


/*----------------------------------------------------------------------------*/
void os_clock_init(void)
{

}


os_tick os_tick_get(void)
{
    return 0;
}


void main_loop_callback(void)
{
    os_clock_update();
}


void main_idle_callback(void)
{
    /* enter idle/sleep state */

    /* exit idle/sleep state */
}


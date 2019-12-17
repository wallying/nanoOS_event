/**
 * file:    main.c
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#include "main.h"


int main(void)
{
    OS_INT_DISABLE();

    bsp_init();
    os_clock_init();

    OS_INT_ENABLE();

    os_init(main_loop_callback, main_idle_callback);

    /* user task init */
    os_task_init(&task_main, task_mainEntry, NULL);
    os_task_init(&task_key, task_keyEntry, NULL);
    os_task_init(&task_led, task_ledEntry, NULL);

    os_start();

    return 0;
}



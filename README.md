# nanoOS_event

nanoOS_event is a task scheduling framework based on event driven, and includes timer related funcation.

## file directory
* app
    * main.c/.h
* bsp
    * bsp.c/.h
* lib
    * *.a/.lib
* nanoos
    * os_api.h
    * os_cfg.h
    * os_core.c
    * os_timer.c
    * os_port.c


## event
### event type
    1. OS_EVT_POLL
    2. OS_EVT_INIT
    3. OS_EVT_EXIT
    4. USER_EVT_TYPE
### event release
    1. os_event_emit() --> synchronous event
    2. os_event_post() --> asynchronous event


## api


## port
### file
    1. os_cfg.h
    2. os_port.c
### type
    1. os_tick
### function
    1. OS_INT_DISABLE()
    2. OS_INT_ENABLE()
    3. os_clock_init()
    4. os_tick_get()


## example

```c
int main(void)
{
    OS_INT_DISABLE();

    bsp_init();
    os_clock_init();

    OS_INT_ENABLE();

    os_init(main_loop_callback, main_idle_callback);

    os_task_init(&task_main, task_mainEntry, NULL);

    os_start();

    return 0;
}
```



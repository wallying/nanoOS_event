# nanoOS_event

nanoOS_event is a task scheduling framework based on event driven, and includes timer related funcation.


## event

### event type
    1. OS_EVT_POLL
    2. OS_EVT_INIT
    3. OS_EVT_EXIT
    4. USER_EVT_TYPE
### event release
    1. os_event_emit() --> synchronous event
    2. os_event_post() --> asynchronous event


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



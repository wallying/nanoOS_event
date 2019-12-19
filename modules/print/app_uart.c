/**
 * file:    app_uart.c
 * author:  wallying@foxmail.com
 * date:    2019-12-19
 **/


#include "lib_print.h"
#include "bsp_uart.h"


void app_uartPrintf(const char *fmt, ...)
{
    os_u8 buf[128] = {0x00};

    va_list arg;
    va_start(arg, fmt);
    os_u16 len = print_vsnprintf((char*)buf, sizeof(buf), fmt, arg);
    va_end(arg);

    bsp_uartPrint(buf, len);
}





/**
 * file:    app_uart.h
 * author:  wallying@foxmail.com
 * date:    2019-12-19
 **/


#ifndef __APP_UART_H__
#define __APP_UART_H__


#include "os_api.h"
#include "print/bsp_uart.h"


void app_uartPrintf(const char *fmt, ...);


#endif /* __APP_UART_H__ */


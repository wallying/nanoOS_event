/**
 * file:    bsp_uart.h
 * author:  wallying@foxmail.com
 * date:    2019-12-19
 **/


#ifndef __BSP_UART_H__
#define __BSP_UART_H__



#include "os_api.h"


void bsp_uartInit(void);
void bsp_uartPrint(os_u8* data, os_u16 len);


#endif /* __BSP_UART_H__ */



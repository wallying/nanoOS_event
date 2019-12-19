/**
 * file:    bsp.h
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#ifndef __BSP_H__
#define __BSP_H__



#include "os_api.h"
#include "print/bsp_uart.h"
#include "key/bsp_key.h"
#include "led/bsp_led.h"


void bsp_mcuInit(void);
void bsp_init(void);


#endif /* __BSP_H__ */



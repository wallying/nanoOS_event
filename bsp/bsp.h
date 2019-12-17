/**
 * file:    bsp.h
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#ifndef __BSP_H__
#define __BSP_H__



#include "os_api.h"
#include "bsp_uart.h"
#include "mod_key/bsp_key.h"
#include "mod_led/bsp_led.h"


void bsp_mcuInit(void);
void bsp_init(void);


#endif /* __BSP_H__ */



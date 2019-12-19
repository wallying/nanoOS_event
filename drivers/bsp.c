/**
 * file:    bsp.c
 * author:  wallying@foxmail.com
 * date:    2019-11-27
 **/


#include "bsp.h"


void bsp_mcuInit(void)
{

}


void bsp_init(void)
{
    bsp_mcuInit();
    bsp_uartInit();
}


/**
 * file:    bsp_led.c
 * author:  wallying@foxmail.com
 * date:    2019-12-18
 **/


#include "bsp_led.h"


void bsp_ledInit(void)
{
	for (os_u8 i = 0; i < LED_NUM; i++)
	{
//		gpio_set_func(bspLedPins[i], AS_GPIO);
//		gpio_set_input_en(bspLedPins[i], 0);
//		gpio_set_output_en(bspLedPins[i], 0);
//		gpio_setup_up_down_resistor(bspLedPins[i], PM_PIN_PULLUP_10K);
	}
}

void bsp_ledCtrl(ledIdx_e led, ledCmd_e cmd)
{
    if (cmd == LED_OFF) {
//    	gpio_set_output_en(bspLedPins[led], 0);
//    	gpio_write(bspLedPins[led], 1);
    } else if (cmd == LED_ON) {
//    	gpio_set_output_en(bspLedPins[led], 1);
//    	gpio_write(bspLedPins[led], 0);
    } else if (cmd == LED_TOGGLE) {

    }
}

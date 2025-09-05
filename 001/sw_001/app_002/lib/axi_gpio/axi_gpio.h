
#pragma once
#ifndef AXI_GPIO_H_
#define AXI_GPIO_H_

#include "xparameters.h"
#include "xgpio.h"

#define gpio_key_channel 1
#define gpio_led_channel 2

void axi_gpio_init();
u16 get_axi_gpio_key_status();
void set_axi_gpio_led(u8 led_ctrl);


#endif
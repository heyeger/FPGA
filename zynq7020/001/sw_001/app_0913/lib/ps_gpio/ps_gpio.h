#pragma once

#ifndef PS_GPIO_H_
#define PS_GPIO_H_


#include "xparameters_ps.h"
#include "xgpiops.h"
#include "scu_gic.h"

#define ps_key 47
#define ps_led 7

void Ps_Gpio_Init();
//void set_ps_led(u8 led);
//u8 get_ps_key_status();

extern XGpioPs ps_gpio;

void Ps_Gpio_Intc_Init(Xil_InterruptHandler Handler);
u32 User_Define_GpioPs_ReadPin(XGpioPs *InstancePtr,u8 Pin);

#endif

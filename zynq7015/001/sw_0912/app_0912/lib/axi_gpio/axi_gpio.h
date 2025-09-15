#pragma once

#ifndef AXI_GPIO_H_
#define AXI_GPIO_H_


#include "scu_gic.h"
#include "xgpio.h"
#include "xparameters.h"

#define pl_key_channel 2
#define pl_led_channel 1


void Axi_Gpio_Init();

void Axi_Gpio_Intc_Init(//XGpio *gpio_inst,
                        //u16 Int_Id, 
                        //u32 Mask,
                        Xil_InterruptHandler Handler);

extern XGpio axi_gpio_pl;

#endif
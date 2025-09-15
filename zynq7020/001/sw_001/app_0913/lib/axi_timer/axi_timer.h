
#pragma once

#ifndef AXI_TIMER_H_
#define AXI_TIMER_H 


#include "scu_gic.h"
#include "xgpio.h"
#include <xtmrctr.h>
#include "xparameters.h"

#define AXI_TIMER_CNT0 1
#define AXI_TIMER_CNT1 2


extern XTmrCtr Axi_Timer_Inst0;

void Axi_Timer_Init(u8 TmrCtrNumber,u32 Time_Interval_Us, Xil_InterruptHandler Handler);
	
//void Axi_Timer_Init();
u32 Counter_Cal(u32 Clock_Freq_Hz,u32 Time_Interva);

//void axi_gpio_init();

//void axi_gpio_intc_init(//XGpio *gpio_inst,
                        //u16 Int_Id, 
                        //u32 Mask,
                        //Xil_InterruptHandler Handler);

//extern XGpio axi_gpio_pl;

#endif

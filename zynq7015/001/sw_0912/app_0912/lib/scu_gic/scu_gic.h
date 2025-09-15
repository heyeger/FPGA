#pragma once

#ifndef SCU_GIC_H_
#define SCU_GIC_H_

//#include "include_all.h"
#include "xscugic.h"
#include "xparameters.h"
#include "xil_exception.h"

#define High_Level_Sensitive  0x01
#define Rising_Edge_Sensitive 0x03

#define SPI_INTERRUPT_BASE_IRQID 32


int ScuGic_Init();
void Set_ScuGic_Link(u16 Int_Id,
                    u8 Priority,
                    u8 Trigger,
                    Xil_InterruptHandler Handler,
                    void *CallBackRef);


extern XScuGic scugic_inst;





#endif
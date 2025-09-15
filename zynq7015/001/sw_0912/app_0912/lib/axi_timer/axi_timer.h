
#pragma  once

#include <xil_types.h>
#ifndef AXI_TIMER_H_
#define AXI_TIMER_H_

//#include <stdio.h>
//#include <xuartps.h>
#include <xparameters_ps.h>
#include <xparameters.h>
#include <xtmrctr.h>

#include "scu_gic.h"

#include "isr_handler.h"

#define AXI_TIMER_CNT0 0U
#define AXI_TIMER_CNT1 1U

typedef struct {
    union {
        u32 Reg_Value;
        struct {
            u32 MDT0 : 1;
            u32 UDT0 : 1;
            u32 GENT0: 1;
            u32 CAPT0: 1;
            u32 ARHT0: 1;
            u32 LOAD0: 1;
            u32 ENIT0: 1;
            u32 ENT0 : 1; 
            u32 T0INT: 1;
            u32 PWMA0: 1;
            u32 ENALL: 1;
            u32 CASC : 1;
            u32 RSVD :20;   
        };
    }TSCR0;

    struct{
        u32 Reg_Value;
    }TLR0;

    struct{
        u32 Reg_Value;
    }TCR0;

}AXI_Timer_Reg_Type;

void AXI_Timer_Reg_Init(AXI_Timer_Reg_Type* Axi_Timer_Reg_Ptr,u8 TmrCtrNumber,u32 Cnt_Val);
void AXI_Timer_Reg_Intc_Clean(AXI_Timer_Reg_Type* Axi_Timer_Reg_Ptr,u8 TmrCtrNumber);

u32 Us2Counter_Cal(u32 Clock_Freq,u32 Interval_Us);
void Axi_Timer_Init(u8 TmrCtrNumber,u32 Interval_Us,Xil_InterruptHandler Handler);

extern XTmrCtr Axi_Timer_Inst;
extern AXI_Timer_Reg_Type Axi_Timer0_Reg;

#endif

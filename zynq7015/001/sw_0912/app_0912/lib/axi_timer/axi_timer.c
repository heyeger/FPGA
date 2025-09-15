
#include "axi_timer.h"
#include "scu_gic.h"
//#include <xil_types.h>
//#include "scu_gic.h"
//#include "scu_gic.h"
//#include <xtmrctr.h>

AXI_Timer_Reg_Type Axi_Timer0_Reg;
XTmrCtr Axi_Timer_Inst;

void Axi_Timer_Init(u8 TmrCtrNumber,u32 Interval_Us,Xil_InterruptHandler Handler){
    XTmrCtr_Config *XTmrCtr_Config_Ptr = XTmrCtr_LookupConfig(XPAR_XTMRCTR_0_BASEADDR);
    XTmrCtr_CfgInitialize(&Axi_Timer_Inst, XTmrCtr_Config_Ptr,XTmrCtr_Config_Ptr->BaseAddress);

    //XTmrCtr_SetOptions(&Axi_Timer_Inst,TmrCtrNumber,XTC_DOWN_COUNT_OPTION|XTC_INT_MODE_OPTION|XTC_AUTO_RELOAD_OPTION);
    //AXI_Timer_Reg_Init(&Axi_Timer0_Reg);
    //XTmrCtr_SetResetValue(&Axi_Timer_Inst,TmrCtrNumber,Us2Counter_Cal(XTmrCtr_Config_Ptr->SysClockFreqHz,Interval_Us));


    Set_ScuGic_Link(SPI_INTERRUPT_BASE_IRQID+XPAR_FABRIC_AXI_TIMER_0_INTR, // warning: IRQ_ID = SPI_BASE_ID + XPAR_FABRIC_...
                    0XB0,
                    High_Level_Sensitive, 
                    Handler, 
                    (void *)(&Axi_Timer_Inst));

    AXI_Timer_Reg_Init(&Axi_Timer0_Reg,TmrCtrNumber,Us2Counter_Cal(XTmrCtr_Config_Ptr->SysClockFreqHz,Interval_Us));


}

u32 Us2Counter_Cal(u32 Clock_Freq,u32 Interval_Us){
    return (u32)(Clock_Freq * ((float)Interval_Us/(1e6)));
}

void AXI_Timer_Reg_Init(AXI_Timer_Reg_Type* Axi_Timer_Reg_Ptr,u8 TmrCtrNumber,u32 Cnt_Val) {
    Axi_Timer_Reg_Ptr->TSCR0.Reg_Value=0;
    Axi_Timer_Reg_Ptr->TLR0.Reg_Value = Cnt_Val-1;
    Axi_Timer_Reg_Ptr->TCR0.Reg_Value = 0;
    
    Axi_Timer_Reg_Ptr->TSCR0.LOAD0 = 1;
    XTmrCtr_WriteReg(Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCSR_OFFSET, Axi_Timer_Reg_Ptr->TLR0.Reg_Value);
    Axi_Timer_Reg_Ptr->TSCR0.LOAD0 = 0;

    Axi_Timer_Reg_Ptr->TSCR0.ENIT0 = 1;
    Axi_Timer_Reg_Ptr->TSCR0.ARHT0 = 1;
    Axi_Timer_Reg_Ptr->TSCR0.UDT0  = 1;
    XTmrCtr_WriteReg(Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCSR_OFFSET, Axi_Timer_Reg_Ptr->TSCR0.Reg_Value);
    Axi_Timer_Reg_Ptr->TSCR0.ENT0  = 1;
    XTmrCtr_WriteReg(Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCSR_OFFSET, Axi_Timer_Reg_Ptr->TSCR0.Reg_Value);
    //Axi_Timer_Reg_Ptr->TSCR0.ENALL = 1;

	//XTmrCtr_WriteReg(Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TLR_OFFSET , Axi_Timer_Reg_Ptr->TLR0.Reg_Value );
    //XTmrCtr_WriteReg(Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCR_OFFSET , Axi_Timer_Reg_Ptr->TCR0.Reg_Value );
    //XTmrCtr_WriteReg(Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCSR_OFFSET, Axi_Timer_Reg_Ptr->TSCR0.Reg_Value);

    Axi_Timer_Reg_Ptr->TLR0.Reg_Value =XTmrCtr_ReadReg( Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TLR_OFFSET);
    Axi_Timer_Reg_Ptr->TCR0.Reg_Value =XTmrCtr_ReadReg( Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCR_OFFSET);
    Axi_Timer_Reg_Ptr->TSCR0.Reg_Value=XTmrCtr_ReadReg( Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCSR_OFFSET);

}

void AXI_Timer_Reg_Intc_Clean(AXI_Timer_Reg_Type* Axi_Timer_Reg_Ptr,u8 TmrCtrNumber) {

    Axi_Timer_Reg_Ptr->TSCR0.Reg_Value=XTmrCtr_ReadReg( Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCSR_OFFSET);
    if(Axi_Timer_Reg_Ptr->TSCR0.T0INT)
    {
        //Axi_Timer_Reg_Ptr->TSCR0.T0INT = 0;
        XTmrCtr_WriteReg( Axi_Timer_Inst.BaseAddress,TmrCtrNumber,XTC_TCSR_OFFSET, Axi_Timer_Reg_Ptr->TSCR0.Reg_Value);
    }

}
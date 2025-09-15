
#include "axi_timer.h"

XTmrCtr Axi_Timer_Inst0;

void Axi_Timer_Init(u8 TmrCtrNumber,u32 Time_Interval_Us, Xil_InterruptHandler Handler){
	
	XTmrCtr_Config *XTmrCtr_Config_Ptr = XTmrCtr_LookupConfig(XPAR_AXI_TIMER_0_BASEADDR);
	XTmrCtr_CfgInitialize(&Axi_Timer_Inst0,XTmrCtr_Config_Ptr,XTmrCtr_Config_Ptr->BaseAddress);
	
	Set_ScuGic_Link(XPAR_FABRIC_XTMRCTR_0_INTR+SPI_INTERRUPT_BASE_IRQID,
                    0xA0,
                    High_Level_Sensitive ,
                    Handler,
                   (void*) &Axi_Timer_Inst0);
	XTmrCtr_SetOptions(&Axi_Timer_Inst0,TmrCtrNumber,XTC_DOWN_COUNT_OPTION|XTC_INT_MODE_OPTION|XTC_AUTO_RELOAD_OPTION );
	XTmrCtr_SetResetValue(&Axi_Timer_Inst0,TmrCtrNumber,Counter_Cal(XTmrCtr_Config_Ptr->SysClockFreqHz,Time_Interval_Us));
	XTmrCtr_Start(&Axi_Timer_Inst0,TmrCtrNumber);

}

u32 Counter_Cal(u32 Clock_Freq_Hz,u32 Time_Interval_Us){
	return (u32)(Clock_Freq_Hz * (float)Time_Interval_Us/1e6);
}

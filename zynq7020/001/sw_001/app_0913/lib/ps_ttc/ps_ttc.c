#include "ps_ttc.h"
//#include <xttcps.h>

XTtcPs ttc0_timer0_inst,ttc0_timer1_inst;

void Ttc_Init(XTtcPs *ttc_inst_ptr,u32 ttc_baseaddr ,u16 Intr_ID,u32 interval_time_us,Xil_InterruptHandler handle)
{
    
    u8  pre_scaler=0;
    XInterval interval=0;

    XTtcPs_Config *ttc_config_ptr;
    ttc_config_ptr=XTtcPs_LookupConfig(ttc_baseaddr);
    XTtcPs_CfgInitialize(ttc_inst_ptr,
         ttc_config_ptr, ttc_config_ptr->BaseAddress);

    XTtcPs_SetOptions(ttc_inst_ptr, XTTCPS_OPTION_INTERVAL_MODE|XTTCPS_OPTION_WAVE_DISABLE);

    u32 freq = 1e6/interval_time_us;
    XTtcPs_CalcIntervalFromFreq(ttc_inst_ptr,freq,&interval,&pre_scaler);


    XTtcPs_SetInterval(ttc_inst_ptr,interval);
    XTtcPs_SetPrescaler(ttc_inst_ptr, pre_scaler);

    //pre_scaler=XTtcPs_GetPrescaler(ttc_inst_ptr);
    //interval=XTtcPs_GetInterval(ttc_inst_ptr);
    
    Set_ScuGic_Link(Intr_ID, 0XB0, High_Level_Sensitive, handle, (void*)(ttc_inst_ptr));
    XTtcPs_EnableInterrupts(ttc_inst_ptr,XTTCPS_IXR_INTERVAL_MASK);
}


//XTtcPs_Start(ttc_inst);
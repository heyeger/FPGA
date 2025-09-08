#include "ps_ttc.h"
//#include <xttcps.h>

XTtcPs ttc_inst0;

void ttc_init(XTtcPs ttc_inst,u32 ttc_baseaddr ,u16 Intr_ID,u32 interval_time_us,Xil_InterruptHandler handle)
{
    u32 curr_interval_time_cnt;
    u32 ceil_quotient;
    u8  pre_scaler =0;
    XInterval interval;

    XTtcPs_Config *ttc_config_ptr;
    ttc_config_ptr=XTtcPs_LookupConfig(ttc_baseaddr);
    XTtcPs_CfgInitialize(&ttc_inst,
         ttc_config_ptr, ttc_config_ptr->BaseAddress);

    XTtcPs_SetOptions(&ttc_inst, XTTCPS_OPTION_INTERVAL_MODE|XTTCPS_OPTION_WAVE_DISABLE);

    
    curr_interval_time_cnt = ((float)ttc_inst.Config.InputClockHz/1e6)*interval_time_us-1;// get the counter when clock not divide.
    //prescaler is in [0,15] ,16 means no use. 
    if(curr_interval_time_cnt>XTTCPS_MAX_INTERVAL_COUNT) //if the counter overflow,calate the prescaler and divide the counter.
    {
        ceil_quotient = curr_interval_time_cnt/XTTCPS_MAX_INTERVAL_COUNT;
        if(curr_interval_time_cnt%XTTCPS_MAX_INTERVAL_COUNT)
        {
            ceil_quotient++;
        }
        while((2U<<pre_scaler)<ceil_quotient)
        {
            pre_scaler++;
        }
        curr_interval_time_cnt = curr_interval_time_cnt >>(pre_scaler+1);
        
    }
    else 
    {
        pre_scaler = XTTCPS_CLK_CNTRL_PS_DISABLE; //16U
    }

    interval = curr_interval_time_cnt;
    //XTtcPs_SetInterval(&ttc_init,curr_interval_time_cnt);
    XTtcPs_SetInterval(&ttc_inst,interval);
    XTtcPs_SetPrescaler(&ttc_inst, pre_scaler);
    
    set_scugic_link(Intr_ID, 0X80, High_Level_Sensitive, handle, (void*)(&ttc_inst));
    XTtcPs_EnableInterrupts(&ttc_inst,XTTCPS_IXR_INTERVAL_MASK);
}


//XTtcPs_Start(ttc_inst);
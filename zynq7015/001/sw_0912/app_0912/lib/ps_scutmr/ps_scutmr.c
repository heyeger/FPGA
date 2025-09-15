
#include "ps_scutmr.h"
//#include "scu_gic.h"
//#include <xscutimer.h>
//#include <xil_exception.h>
//#include <xscutimer.h>

XScuTimer scutimer_inst;

void Ps_ScuTmr_Init(u32 time_us)
{
    XScuTimer_Config *XScuTimer_Config_Ptr = XScuTimer_LookupConfig(XPAR_XSCUTIMER_0_BASEADDR);
    XScuTimer_CfgInitialize(&scutimer_inst,XScuTimer_Config_Ptr,XScuTimer_Config_Ptr->BaseAddr);
    
    u32 load_val = ((float)time_us*(1e-6) * XPAR_CPU_CORE_CLOCK_FREQ_HZ/2)-1;
    

    XScuTimer_LoadTimer(&scutimer_inst,load_val);
    XScuTimer_EnableAutoReload(&scutimer_inst);
    Set_ScuGic_Link(XPAR_PS7_SCUTIMER_0_INTR, 0xB0, Rising_Edge_Sensitive, (Xil_InterruptHandler)scu_timer_handle, (void*)&scutimer_inst);

    XScuTimer_EnableInterrupt(&scutimer_inst);
    XScuTimer_Start(&scutimer_inst);
    

}
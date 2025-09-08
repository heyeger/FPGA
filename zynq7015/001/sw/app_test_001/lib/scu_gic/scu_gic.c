
#include "scu_gic.h"

XScuGic scugic_inst;

int scugic_init()
{
    XScuGic_Config *scugic_cfg_ptr;
    scugic_cfg_ptr=XScuGic_LookupConfig(XPAR_XSCUGIC_0_BASEADDR);
    XScuGic_CfgInitialize(  &scugic_inst,
                            scugic_cfg_ptr,
							scugic_cfg_ptr->CpuBaseAddress);
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, 
                                (Xil_ExceptionHandler)XScuGic_InterruptHandler, 
                                &scugic_inst);
    Xil_ExceptionEnable();
    return XST_SUCCESS;
                            
}

void set_scugic_link(u16 Int_Id,
                    u8 Priority,
                    u8 Trigger,
                    Xil_InterruptHandler Handler,
                    void *CallBackRef)
{
    XScuGic_SetPriorityTriggerType( &scugic_inst,
                                    Int_Id, 
                                    Priority, 
                                    Trigger);
    XScuGic_Connect(&scugic_inst, 
                    Int_Id, 
                    Handler, 
                    CallBackRef);
    XScuGic_Enable(&scugic_inst, Int_Id);

}
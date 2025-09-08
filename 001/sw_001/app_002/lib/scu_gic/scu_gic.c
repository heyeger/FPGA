
#include "scu_gic.h"

XScuGic ScuGic;	
void ScuGic_Init()
{
	XScuGic_Config *IntcConfig;
	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	XScuGic_CfgInitialize(	&ScuGic, 
				IntcConfig,IntcConfig->CpuBaseAddress);

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,&ScuGic);
	Xil_ExceptionEnable();
}

void Set_ScuGic_Link(uint16_t IntrId, uint8_t Priority, uint8_t Trigger,Xil_InterruptHandler Handler, void *CallBackRef)
{
	XScuGic_SetPriorityTriggerType(&ScuGic, IntrId, Priority, Trigger);
	XScuGic_Connect(&ScuGic, IntrId,(Xil_ExceptionHandler)Handler,CallBackRef);
	XScuGic_Enable(&ScuGic, IntrId);
}

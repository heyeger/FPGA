
#include "ps_gpio.h"
//#include <xgpiops.h>
//#include "scu_gic.h"


XGpioPs ps_gpio;

void ps_gpio_init()
{
    XGpioPs_Config *ps_gpio_cfg_ptr;
    ps_gpio_cfg_ptr = XGpioPs_LookupConfig(XPS_GPIO_BASEADDR);
    XGpioPs_CfgInitialize(&ps_gpio, ps_gpio_cfg_ptr,
			   ps_gpio_cfg_ptr->BaseAddr);
    
    XGpioPs_SetDirectionPin(&ps_gpio, ps_key, 0x0);
//*               Bits with 0 are set to Input mode,
//*               bits with 1 are set to Output Mode.
    XGpioPs_SetDirectionPin(&ps_gpio, ps_led, 0x1);
    XGpioPs_SetOutputEnablePin(&ps_gpio, ps_led, 0x1);
    XGpioPs_WritePin(&ps_gpio, ps_led, 0x1);

}

void ps_gpio_intc_init(Xil_InterruptHandler Handler)
{
    set_scugic_link(XPAR_PS7_GPIO_0_INTR, // warning: IRQ_ID = SPI_BASE_ID + XPAR_FABRIC_...
                    0xA0,
                    Rising_Edge_Sensitive, 
                    Handler, 
                    (void *)(&ps_gpio));

    //XGpioPs_SetCallbackHandler(&ps_gpio, (void *)(&ps_gpio),Handler);

    XGpioPs_SetIntrTypePin(&ps_gpio, ps_key, XGPIOPS_IRQ_TYPE_EDGE_FALLING);
    XGpioPs_IntrEnablePin(  &ps_gpio,
                            ps_key);// 

}


/****************************************************************************/
/**
*
* Read data from the specified pin.
*
* @param	InstancePtr is a pointer to the XGpioPs instance.
* @param	Pin is the pin number to which the Data is to be written.
* 
*
* @return	None.
*
* @note		This function does read from the specified pin of
*		the specified GPIO bank. The previous state of other pins
*		is maintained.
*
*****************************************************************************/

u32 User_Define_GpioPs_ReadPin(XGpioPs *InstancePtr,u8 Pin)
{
    u32 RegOffset;
	//u32 Value;
	u8 Bank;
	u8 PinNumber;
	//u32 DataVar = Data;
	//Xil_AssertVoid(InstancePtr != NULL);
	//Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	//Xil_AssertVoid(Pin < InstancePtr->MaxPinNum);

	/* Get the Bank number and Pin number within the bank. */
#ifdef versal
	XGpioPs_GetBankPin(InstancePtr,(u8)Pin, &Bank, &PinNumber);
#else
	XGpioPs_GetBankPin((u8)Pin, &Bank, &PinNumber);
#endif

	if (PinNumber > 15U) {
		/* There are only 16 data bits in bit maskable register. */
		PinNumber -= (u8)16;
		RegOffset = XGPIOPS_DATA_MSW_OFFSET;
	} else {
		RegOffset = XGPIOPS_DATA_LSW_OFFSET;
	}

	/*
	 * Get the 32 bit value to be written to the Mask/Data register where
	 * the upper 16 bits is the mask and lower 16 bits is the data.
	 */
	//DataVar &= (u32)0x01;
	//Value = ~((u32)1 << (PinNumber + 16U)) & ((DataVar << PinNumber) | 0xFFFF0000U);
	return ((XGpioPs_ReadReg(InstancePtr->GpioConfig.BaseAddr,
			  ((u32)(Bank) * XGPIOPS_DATA_MASK_OFFSET) +
			  RegOffset))>>PinNumber)&0x1;

}

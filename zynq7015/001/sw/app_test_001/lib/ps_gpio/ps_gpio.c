
#include "ps_gpio.h"
#include "scu_gic.h"


XGpioPs ps_gpio;

void ps_gpio_int()
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
    XGpioPs_WritePin(&ps_gpio, ps_led, 0x0);

}

void ps_gpio_intc_init(XGpioPs_Handler Handler)
{
    set_scugic_link(XPAR_PS7_GPIO_0_INTR, // warning: IRQ_ID = SPI_BASE_ID + XPAR_FABRIC_...
                    0xA0,
                    Rising_Edge_Sensitive, 
                    (Xil_InterruptHandler)Handler, 
                    (void *)(&ps_gpio));

    XGpioPs_SetCallbackHandler(&ps_gpio, (void *)(&ps_gpio),Handler);

    XGpioPs_SetIntrTypePin(&ps_gpio, ps_key, XGPIOPS_IRQ_TYPE_EDGE_BOTH);
    XGpioPs_IntrEnablePin(  &ps_gpio,
                            ps_key);// 

}


//u8 get_ps_key_status()
//{
//    return XGpioPs_ReadPin(&ps_gpio, ps_key);
//}
//
//void set_ps_led(u8 led)
//{
//    XGpioPs_WritePin(&ps_gpio, ps_led, led);
//}

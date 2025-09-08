
#include "axi_gpio.h"
#include "scu_gic.h"
//#include <xgpio.h>
//#include <xgpio_l.h>
//#include <xil_printf.h>

XGpio axi_gpio_pl;

void axi_gpio_init()
{
    XGpio_Config *XGpio_Config_ptr;
    XGpio_Config_ptr = XGpio_LookupConfig(XPAR_XGPIO_0_BASEADDR);
    XGpio_CfgInitialize(&axi_gpio_pl, XGpio_Config_ptr,
			XGpio_Config_ptr->BaseAddress);

    //XGpio_WriteReg(axi_gpio_pl.BaseAddress, 0XC, 0x0);
    XGpio_SetDataDirection(&axi_gpio_pl, pl_led_channel, 0x0);        
    XGpio_SetDataDirection(&axi_gpio_pl, pl_key_channel, 0x1);
    
    XGpio_DiscreteWrite(&axi_gpio_pl, pl_led_channel, 0x2);
}

void axi_gpio_intc_init(Xil_InterruptHandler Handler)
{
    set_scugic_link(SPI_INTERRUPT_BASE_IRQID+XPAR_FABRIC_AXI_GPIO_0_INTR, // warning: IRQ_ID = SPI_BASE_ID + XPAR_FABRIC_...
                    0xA0,
                    High_Level_Sensitive, 
                    Handler, 
                    (void *)(&axi_gpio_pl));
    
    
    XGpio_InterruptDisable( &axi_gpio_pl,
                            0x3);
    XGpio_InterruptEnable(  &axi_gpio_pl,
                            pl_key_channel);// enable channel01 interrupt.
    
    XGpio_InterruptGlobalEnable(&axi_gpio_pl);

}

/*
u8 get_pl_key_status()
{
    return XGpio_DiscreteRead(&axi_gpio_pl,  1)>>1;
}

void set_pl_led(u8 led_status)
{
    XGpio_DiscreteWrite(&axi_gpio_pl, 1, led_status);
}
*/

#include "axi_gpio.h"

XGpio axi_gpio_inst;

void axi_gpio_init()
{
    XGpio_Config *Xaxi_gpio_cfg_ptr;
    Xaxi_gpio_cfg_ptr = XGpio_LookupConfig(XPAR_AXI_GPIO_0_BASEADDR);
    XGpio_CfgInitialize(&axi_gpio_inst, Xaxi_gpio_cfg_ptr,
			Xaxi_gpio_cfg_ptr->BaseAddress);
    //XGpio_SetDataDirection(&axi_gpio_inst, gpio_key_channel,0x3ff);
    //XGpio_SetDataDirection(&axi_gpio_inst, gpio_led_channel,0x00);
    XGpio_DiscreteWrite(&axi_gpio_inst, gpio_led_channel,
			0x00);
}

u16 get_axi_gpio_key_status()
{
    return XGpio_DiscreteRead(&axi_gpio_inst, gpio_key_channel);
}

void set_axi_gpio_led(u8 led_ctrl)
{   
    XGpio_DiscreteWrite(&axi_gpio_inst, gpio_led_channel,
			led_ctrl);
}
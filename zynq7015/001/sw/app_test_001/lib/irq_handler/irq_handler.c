
#include "irq_handler.h"
//#include "axi_gpio.h"

volatile u8 inter_flag;

void axi_gpio_irq_handler()
{
	u32 key_int_state;
    key_int_state = XGpio_InterruptGetStatus(&axi_gpio_pl);
	//u8 enable_sts = XGpio_InterruptGetEnabled(&axi_gpio_pl);
	if(key_int_state&0x2)
	{
		//u8 axi_led_status = XGpio_DiscreteRead(&axi_gpio_pl,1);
    	//XGpio_DiscreteWrite(&axi_gpio_pl, 1, 0x3&(~axi_led_status));
		inter_flag = PL_GPIO_INTR_FLAG;
		XTtcPs_Start(&ttc_inst);
		XGpio_InterruptClear(&axi_gpio_pl, pl_key_channel);//clear channel01 interrupt.

	}
}


void ps_gpio_irq_handler()
{
	u32 pskey_int_state;
    pskey_int_state = XGpioPs_IntrGetStatusPin(&ps_gpio,ps_key);
	//u8 enable_sts = XGpio_InterruptGetEnabled(&axi_gpio_pl);
	if(pskey_int_state)
	{
		//u8 ps_led_status = XGpioPs_ReadPin(&ps_gpio, ps_key);
		//XGpioPs_WritePin(&ps_gpio, ps_led, ~ps_led_status );
		inter_flag = PS_GPIO_INTR_FLAG;
		XTtcPs_Start(&ttc_inst);
		XGpioPs_IntrClearPin(&ps_gpio, ps_key);

	}
}


void ttc_irq_handler()
{
	XTtcPs_Stop(&ttc_inst);
	XTtcPs_ResetCounterValue(&ttc_inst);
	if(inter_flag == PL_GPIO_INTR_FLAG)
	{	
		u8 axi_led_status = XGpio_DiscreteRead(&axi_gpio_pl,1);
    	XGpio_DiscreteWrite(&axi_gpio_pl, 1, 0x3&(~axi_led_status));
	}
	else if(inter_flag == PS_GPIO_INTR_FLAG)
	{
		u8 ps_led_status = XGpioPs_ReadPin(&ps_gpio, ps_key);
		XGpioPs_WritePin(&ps_gpio, ps_led, ~ps_led_status );
	}
	inter_flag = CLEARIO_INTR_FLAG;

	u32 ttc_intr_sts = XTtcPs_GetInterruptStatus(&ttc_inst);
	XTtcPs_ClearInterruptStatus(&ttc_inst,ttc_intr_sts);
}

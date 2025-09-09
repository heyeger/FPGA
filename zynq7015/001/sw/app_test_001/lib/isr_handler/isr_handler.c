
#include "isr_handler.h"
#include "ps_uart.h"
//#include <xil_types.h>
//#include "ps_uart.h"
//#include "axi_gpio.h"

volatile u8 inter_flag;
char* tx_buffer = "";

void axi_gpio_irq_handler()
{
	u32 key_int_state;
    key_int_state = XGpio_InterruptGetStatus(&axi_gpio_pl);
	//u8 enable_sts = XGpio_InterruptGetEnabled(&axi_gpio_pl);
	if(key_int_state&0x2)
	{

		inter_flag = PL_GPIO_INTR_FLAG;
		XTtcPs_Start(&ttc0_timer0_inst);

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

		inter_flag = PS_GPIO_INTR_FLAG;
		XTtcPs_Start(&ttc0_timer0_inst);
		XGpioPs_IntrClearPin(&ps_gpio, ps_key);

	}
}


void ttc0_timer0_irq_handler()
{
	XTtcPs_Stop(&ttc0_timer0_inst);
	XTtcPs_ResetCounterValue(&ttc0_timer0_inst);
	if(inter_flag == PL_GPIO_INTR_FLAG)
	{	
		u8 axi_led_status = XGpio_DiscreteRead(&axi_gpio_pl,1);
    	XGpio_DiscreteWrite(&axi_gpio_pl, 1, 0x3&(~axi_led_status));
		log_upload("PL_KEY!");
	}
	else if(inter_flag == PS_GPIO_INTR_FLAG)
	{
		u8 ps_led_status = XGpioPs_ReadPin(&ps_gpio, ps_key);
		XGpioPs_WritePin(&ps_gpio, ps_led, ~ps_led_status );
		log_upload("PS_KEY!");
	}
	inter_flag = CLEARIO_INTR_FLAG;

	u32 ttc_intr_sts = XTtcPs_GetInterruptStatus(&ttc0_timer0_inst);
	XTtcPs_ClearInterruptStatus(&ttc0_timer0_inst,ttc_intr_sts);
}

void ttc0_timer1_irq_handler()
{
	uart_tx(tx_buffer);
}

void uart_log_irq_handler()
{
	//uart_tx();
}
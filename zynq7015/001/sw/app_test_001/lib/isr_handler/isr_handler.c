
#include "isr_handler.h"


volatile u8 inter_flag;

//u16 pl_times=0;
//u16 ps_times=0;

XUartPsBuffer upload_buffer;

void axi_gpio_irq_handler()
{
	u32 key_int_state;
    //key_int_state = XGpio_InterruptGetEnabled(&axi_gpio_pl);
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
	u32 led_status=0;
	static u16 pl_times=0;
	static u16 ps_times=0;
	XTtcPs_Stop(&ttc0_timer0_inst);
	XTtcPs_ResetCounterValue(&ttc0_timer0_inst);
	if(inter_flag == PL_GPIO_INTR_FLAG)
	{	

		u32 pl_key_status = XGpio_DiscreteRead(&axi_gpio_pl,pl_key_channel);
		// only rising edge will operate;
		if(0x1&(~pl_key_status))
		{
			led_status = XGpio_DiscreteRead(&axi_gpio_pl,pl_led_channel);
    		XGpio_DiscreteWrite(&axi_gpio_pl, pl_led_channel, 0x3&(~led_status));
			log_upload("CNT:%02d -- PL_KEY!\r\n",pl_times++);
		}


	}
	else if(inter_flag == PS_GPIO_INTR_FLAG)
	{

		led_status = User_Define_GpioPs_ReadPin(&ps_gpio, ps_led);
		XGpioPs_WritePin(&ps_gpio, ps_led, 0x1&(~led_status) );
		//led_status = XGpioPs_ReadPin(&ps_gpio, ps_led);
		log_upload("CNT:%02d -- PS_KEY!\r\n",ps_times++);
	}
	else {
		return;
	}
	inter_flag = CLEARIO_INTR_FLAG;

	u32 ttc_intr_sts = XTtcPs_GetInterruptStatus(&ttc0_timer0_inst);
	XTtcPs_ClearInterruptStatus(&ttc0_timer0_inst,ttc_intr_sts);
}

void ttc0_timer1_irq_handler()
{
	uart_tx(tx_log_text);
}

void uart_log_irq_handler()
{
	//uart_tx();
}

void scu_timer_handle()
{
	static u8 hour = 9;
	static u8 min  = 43;
	static u8 sec  = 35;

	if(sec==59)
	{
		sec = 0;
		if(min==59){
			min=0;
			if(hour==23){
				hour = 0;
			}else {
				hour++;
			}
		}else{
			min++;
		}
	}else {
		sec++;
	}
	log_upload("CURRENT_TIME--%02d:%02d:%02d\r\n",hour,min,sec);

}

#include "ps_uart.h"
//#include "ps_ttc.h"
//#include "scu_gic.h"

char *tx_buffer;

XUartPs psuart_inst;

void ps_uart_init(Xil_InterruptHandler Handler)
{
    XUartPs_Config *ps_uart_config_ptr = XUartPs_LookupConfig(XPS_UART0_BASEADDR);
    XUartPs_CfgInitialize(&psuart_inst,ps_uart_config_ptr,ps_uart_config_ptr->BaseAddress);
    XUartPs_SetBaudRate(&psuart_inst,PS_UART_BAUDRATE);
    
    set_scugic_link(XPAR_XUARTPS_0_INTR, 0xA0, High_Level_Sensitive, Handler, &psuart_inst);

    ttc_init(ttc_inst1, PS_TTC0_TIMER1_BASEADDR, XPS_TTC0_1_INT_ID, 10000, ttc0_timer1_irq_handler);
    XTtcPs_Start(&ttc_inst1); 

}


void uart_tx()
{
    psuart_inst.SendBuffer.NextBytePtr=(u8*)tx_buffer;
    
}
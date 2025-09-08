
#include "ps_uart.h"
#include "scu_gic.h"

XUartPs psuart_inst;

void ps_uart_init(Xil_InterruptHandler Handler)
{
    XUartPs_Config *ps_uart_config_ptr = XUartPs_LookupConfig(XPS_UART0_BASEADDR);
    XUartPs_CfgInitialize(&psuart_inst,ps_uart_config_ptr,ps_uart_config_ptr->BaseAddress);
    XUartPs_SetBaudRate(&psuart_inst,PS_UART_BAUDRATE);
    
    set_scugic_link(XPAR_XUARTPS_0_INTR, 0xA0, High_Level_Sensitive, Handler, &psuart_inst);

}

#include "ps_uart.h"
//#include <string.h>
//#include <xuartps.h>
//#include <xuartps_hw.h>
//#include "ps_ttc.h"
//#include "scu_gic.h"

//volatile char* tx_buffer = "";

XUartPs psuart_inst;

void ps_uart_init(Xil_InterruptHandler Handler)
{
    XUartPs_Config *ps_uart_config_ptr = XUartPs_LookupConfig(XPAR_XUARTPS_0_BASEADDR);
    XUartPs_CfgInitialize(&psuart_inst,ps_uart_config_ptr,ps_uart_config_ptr->BaseAddress);
    XUartPs_SetBaudRate(&psuart_inst,PS_UART_BAUDRATE);
    
    set_scugic_link(XPAR_XUARTPS_0_INTR, 0xA0, High_Level_Sensitive, Handler, &psuart_inst);

    ttc_init(&ttc0_timer1_inst, PS_TTC0_TIMER1_BASEADDR, XPS_TTC0_1_INT_ID, 10000, ttc0_timer1_irq_handler);
    XTtcPs_Start(&ttc0_timer1_inst); 

}


void uart_tx(char* tx_data)
{   
    
    //u32 tx_send_bytes;
    // disable tx_empty_interrupt;
    //XUartPs_SetInterruptMask(&psuart_inst, XUARTPS_IXR_MASK&(~XUARTPS_IXR_TXEMPTY));
    //psuart_inst.SendBuffer.NextBytePtr=(u8*)tx_buffer;
    //psuart_inst.SendBuffer.RequestedBytes=strlen(tx_buffer);
    //psuart_inst.SendBuffer.RemainingBytes=strlen(tx_buffer);
    u16 string_len = strlen(tx_data);
    if (string_len)
    {
        XUartPs_Send(&psuart_inst, (u8 *)tx_data, string_len);
        tx_data = "";
 
    }
}
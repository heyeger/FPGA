
#include "ps_uart.h"


//volatile char* tx_log_text = "";
char* tx_log_text = "";
volatile u16 tx_len;

XUartPs psuart_inst;

void Ps_Uart_Init(Xil_InterruptHandler Handler)
{
    XUartPs_Config *ps_uart_config_ptr = XUartPs_LookupConfig(XPAR_XUARTPS_0_BASEADDR);
    XUartPs_CfgInitialize(&psuart_inst,ps_uart_config_ptr,ps_uart_config_ptr->BaseAddress);
    XUartPs_SetBaudRate(&psuart_inst,PS_UART_BAUDRATE);
    
    Set_ScuGic_Link(XPAR_XUARTPS_0_INTR, 0xB8, High_Level_Sensitive, Handler, &psuart_inst);

    //PS_TTC0_TIMER1_BASEADDR define in xparameter.h not in xparameter_ps.h
    Ttc_Init(&ttc0_timer1_inst, PS_TTC0_TIMER1_BASEADDR, XPS_TTC0_1_INT_ID, 10000, ttc0_timer1_irq_handler);
    XTtcPs_Start(&ttc0_timer1_inst); 

}


void Uart_Tx(char* tx_data)
{   
    
    //u32 tx_send_bytes;
    // disable tx_empty_interrupt;
    //XUartPs_SetInterruptMask(&psuart_inst, XUARTPS_IXR_MASK&(~XUARTPS_IXR_TXEMPTY));
    //psuart_inst.SendBuffer.NextBytePtr=(u8*)tx_log_text;
    //psuart_inst.SendBuffer.RequestedBytes=strlen(tx_log_text);
    //psuart_inst.SendBuffer.RemainingBytes=strlen(tx_log_text);
    //u16 string_len = strlen(tx_data);
    if (tx_len)
    {
        XUartPs_Send(&psuart_inst, (u8 *)tx_data, tx_len);
        tx_len = 0;
 
    }
}
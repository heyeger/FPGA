
#pragma  once

#ifndef PS_UART_H_
#define PS_UART_H_

#include <stdio.h>
#include <xuartps.h>
#include <xparameters_ps.h>

#include "scu_gic.h"
#include "ps_ttc.h"
#include "isr_handler.h"

#define PS_UART_BAUDRATE 115200

#define log_upload(x, ...) do{ \
                            sprintf(tx_buffer,x,##__VA_ARGS__);\
                            }while(0)

extern XUartPs psuart_inst;
//extern volatile char *tx_buffer;

void ps_uart_init(Xil_InterruptHandler Handler);
void uart_tx();


//#define func(x,...) do{ \
//                   	sprintf(x,##__VA_ARGS__);
//                      }while(0)
//
//https://c.biancheng.net/view/zlb1viy.html
//https://blog.csdn.net/dldw8816/article/details/86519575
//https://blog.csdn.net/m0_37989557/article/details/149370203?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-149370203-blog-86519575.235^v43^pc_blog_bottom_relevance_base7&spm=1001.2101.3001.4242.1&utm_relevant_index=2

#endif

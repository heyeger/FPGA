#pragma once

#ifndef ISR_HANDLER_H_
#define ISR_HANDLER_H_

//ISR: interrupt service routine 

#include "axi_gpio.h"
#include "ps_gpio.h"
#include "xgpio.h"
//#include "xparameters_ps.h"

#include "ps_ttc.h"
#include "ps_uart.h"

#define CLEARIO_INTR_FLAG 0U
#define PL_GPIO_INTR_FLAG 1U
#define PS_GPIO_INTR_FLAG 2U


void Axi_Gpio_IrqHandler();
void Ps_Gpio_IrqHandler();
void Ttc0_Timer0_IrqHandler();
void Ttc0_Timer1_IrqHandler();
void Uart_Log_IrqHandler();
void Scu_Timer_IrqHandler();

void Axi_Timer_IrqHandler();
#endif

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


void axi_gpio_irq_handler();
void ps_gpio_irq_handler();
void ttc0_timer0_irq_handler();
void ttc0_timer1_irq_handler();
void uart_log_irq_handler();
void scu_timer_handle();

#endif

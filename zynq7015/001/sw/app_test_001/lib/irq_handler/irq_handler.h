#pragma once

#ifndef IRQ_HANDLER_H_
#define IRQ_HANDLER_H_

#include "axi_gpio.h"
#include "ps_gpio.h"
#include "xgpio.h"
#include "xparameters.h"

#include "ps_ttc.h"

#define CLEARIO_INTR_FLAG 0U
#define PL_GPIO_INTR_FLAG 1U
#define PS_GPIO_INTR_FLAG 2U


void axi_gpio_irq_handler();
void ps_gpio_irq_handler();
void ttc_irq_handler();


#endif

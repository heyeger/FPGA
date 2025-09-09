#pragma once

#ifndef PS_TTC_H_
#define PS_TTC_H_

//#include "include_all.h"
#include <xttcps.h>
#include <xparameters_ps.h>
#include "scu_gic.h"

#define PS_TIMER1_BASEADDR_OFFSET 4
#define PS_TIMER2_BASEADDR_OFFSET 8

#define PS_TTC0_TIMER0_BASEADDR XPS_TTC0_BASEADDR
#define PS_TTC0_TIMER1_BASEADDR XPS_TTC0_BASEADDR+PS_TIMER1_BASEADDR_OFFSET
#define PS_TTC0_TIMER2_BASEADDR XPS_TTC0_BASEADDR+PS_TIMER2_BASEADDR_OFFSET

#define PS_TTC1_TIMER0_BASEADDR XPS_TTC0_BASEADDR
#define PS_TTC1_TIMER1_BASEADDR XPS_TTC0_BASEADDR+PS_TIMER1_BASEADDR_OFFSET
#define PS_TTC1_TIMER2_BASEADDR XPS_TTC0_BASEADDR+PS_TIMER2_BASEADDR_OFFSET


void ttc_init(XTtcPs *ttc_inst_ptr,u32 ttc_baseaddr ,u16 Intr_ID,u32 interval_time_us,Xil_InterruptHandler handle);

extern XTtcPs ttc0_timer0_inst,ttc0_timer1_inst;


#endif
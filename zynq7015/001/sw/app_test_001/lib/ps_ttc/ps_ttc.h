#pragma once

#ifndef PS_TTC_H_
#define PS_TTC_H_

//#include "include_all.h"
#include <xttcps.h>
#include <xparameters_ps.h>
#include "scu_gic.h"

void ttc_init(XTtcPs ttc_inst,u32 ttc_baseaddr ,u16 Intr_ID,u32 interval_time_us,Xil_InterruptHandler handle);

extern XTtcPs ttc_inst0;


#endif
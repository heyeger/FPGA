
#pragma  once

#ifndef PS_SCUTMR_H_
#define PS_SCUTMR_H_

//#include <stdio.h>
//#include <xuartps.h>
#include <xparameters_ps.h>
#include <xparameters.h>
#include <xscutimer.h>

#include "scu_gic.h"

#include "isr_handler.h"

void ps_scutmr_init(u32 time_us);


#endif

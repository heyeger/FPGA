#ifndef AC820_LIB_SCU_TIMER_H_
#define AC820_LIB_SCU_TIMER_H_


#include "xparameters.h"
#include "xparameters_ps.h"

#include "xscutimer.h"

#include "SCU_GIC.h"
//#include "ISR.h"

#define CPU_CLK_HZ 666666667


XScuTimer ScuTimer;		//˽�ж�ʱ��

void ScuTimer_Int_Init(uint32_t Load_Val,Xil_InterruptHandler Handler);

#endif /* AC820_LIB_SCU_TIMER_H_ */

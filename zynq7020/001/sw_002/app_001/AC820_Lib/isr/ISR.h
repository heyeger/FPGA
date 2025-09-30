#ifndef AC820_LIB_ISR_H_
#define AC820_LIB_ISR_H_

#include "SCU_GIC.h"
//#include "SCU_TIMER.h"

#include "PS_UART.h"

//�ж���ʹ�õı�־λ
extern volatile int Send_All_Flag;	//ȫ�����ͱ�־
extern volatile int Recv_All_Flag;	//ȫ�����ձ�־
extern volatile int TimeOut_Flag;	//��ʱ��־

void ScuTimer_IRQ_Handler(void *CallBackRef);

void PS_UART1_IRQ_Handler(void *CallBackRef, uint32_t Event, unsigned int EventData);

#endif /* AC820_LIB_ISR_H_ */

/**
  *****************************************************************************
  * 					����û��жϴ�������������ͳһ����
  *****************************************************************************
  *
  * @File   : ISR.c
  * @By     : Sun
  * @Version: V0.5
  * @Date   : 2022 / 06 / 01
  * @Shop	: https://xiaomeige.taobao.com/
  *
  *****************************************************************************
**/

#include "ISR.h"

uint8_t Receive_Buffer[10];
uint8_t Data[10];
uint8_t i;

//�ж���ʹ�õı�־λ
volatile int Send_All_Flag = 0;	//ȫ�����ͱ�־
volatile int Recv_All_Flag = 0;	//ȫ�����ձ�־
volatile int TimeOut_Flag = 0;	//��ʱ��־

/**
  *****************************************************
  * @brief	˽�ж�ʱ���жϴ�������
  * @tag	��������������˽�ж�ʱ���жϣ����ڲ������û����򼴿�
  *****************************************************
**/

//void ScuTimer_IRQ_Handler(void *CallBackRef)
//{
//	/* �������û����������� */
//
//
//	/* �������������������� */
//    XScuTimer_ClearInterruptStatus(&ScuTimer);
//}

/***********************************************************************************************************
 * @brief:	PS_UART1�жϴ�������
 * @param:	CallBackRef������������������Ļص����ã��ڱ����У�����XUartPs���������ʵ��ָ�롣
 * @param:	Event�������ѷ������ض����͵��¼���
 * @param:	EventData���������ͺͽ����¼������ͻ���յ��ֽ�����
 * @return:	None.
***********************************************************************************************************/
void PS_UART1_IRQ_Handler(void *CallBackRef, uint32_t Event, unsigned int EventData)
{
	//�������
	if(Event == XUARTPS_EVENT_SENT_DATA){
		Send_All_Flag = 1;
    Send_All_Flag = 0;
	}

	//�������
	if(Event == XUARTPS_EVENT_RECV_DATA){	//����ж��¼�Ϊ���ڽ����ж�
		Recv_All_Flag = 1;

    PS_Uart_RecvData(&UartPs1, Receive_Buffer, 10);

    if((Receive_Buffer[0] == 'S') && (Receive_Buffer[9] == 'E')) {
				for(i=0;i<8;i++) {
					Data[i] = Receive_Buffer[i+1];
				}

				//�ط�8λ��Ч����
				XUartPs_Send(&UartPs1,Data,8);

				//����
				PS_Uart_SendString(&UartPs1,"\n");
		}
    Recv_All_Flag = 0;
	}

	//��ʱ
	if(Event == XUARTPS_EVENT_RECV_TOUT){
		TimeOut_Flag = 1;
    TimeOut_Flag = 0;
	}

}

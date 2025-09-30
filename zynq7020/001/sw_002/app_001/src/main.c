/**
  *****************************************************************************
  * 					ʹ��PS�˵Ĵ����ж�ʵ�����ݷ��ͺͽ��մ���
  * 				֡ͷ'S' ֡β'E' �м���Ч���ݳ���Ϊ8�ֽڣ��ܳ�10�ֽ�
  *****************************************************************************
  *
  * @File   : main.c
  * @By     : Sun
  * @Version: V1.0
  * @Date   : 2022 / 06 / 07
  * @Shop	: https://xiaomeige.taobao.com/
  *
  *****************************************************************************
**/
#include "main.h"

//uint8_t Receive_Buffer[10];

int main(void)
{
	//uint8_t Data[10];
	//uint8_t i;

	//����ͨ���жϿ�����
	ScuGic_Init();

	//UART��ʼ��
	PS_UART_Init(&UartPs1,XPS_UART1_BASEADDR, XUARTPS_OPER_MODE_NORMAL, 921600);

	//UART�жϳ�ʼ����������ʱ����
	PS_UART_Intr_Init(&UartPs1, PS_UART1_IRQ_ID, 8, (void *)PS_UART1_IRQ_Handler);

	//UART����
	PS_Uart_SendString(&UartPs1,"00 01 02 03 04 05 06 07 08 09 10 "
			"11 12 13 14 15 16 17 18 19 20 21 22 23 24 25\n");

	//�ȴ���һ�ַ������
	//while(!Send_All_Flag);
	//Send_All_Flag = 0;

	PS_Uart_SendString(&UartPs1,"UART send done!!!\n");


	while(1) {
/*
		//UART����10���ַ�
		PS_Uart_RecvData(&UartPs1, Receive_Buffer, 10);

		//�ȴ�10�ֽڽ�����ɻ���ճ�ʱ
		while(!(Recv_All_Flag || TimeOut_Flag));


		//���������������
		if(Recv_All_Flag) {
			//���������ɱ�־
			Recv_All_Flag = 0;

			//�������ܵ������ݣ�֡ͷ'S' ֡β'E'���м���Ч���ݳ���Ϊ8�ֽ�
			if((Receive_Buffer[0] == 'S') && (Receive_Buffer[9] == 'E')) {
				for(i=0;i<8;i++) {
					Data[i] = Receive_Buffer[i+1];
				}

				//�ط�8λ��Ч����
				XUartPs_Send(&UartPs1,Data,8);

				//����
				PS_Uart_SendString(&UartPs1,"\n");
			}
		}

		//���ճ�ʱ�����½���
		if(TimeOut_Flag) {
			//������ճ�ʱ��־
			TimeOut_Flag = 0;
		}
*/	}

	return 0;

}

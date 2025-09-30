/**
  *****************************************************************************
  * 						PS����UART��ؿ�
  *****************************************************************************
  *
  * @File   : PS_UART.c
  * @By     : Sun
  * @Version: V1.3
  * @Date   : 2021 / 11 / 04
  * @Shop	: https://xiaomeige.taobao.com/
  *
  *****************************************************************************
**/


#include "PS_UART.h"

XUartPs UartPs1;			//UART�豸ʵ��



/***********************************************************************************************************
 * @brief:	��ʼ��PS_UART�豸
 * @param:	UartInstPtr		UART����
 * @param:	DeviceId		UART�豸ID
 * @param:	UART_Mode		UARTģʽѡ��
 * @param:	BaudRate		���ò�����
 * ģʽ�����¼��֣�	XUARTPS_OPER_MODE_NORMAL		��׼ģʽ
 * 					XUARTPS_OPER_MODE_AUTO_ECHO		�Զ�����ģʽ
 * 					XUARTPS_OPER_MODE_LOCAL_LOOP	���ػ���ģʽ
 * 					XUARTPS_OPER_MODE_REMOTE_LOOP	Զ�̻���ģʽ
 * 			//��ʼ��UART�豸UartPs1����Ϊ��׼ģʽ��������115200
 * Sample:	PS_UART_Init(&UartPs1,XPAR_PS7_UART_1_DEVICE_ID, XUARTPS_OPER_MODE_NORMAL, 115200);
***********************************************************************************************************/
void PS_UART_Init(XUartPs *UartInstPtr,u32 DeviceId, uint8_t UART_Mode, uint32_t BaudRate)
{
	XUartPs_Config *Config;
	Config = XUartPs_LookupConfig(DeviceId);
	XUartPs_CfgInitialize(UartInstPtr, Config, Config->BaseAddress);

	//���ò�����
	XUartPs_SetBaudRate(UartInstPtr, BaudRate);

	//����UARTģʽ
	XUartPs_SetOperMode(UartInstPtr, UART_Mode);
}

/***********************************************************************************************************
 * @brief:	��ʼ��PS UART�жϣ���ʼ��PS UART�ж�ǰ�����ȳ�ʼ��PS UART��
 * @param:	UartInstPtr	UART����
 * @param:	UartIntrId		UART�ж�ID
 * @param:	RecvTimeout		���ճ�ʱ���ã�����Ϊnʱ���������nx4���ַ�ʱ����δ���յ����ݣ�����볬ʱ�жϣ�
 * 							����Ϊ0ʱ���øù��ܣ�
 * @return:	��
 * Sample:	PS_UART_Intr_Init(&UartPs1, PS_UART1_IRQ_ID, 8, (void *)PS_UART1_IRQ_Handler);
 * 			//��ʼ��PS UART�жϣ�UART����ΪUartPs���ж�IDΪUART1_IRQ_ID�����ճ�ʱ32�ַ�
***********************************************************************************************************/
void PS_UART_Intr_Init(XUartPs *UartInstPtr,uint16_t UartIntrId, uint8_t RecvTimeout, Xil_InterruptHandler Handler)
{
	uint32_t IntrMask;

	Set_ScuGic_Link(UartIntrId, 0xA8, HIGH_Level_Sensitive,
			(Xil_ExceptionHandler)XUartPs_InterruptHandler, (void *)UartInstPtr);

	//Ϊ UART ���ô������򣬵����ݷ��ͺͽ���ʱ���ô������򽫴��ж��������е��ã�
	//ָ��һ��ָ�� UART ��������ʵ����ָ����Ϊ�ص����ã��Ա㴦�������ܹ�����ʵ������
	XUartPs_SetHandler(UartInstPtr, (XUartPs_Handler)Handler, UartInstPtr);

	//����UART���ж�ģʽ
	IntrMask = XUARTPS_IXR_TOUT |	XUARTPS_IXR_PARITY | XUARTPS_IXR_FRAMING |
		XUARTPS_IXR_OVER | XUARTPS_IXR_TXEMPTY | XUARTPS_IXR_RXFULL | XUARTPS_IXR_RXOVR;
	XUartPs_SetInterruptMask(UartInstPtr, IntrMask);

	//Fifo��ֵ����Ϊ1
	XUartPs_SetFifoThreshold(&UartPs1, 1);

	//���ճ�ʱ����
	XUartPs_SetRecvTimeout(UartInstPtr, RecvTimeout);

}

/***********************************************************************************************************
 * @brief:	ʹ��PS UART�������ݣ���������0~65535֮��
 * @param:	UartInstPtr		UART����
 * @param:	data			����
 * @return:	��
 * Sample:	PS_Uart_SendData(&UartPs,12345); //��������12345
***********************************************************************************************************/
void PS_Uart_SendData(XUartPs *UartInstPtr,uint32_t data)
{
	uint8_t SendData[2];
	int data_H,data_L;
	data_H = data>>8;
	data_L = data&0x00ff;
	if(data_H == 0)//�����λΪ0
	{
		SendData[0] = data;
		XUartPs_Send(UartInstPtr, SendData, 1);
	}
	else
	{
		SendData[0] = data_H;
		SendData[1] = data_L;
		XUartPs_Send(UartInstPtr, SendData, 2);
	}
}

/***********************************************************************************************************
 * @brief:	ʹ��PS UART�����ַ���
 * @param:	UartInstPtr		UART����
 * @param:	str				�ַ�����ַ
 * @return:	��
 * Sample:	PS_Uart_SendString(&UartPs,"1234567"); //������7���ֽ�
***********************************************************************************************************/
void PS_Uart_SendString(XUartPs *UartInstPtr, char *str)
{
	XUartPs_Send(UartInstPtr, (uint8_t *)str, strlen(str));
}

/***********************************************************************************************************
 * @brief:	ʹ��PS UART��������
 * @param:	UartInstPtr		UART����
 * @param:	Buffer			�������ݴ洢��
 * @param:	Len				�������ݵĳ���
 * @return:	��
 * Sample:	PS_Uart_RecvData(&UartPs, RecvBuffer,2);�����������ݣ��������ݴ���RecvBuffer����
***********************************************************************************************************/
void PS_Uart_RecvData(XUartPs *UartInstPtr, uint8_t *Buffer,uint32_t Len)
{
	XUartPs_Recv(UartInstPtr, Buffer, Len);
}


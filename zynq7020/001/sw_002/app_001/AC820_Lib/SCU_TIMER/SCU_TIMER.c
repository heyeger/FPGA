/**
  *****************************************************************************
  * 						˽�ж�ʱ��Ӧ�ÿ�
  *****************************************************************************
  *
  * @File   : SCU_TIMER.c
  * @By     : Sun
  * @Version: V0.5
  * @Date   : 2022 / 05 / 30
  * @Shop	: https://xiaomeige.taobao.com/
  *
  *****************************************************************************
**/
#include "SCU_TIMER.h"

XScuTimer ScuTimer;		//˽�ж�ʱ��


/**
  *****************************************************
  * @brief	��ʼ��˽�ж�ʱ��
  * @param	Time_us		��ʱ���жϴ���ʱ�䣬��λΪus
  * @usage	ScuTimer_Int_Init(20);	//��ʼ��˽�ж�ʱ����ÿ20us����һ��
  * @tag	����������˽�ж�ʱ�����������������жϣ�Ҫֹͣ˽�ж�ʱ����ʹ��XScuTimer_Stop(&ScuTimer);
  *****************************************************
**/
void ScuTimer_Int_Init(uint32_t Time_us,Xil_InterruptHandler Handler)
{
	uint32_t Load_Val;
    //��ʱ����ʼ��
    XScuTimer_Config *Config;
    Config = XScuTimer_LookupConfig(XPAR_SCUTIMER_BASEADDR);
    XScuTimer_CfgInitialize(&ScuTimer, Config,Config->BaseAddr);

    //��usת��Ϊ��ʱ��װ��ֵ
    Load_Val = ((float)CPU_CLK_HZ / 2 / 1000000 * Time_us) - 1;

	//�����Զ�װ��ֵ���Զ�װ��ģʽ
    XScuTimer_LoadTimer(&ScuTimer, Load_Val);
    XScuTimer_EnableAutoReload(&ScuTimer);

    //���ӵ��жϿ�����
    Set_ScuGic_Link(XPAR_SCUTIMER_INTR, 0xA8, HIGH_Level_Sensitive,Handler, (void *)&ScuTimer);

    //ʹ�ܶ�ʱ���ж�
    XScuTimer_EnableInterrupt(&ScuTimer);

    //����������
    XScuTimer_Start(&ScuTimer);
}

/****************************** (C) COPYRIGHT 2016 *******************************
 *
 * ͨ��ʹ�ùٷ�������������LED�ƣ�ʵ����ز�������Ҫ�о�ѧϰGPIO��ʹ��
 * 
 *********************************************************************************/


#include "includes.h"





/*************************************************
	Function: 		main
	Description: 	������
	Calls: 			ReadPressure
	Called By:		startup�ײ���
	Input: 			��
	Output: 		��
	Return: 		0
*************************************************/
int main(void)
{	
	/* ����NVIC�ж����ȼ����� */
	NVIC_Configuration();
	
	LED_Init();				//��ʼ��LED�˿� 

	KEY_Init();				//�����������ü��ж�����

	LedTurnOnALL();
	DelayTest(2);
	LedTurnOffALL();

	while(1)
	{
//		KeyScan();			//ɨ�谴���ķ�ʽ
		
	}
}



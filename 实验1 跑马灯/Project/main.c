/****************************** (C) COPYRIGHT 2016 *******************************
 *
 * ͨ��ʹ�ùٷ�������������LED�ƣ�ʵ����ز�������Ҫ�о�ѧϰGPIO��ʹ��
 * 
 *********************************************************************************/


#include "includes.h"

#define DELAY_ABOUT_200MS 0x3FFFFF


void Delay100msSoft(void);
void DelayTest(u8 cnt);




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

	LED_Init();				//��ʼ��LED�˿� 
	

	while(1)
	{
		/* ����Ʒ���1 */
//		LED_TurnOn(LED1);
//		DelayTest(1);
//		LED_TurnOn(LED2);
//		DelayTest(1);
//		LED_TurnOn(LED3);
//		DelayTest(1);
//		LED_TurnOn(LED4);
//		DelayTest(1);
//		LED_TurnOff(LED1);
//		DelayTest(1);
//		LED_TurnOff(LED2);
//		DelayTest(1);
//		LED_TurnOff(LED3);
//		DelayTest(1);
//		LED_TurnOff(LED4);
//		DelayTest(1);
	
		/* ����Ʒ���2 */	
		for (u8 i = LED1; i <= LED4; i++)
		{
			LED_TurnOn(i);
			DelayTest(1);
		}
		for (u8 i = LED1; i <= LED4; i++)
		{
			LED_TurnOff(i);
			DelayTest(1);
		}
		
	}
}


/**************************************
 * ��������DelayTest
 * ����  ���򵥵Ĳ���׼��ʱ
 * ����  ����
 * ���  ����
 *************************************/
void DelayTest(u8 cnt)
{
	for (u8 i = 0; i < cnt; i++)
	{
		Delay100msSoft();
	}
}


/**************************************
 * ��������Delay100msSoft
 * ����  ���򵥵���ʱ����Լms
 * ����  ����
 * ���  ����
 *************************************/
void Delay100msSoft(void)	 //
{
	__IO u32 nCount = DELAY_ABOUT_200MS;
	for(; nCount != 0; nCount--);
}


/****************************** (C) COPYRIGHT 2016 *******************************
 *
 * ͨ��ʹ�ùٷ���������������������ʵ����ز�������Ҫ�о�ѧϰGPIO��ʹ��
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
	delay_init();
	BEEP_Init();

	while(1)
	{
		GPIO_SetBits(GPIOF, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
		PFout(6) = 0;
		delay_us(50000);
		GPIO_ResetBits(GPIOF, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);	 
		PFout(6) = 1;
		delay_us(50000);
	}
}



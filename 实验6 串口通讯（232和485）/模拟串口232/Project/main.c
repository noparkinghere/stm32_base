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
	NVIC_Configuration();
	COM_Init();				//ͨѶ��ʼ��
	delay_init();
	
	TIM_Init();
	TIM3_Init_Ctrl(DISABLE);	
	
	while(1)
	{
//		UART_SendByte('a');
//		UART_SendByte('f');
//		my_printf("UART TEST!\n");
		delay_ms(200);
		delay_ms(200);
		delay_ms(200);
		delay_ms(200);
		Xprintf();
	}
}



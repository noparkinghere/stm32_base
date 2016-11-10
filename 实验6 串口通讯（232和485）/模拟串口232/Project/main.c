/****************************** (C) COPYRIGHT 2016 *******************************
 *
 * 通过使用官方函数库来操作LED灯，实现相关操作，主要研究学习GPIO的使用
 * 
 *********************************************************************************/


#include "includes.h"




/*************************************************
	Function: 		main
	Description: 	主函数
	Calls: 			ReadPressure
	Called By:		startup底层汇编
	Input: 			无
	Output: 		无
	Return: 		0
*************************************************/
int main(void)
{
	NVIC_Configuration();
	COM_Init();				//通讯初始化
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



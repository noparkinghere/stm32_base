/****************************** (C) COPYRIGHT 2016 *******************************
 *
 * 通过使用官方函数库来操作蜂鸣器，实现相关操作，主要研究学习GPIO的使用
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



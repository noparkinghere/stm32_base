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
	/* 配置NVIC中断优先级分组 */
	NVIC_Configuration();
	
	LED_Init();				//初始化LED端口 

	KEY_Init();				//包含按键设置及中断设置

	LedTurnOnALL();
	DelayTest(2);
	LedTurnOffALL();

	while(1)
	{
//		KeyScan();			//扫描按键的方式
		
	}
}



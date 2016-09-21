/****************************** (C) COPYRIGHT 2016 *******************************
 *
 * 通过使用官方函数库来操作LED灯，实现相关操作，主要研究学习GPIO的使用
 * 
 *********************************************************************************/


#include "includes.h"

#define DELAY_ABOUT_200MS 0x3FFFFF


void Delay100msSoft(void);
void DelayTest(u8 cnt);




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

	LED_Init();				//初始化LED端口 
	

	while(1)
	{
		/* 走马灯方法1 */
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
	
		/* 走马灯方法2 */	
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
 * 函数名：DelayTest
 * 描述  ：简单的不精准延时
 * 输入  ：无
 * 输出  ：无
 *************************************/
void DelayTest(u8 cnt)
{
	for (u8 i = 0; i < cnt; i++)
	{
		Delay100msSoft();
	}
}


/**************************************
 * 函数名：Delay100msSoft
 * 描述  ：简单的延时函数约ms
 * 输入  ：无
 * 输出  ：无
 *************************************/
void Delay100msSoft(void)	 //
{
	__IO u32 nCount = DELAY_ABOUT_200MS;
	for(; nCount != 0; nCount--);
}


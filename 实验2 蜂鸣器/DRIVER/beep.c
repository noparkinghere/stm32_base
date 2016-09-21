#include "beep.h" 



/** Default config for LED GPIO init structure. */
#define BEEP_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_OUT,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_DOWN									\
}




/*************************************************
	Function: 		BEEP_Init
	Description: 	蜂鸣器初始化函数				
	Calls: 			GPIO口初始化
	Called By:		
	Input: 			无
	Output: 		无
	Return: 		无
*************************************************/
void BEEP_Init(void)
{   

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

	/* 初始化蜂鸣器对应引脚 */
	GPIO_InitTypeDef  GPIO_InitStructure = BEEP_GPIO_DEFAULT;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO

	GPIO_ResetBits(GPIOF,GPIO_Pin_6);  //蜂鸣器对应引脚GPIOF8拉低有效开启
}



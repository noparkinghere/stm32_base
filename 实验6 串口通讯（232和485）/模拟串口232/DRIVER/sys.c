/****************************** (C) COPYRIGHT 2016 *******************************
 *
 *  	功能：中断优先级控制，多种延时函数，及位带操作等功能
 *		注意：位带操作相关实现在sys.h中，且移植性较强
 * 
 ********************************************************************************/

#include "sys.h"


static u8  fac_us=0;		//us延时倍乘数
static u16 fac_ms=0;		//ms延时倍乘数



/**-------------------------------------------------------
  * @函数名 NVIC_GroupConfig
  * @功能   配置NVIC中断优先级分组函数.
  *         默认配置为1比特表示主优先级, 3比特表示次优先级
  *         用户可以根据需要修改
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void NVIC_Configuration(void)
{
	/* 配置NVIC中断优先级分组:
	 - 1比特表示主优先级  主优先级合法取值为 0 或 1 
	 - 3比特表示次优先级  次优先级合法取值为 0..7
	 - 数值越低优先级越高，取值超过合法范围时取低bit位 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/*==================================================================================
	NVIC_PriorityGroup   |  主优先级范围  |  次优先级范围  |   描述
	==================================================================================
	NVIC_PriorityGroup_0  |      0         |      0-15      |   0 比特表示主优先级
						 |                |                |   4 比特表示次优先级 
	----------------------------------------------------------------------------------
	NVIC_PriorityGroup_1  |      0-1       |      0-7       |   1 比特表示主优先级
						 |                |                |   3 比特表示次优先级 
	----------------------------------------------------------------------------------
	NVIC_PriorityGroup_2  |      0-3       |      0-3       |   2 比特表示主优先级
						 |                |                |   2 比特表示次优先级 
	----------------------------------------------------------------------------------
	NVIC_PriorityGroup_3  |      0-7       |      0-1       |   3 比特表示主优先级
						 |                |                |   1 比特表示次优先级 
	----------------------------------------------------------------------------------
	NVIC_PriorityGroup_4  |      0-15      |      0         |   4 比特表示主优先级
						 |                |                |   0 比特表示次优先级   
	==================================================================================*/
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
 * 初始化延迟函数
 * SYSTICK的时钟固定为HCLK时钟的1/8
 * SYSCLK:系统时钟
 *************************************/
void delay_init(void)	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	
	fac_us = SystemCoreClock / 8000000;	//SystemCoreClock=180M, time=fac_us*(1/(AHB/8))
	fac_ms = (u16)fac_us * 1000;//非ucos下,代表每个ms需要的systick时钟数   
}								    

/*******************************
 * 延时nus
 * nus为要延时的us数.
 ******************************/ 
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD = nus*fac_us; //时间加载	  		 
	SysTick->VAL = 0x00;        //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp = SysTick->CTRL;
	}while(temp & 0x01 && !(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	 
}


/********************************************
	延时nms
	注意nms的范围
	SysTick->LOAD为24位寄存器,所以,最大延时为:
	nms<=0xffffff*8*1000/SYSCLK
	SYSCLK单位为Hz,nms单位为ms
	对72M条件下,nms<=1864 
********************************************/
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD = (u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;           //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
	do
	{
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	  	    
} 




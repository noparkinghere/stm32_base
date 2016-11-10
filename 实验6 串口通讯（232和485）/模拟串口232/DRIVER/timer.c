/****************************** (C) COPYRIGHT 2016 *******************************
 *
 *  	功能：MCU时钟驱动相关函数和中断服务函数
 *		注意：包含了中断等相关功能
 * 
 ********************************************************************************/

#include "timer.h"
#include "led.h"
#include "key.h"
#include "com.h"

u8 g_TimeOut = 0;

#define TIMER_NVIC_DEFAULT				\
{										\
	TIM2_IRQn,							\
	0xf,								\
	0xf,								\
	ENABLE,								\
}



#define TIM_INIT_DEFAULT				\
{										\
	4499,								\
	TIM_CounterMode_Up,					\
	9999,								\
	TIM_CKD_DIV1,						\
	0x00								\
}


TIM_TypeDef * TIMER_NUM[4] = {TIM2, TIM3, TIM4, TIM5};


void TIM_Init(void)
{
	/* t=10000*1/(180M/4*2/9000) */
	TIM_Configure(TIMER3, UART_TIME_OUT, 1);
	
}



/***************************************************************
	通用定时器中断初始化
	除非 APB1 的时钟分频数设置为 1（一般都不会是 1），否则通用
	定时器 TIMx 的时钟是 APB1 时钟的 2 倍
	arr：自动重装值。
	psc：时钟预分频数
	定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
	Ft=定时器工作频率,单位:Mhz
	这里使用的是定时器3!
***************************************************************/
void TIM_Configure(TIMER_TypeDef num, u16 arr,u16 psc)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  // 使能TIM3时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = TIM_INIT_DEFAULT;
	
	/* 这个就是自动装载的计数值，由于计数是从0开始的，计数arr次后为arr-1*/
	TIM_TimeBaseInitStructure.TIM_Period = arr - 1;
	
	/* 这个就是预分频系数，当由于为0时表示不分频所以要减1 */
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;  //定时器分频
	TIM_TimeBaseInit(TIMER_NUM[num], &TIM_TimeBaseInitStructure);//初始化TIMER_NUM[num]
	TIM_ITConfig(TIMER_NUM[num], TIM_IT_Update,ENABLE); //允许定时器3更新中断
//	TIM_Cmd(TIMER_NUM[num], ENABLE); //使能定时器3
	TIM_Cmd(TIMER_NUM[num], DISABLE); //失能定时器3


}


void TIM3_Init_Ctrl(u8 state)
{
	/* 定时器中断功能，如有需要可以单独设为函数 */
	NVIC_InitTypeDef NVIC_InitStructure = TIMER_NVIC_DEFAULT;
	NVIC_InitStructure.NVIC_IRQChannelCmd = state;
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x07; //子优先级3
	NVIC_Init(&NVIC_InitStructure);

}

/* 定时器3中断服务函数，该定时器用于判定是否串口接受结束 */
void TIM3_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		g_TimeOut = 1;
		
		TIM_Cmd(TIMER_NUM[TIMER3], DISABLE); //失能定时器3
		TIM3_Init_Ctrl(DISABLE);
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}








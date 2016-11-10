/****************************** (C) COPYRIGHT 2016 *******************************
 *
 *  	功能：串口驱动相关函数
 *		注意：包含了中断等相关功能
 * 
 ********************************************************************************/
 

#include "com.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys.h"
#include "exti.h"
#include "timer.h"


/* usart引脚相关定义 */
#define USART1_RCC			RCC_APB2Periph_USART1

#define RX1_PORT_RCC		RCC_AHB1Periph_GPIOA
#define RX1_PORT			GPIOA
#define RX1_PIN				GPIO_Pin_10

#define TX1_PORT_RCC		RCC_AHB1Periph_GPIOA
#define TX1_PORT			GPIOA
#define TX1_PIN				GPIO_Pin_9


#define RX1_PORT_SOURCE		GPIO_PortSourceGPIOA
#define RX1_PIN_SOURCE		GPIO_PinSource10
#define RX1_EXTI_LINE		EXTI_Line10
#define RX1_EXTI_IRQn 		EXTI15_10_IRQn

#define RX1_READ() 		GPIO_ReadInputDataBit(RX1_PORT, RX1_PIN) 	//PA0


/** Default config for LED GPIO init structure. */
#define LED_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_OUT,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}

/** Default config for KEY GPIO init structure. */
#define KEY_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_IN,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}



#define EN_USART_RX		1		//是否启动串口中断
#define USART_DATA_LEN	8		//每次发送8个位的数据
#define BAUD_RATE		115200	//波特率115200

/* 控制串口管脚的高低电平 */
#define RX_HIGH()		GPIO_SetBits(RX1_PORT, RX1_PIN)
#define RX_LOW()		GPIO_ResetBits(RX1_PORT, RX1_PIN)
#define TX_HIGH()		GPIO_SetBits(TX1_PORT, TX1_PIN)
#define TX_LOW()		GPIO_ResetBits(TX1_PORT, TX1_PIN)

#define	UART_DELAY()	delay_com(BAUD_RATE)



u8 point = 0;
u8 g_byStore[100];

void delay_com(u32 baud);
void USART_Configure(void);
void UART_SendByte(u8 data);
void EXTIX_KeyInit(void);
void EXTIX_KeyInit(void);
u8 UART_GetByte(void);


/* 通讯初始化 */
void COM_Init(void)		
{
	USART_Configure();

//	USART_Configure(COM_USART3, 115200);
	
}

/* 串口IO管脚配置 */
void USART_Configure(void)
{

	RCC_AHB1PeriphClockCmd(TX1_PORT_RCC, ENABLE); 
	RCC_AHB1PeriphClockCmd(RX1_PORT_RCC, ENABLE); 
//	RCC_APB2PeriphClockCmd(USART1_RCC, ENABLE);

	/* 初始化IO口 */
	GPIO_InitTypeDef GPIO_RX_InitStructure = KEY_GPIO_DEFAULT;	//模拟使用串口时，直接配置成IO口即可
	GPIO_RX_InitStructure.GPIO_Pin = RX1_PIN;
	GPIO_Init(RX1_PORT, &GPIO_RX_InitStructure); 

	/* GPIO，RX口初始化 */
	GPIO_InitTypeDef GPIO_TX_InitStructure = LED_GPIO_DEFAULT;
	GPIO_TX_InitStructure.GPIO_Pin = TX1_PIN;
	GPIO_Init(TX1_PORT, &GPIO_TX_InitStructure); 
	
	/*作为串口需要初始为高电平*/
	TX_HIGH();
	RX_HIGH();	

	EXTIX_KeyInit();       			


}


/* 串口延时时间，主要用来设置波特率 */
void delay_com(u32 baud)
{		
	u32 temp;	    	 
	SysTick->LOAD =  SystemCoreClock / 8 / baud; //时间加载	  		 
	SysTick->VAL = 0x00;        //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp = SysTick->CTRL;
	}while(temp & 0x01 && !(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	 
}


/* 串口完整发送一个字节的数据 */
void UART_SendByte(u8 data)
{
	TX_LOW();	// 开始位
	UART_DELAY();

	for (u8 i = 0; i < USART_DATA_LEN; i++)
	{
		if (data & 0x01)
		{
			TX_HIGH();
		}
		else 
		{
			TX_LOW();
		}
		data >>= 1;
		
		UART_DELAY();
	}
	
	TX_HIGH();		// 停止位
	
	// 每一次停止发送完成后，会有一段较长的间隔时间
	UART_DELAY();
	UART_DELAY();
}



/* 字符串打印程序 */
void my_printf(char * str, ...)
{
	while (*str != '\0')
	{
		UART_SendByte((u8)*str++);
	}
}



/* 串口完整发送一个字节的数据 */
u8 UART_GetByte(void)
{
	u8 Data = 0;

	for (u8 i = 0; i < USART_DATA_LEN; i++)
	{
		UART_DELAY();
		Data |= RX1_READ()<<i;	
	}

	return Data;

}

void Xprintf(void)
{
	if (g_TimeOut && point)
	{
		for (u8 i = 0; i < point; i++)
		{
			UART_SendByte(g_byStore[i]);
		}
		
		point = 0;
	}
}


void EXTIX_KeyInit(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Connect Button EXTI Line to Button GPIO Pin */
	SYSCFG_EXTILineConfig(RX1_PORT_SOURCE, RX1_PIN_SOURCE);

	/* Configure Button EXTI line */
	EXTI_InitStructure.EXTI_Line = RX1_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = RX1_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//全部采用相同最低优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//全部采用相同最低优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
}






/**-------------------------------------------------------
  * @函数名 EXTI15_10_IRQHandler
  * @功能   处理外部中断线10-15的中断，按键2和3中断处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void EXTI15_10_IRQHandler(void) /* bit & add */
{
	/* about key2 bit*/
    if(EXTI_GetITStatus(RX1_EXTI_LINE) != RESET)
    {
		/* 每次有数据接受时，开启定时器用来计量数据采集的时间 */

		/* 这边没必要更改arr，只需要每次使能即可 */
//		TIM3->CR1 &= ~(1 < 7);			//允许修改ARR隐寄存器
//		TIM3->ARR =	UART_TIME_OUT;		//重新将值写入ARR中
		TIM3->CNT = 0;
		TIM_Cmd(TIMER_NUM[TIMER3], ENABLE); //使能定时器3

		TIM3_Init_Ctrl(ENABLE);

		g_TimeOut = 0;
		
		
		g_byStore[point++] = UART_GetByte();
		
		/*在中断中用模拟的模式，内容基本无法打印出去，每次接收到一个数据时打印，
		会错过接受下一个字符的时间，一般采用标志位的方法，在主程序中实现操作为好*/
//		my_printf("right");

//		cnt++;

        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
      	EXTI_ClearITPendingBit(RX1_EXTI_LINE);
    } 
}





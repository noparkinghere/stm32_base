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

#define RX_HIGH()		GPIO_SetBits(RX1_PORT, RX1_PIN)

#define TX_HIGH()		GPIO_SetBits(TX1_PORT, TX1_PIN)
#define TX_LOW()		GPIO_ResetBits(TX1_PORT, TX1_PIN)

#define	UART_DELAY()	delay_com()



#define EN_USART_RX		1	//是否启动串口中断
#define COM_REV_LEN		6


/* usart引脚相关定义 */
#define USART1_RCC			RCC_APB2Periph_USART1
#define RX1_PORT_RCC		RCC_AHB1Periph_GPIOA
#define RX1_PORT			GPIOA
#define RX1_PIN				GPIO_Pin_10
#define RX1_PIN_SOURCE		GPIO_PinSource10
#define TX1_PORT_RCC		RCC_AHB1Periph_GPIOA
#define TX1_PORT			GPIOA
#define TX1_PIN				GPIO_Pin_9
#define TX1_PIN_SOURCE		GPIO_PinSource9



#define USART_NUM	2




char ComRev[6];		// 串口接受数据



/** Default config for LED GPIO init structure. */
#define LED_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_OUT,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}


/* 通讯初始化 */
void COM_Init(void)		
{
	USART_Configure();
//	USART_Configure(COM_USART3, 115200);
	
}


void USART_Configure(void)
{

	RCC_AHB1PeriphClockCmd(TX1_PORT_RCC, ENABLE); 
	RCC_AHB1PeriphClockCmd(RX1_PORT_RCC, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* 定义 几个用来初始化的变量 */
	GPIO_InitTypeDef GPIO_InitStructure = LED_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = RX1_PIN;
	GPIO_Init(RX1_PORT, &GPIO_InitStructure); 

	// GPIO，RX口初始化
	GPIO_InitStructure.GPIO_Pin = TX1_PIN;
	GPIO_Init(TX1_PORT, &GPIO_InitStructure); 
	
	/*作为串口需要初始为高电平*/
	TX_HIGH();
	RX_HIGH();	

}



void delay_com(void)
{		
	u32 temp;	    	 
	SysTick->LOAD =  SystemCoreClock / 8 / 115200; //时间加载	  		 
	SysTick->VAL = 0x00;        //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp = SysTick->CTRL;
	}while(temp & 0x01 && !(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	 
}


void UART_SendByte(u8 data, u8 len)
{
	for (u8 i = 0; i < len; i++)
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
}

void UART_SendData(u8 data)
{
	TX_LOW();
	UART_DELAY();

	UART_SendByte(data, 8);
	
	TX_HIGH();
	
	// 值得注意的是在发送完毕后
	UART_DELAY();
	UART_DELAY();
}


void my_printf(char * str, ...)
{
	while (*str != '\0')
	{
		UART_SendData((u8)*str++);
	}
}






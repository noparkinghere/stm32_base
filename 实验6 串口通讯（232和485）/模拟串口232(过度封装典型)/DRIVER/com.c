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

#define RX_HIGH()		GPIO_SetBits(RX_PORT[0], RX_PIN[0])

#define TX_HIGH()		GPIO_SetBits(TX_PORT[0], TX_PIN[0])
#define TX_LOW()		GPIO_ResetBits(TX_PORT[0], TX_PIN[0])

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




#define USART3_RCC			RCC_APB2Periph_USART1
#define RX3_PORT_RCC		RCC_AHB1Periph_GPIOA
#define RX3_PORT			GPIOA
#define RX3_PIN				GPIO_Pin_10
#define RX3_PIN_SOURCE		GPIO_PinSource10
#define TX3_PORT_RCC		RCC_AHB1Periph_GPIOA
#define TX3_PORT			GPIOA
#define TX3_PIN				GPIO_Pin_9
#define TX3_PIN_SOURCE		GPIO_PinSource9


#define USART_NUM	2


/* 作为常量来使用 */
GPIO_TypeDef* RX_PORT[USART_NUM] = {RX1_PORT, RX3_PORT}; 
GPIO_TypeDef* TX_PORT[USART_NUM] = {TX1_PORT, TX3_PORT}; 
USART_TypeDef *COM_USART[2] = {USART1, USART3};

const uint32_t RX_PIN[USART_NUM] = {RX1_PIN, RX3_PIN};
const uint32_t TX_PIN[USART_NUM] = {TX1_PIN, TX3_PIN};
const uint32_t RX_PIN_SOURCE[USART_NUM] = {RX1_PIN_SOURCE, RX3_PIN_SOURCE};
const uint32_t TX_PIN_SOURCE[USART_NUM] = {TX1_PIN_SOURCE, TX3_PIN_SOURCE};
const uint32_t USART_CLK[USART_NUM] = {USART1_RCC, USART3_RCC};
const uint32_t RX1_PORT_CLK[USART_NUM] = {RX1_PORT_RCC, TX3_PORT_RCC};
const uint32_t TX1_PORT_CLK[USART_NUM] = {TX1_PORT_RCC, RX3_PORT_RCC};
const uint32_t USART_AF[USART_NUM] = {GPIO_AF_USART1, GPIO_AF_USART3};
const uint32_t USART_IRQ[USART_NUM] = {USART1_IRQn, USART3_IRQn};

char ComRev[6];		// 串口接受数据



/* 加入以下代码,支持printf函数,而不需要选择use MicroLIB	*/  
#if 1
#pragma import(__use_no_semihosting)             
/* 标准库需要的支持函数 */              
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{ 
	x = x; 
}
/* 重定义fputc函数 */
int fputc(int ch, FILE *f)
{      
//	while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
//	
//	USART_SendData(USART1,(uint8_t)ch);   
//	return ch;

	UART_SendData((u8)ch);
	return ch;

}
#endif


/** Default config for LED GPIO init structure. */
#define LED_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_OUT,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}

/**************************************************************************************/

/** Default config for USART GPIO init structure. */
#define USART_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_AF,									\
	GPIO_Speed_50MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}


/** Default config for USART init structure. */
#define USART_INIT_DEFAULT							\
{													\
	9600,				/* 9600 bits/s. */        	\
	USART_WordLength_8b,					/* USART_WordLength */ 		\
	USART_StopBits_1,								\
	USART_Parity_No,								\
	USART_Mode_Rx | USART_Mode_Tx,					\
	USART_HardwareFlowControl_None					\
}

/** Default config for USART NVIC structure. */
#define USART_NVIC_DEFAULT				\
{										\
	USART1_IRQn,						\
	0xf,								\
	0xf,								\
	ENABLE,								\
}

/**************************************************************************************/




/* 通讯初始化 */
void COM_Init(void)		
{
	USART_Configure(COM_USART1, 115200);
//	USART_Configure(COM_USART3, 115200);
	
}


void USART_Configure(COM_TypeDef com, u32 bound)
{

	RCC_AHB1PeriphClockCmd(TX1_PORT_CLK[com], ENABLE); 
	RCC_AHB1PeriphClockCmd(RX1_PORT_CLK[com], ENABLE); 
	RCC_APB2PeriphClockCmd(USART_CLK[com], ENABLE);
//	GPIO_PinAFConfig(RX_PORT[com], RX_PIN_SOURCE[com], USART_AF[com]);
//	GPIO_PinAFConfig(TX_PORT[com], TX_PIN_SOURCE[com], USART_AF[com]);

	/* 定义 几个用来初始化的变量 */
	GPIO_InitTypeDef GPIO_InitStructure = LED_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = RX_PIN[com];
	GPIO_Init(RX_PORT[com], &GPIO_InitStructure); 

	// GPIO，RX口初始化
	GPIO_InitStructure.GPIO_Pin = TX_PIN[com];
	GPIO_Init(TX_PORT[com], &GPIO_InitStructure); 
	
	TX_HIGH();
	RX_HIGH();	

}



void delay_com(void)
{		
	u32 temp;	    	 
	SysTick->LOAD =  SystemCoreClock / 8 / 120000; //时间加载	  		 
	SysTick->VAL = 0x00;        //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp = SysTick->CTRL;
	}while(temp & 0x01 && !(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	 
}



/*发送起始位*/
void UART_Start()
{

}


/*发送停止位*/
void UART_Stop()
{

	UART_DELAY();
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
}


void my_printf(char * str, ...)
{
	while (*str != '\0')
	{
		UART_SendData((u8)*str++);
	}
}


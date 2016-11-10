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
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	
	USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif



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
	GPIO_PinAFConfig(RX_PORT[com], RX_PIN_SOURCE[com], USART_AF[com]);
	GPIO_PinAFConfig(TX_PORT[com], TX_PIN_SOURCE[com], USART_AF[com]);

	/* 定义 几个用来初始化的变量 */
	GPIO_InitTypeDef GPIO_InitStructure = USART_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = RX_PIN[com];
	GPIO_Init(RX_PORT[com], &GPIO_InitStructure); 

	// GPIO，RX口初始化
	GPIO_InitStructure.GPIO_Pin = TX_PIN[com];
	GPIO_Init(TX_PORT[com], &GPIO_InitStructure); 

	/* 配置usart的模式 */
	USART_InitTypeDef USART_InitStructure = USART_INIT_DEFAULT;
	USART_InitStructure.USART_BaudRate = bound;
	USART_Init(COM_USART[com], &USART_InitStructure);


	/* 串口中断功能，如有需要可以单独设为函数 */
	#if		EN_USART_RX		// 使能usart的中断		
	NVIC_InitTypeDef NVIC_InitStructure = USART_NVIC_DEFAULT;
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQ[com];	//相应中断配置
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(COM_USART[com], USART_IT_RXNE, ENABLE);
	#endif	

	USART_Cmd(COM_USART[com], ENABLE);	//最后 使能串口
}


void USART1_IRQHandler(void)
{
	static u8 c = 0;	
	
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{		
	    c=USART1->DR;
		
		//这边仅仅是个样例，并不推荐如此操作，一般中断中尽量使用标志判定，不推荐执行
		//过多语句，另外这边芯片级的有16字节左右的缓冲区，所以能够来得及打赢的，如果
		//用模拟的模式，内容基本无法打印出去，每次接收到一个数据时打印，会错过接受下一个字符的时间
	  	printf("%c",c);    //将接受到的数据直接返回打印

	}
	USART1->DR;	//清除Parity error 手册988 PE
}




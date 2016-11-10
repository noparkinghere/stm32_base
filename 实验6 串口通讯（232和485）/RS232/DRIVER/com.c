/****************************** (C) COPYRIGHT 2016 *******************************
 *
 *  	���ܣ�����������غ���
 *		ע�⣺�������жϵ���ع���
 * 
 ********************************************************************************/
 

#include "com.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>


#define EN_USART_RX		1	//�Ƿ����������ж�
#define COM_REV_LEN		6


/* usart������ض��� */
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


/* ��Ϊ������ʹ�� */
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

char ComRev[6];		// ���ڽ�������



/* �������´���,֧��printf����,������Ҫѡ��use MicroLIB	*/  
#if 1
#pragma import(__use_no_semihosting)             
/* ��׼����Ҫ��֧�ֺ��� */              
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{ 
	x = x; 
}
/* �ض���fputc���� */
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




/* ͨѶ��ʼ�� */
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

	/* ���� ����������ʼ���ı��� */
	GPIO_InitTypeDef GPIO_InitStructure = USART_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = RX_PIN[com];
	GPIO_Init(RX_PORT[com], &GPIO_InitStructure); 

	// GPIO��RX�ڳ�ʼ��
	GPIO_InitStructure.GPIO_Pin = TX_PIN[com];
	GPIO_Init(TX_PORT[com], &GPIO_InitStructure); 

	/* ����usart��ģʽ */
	USART_InitTypeDef USART_InitStructure = USART_INIT_DEFAULT;
	USART_InitStructure.USART_BaudRate = bound;
	USART_Init(COM_USART[com], &USART_InitStructure);


	/* �����жϹ��ܣ�������Ҫ���Ե�����Ϊ���� */
	#if		EN_USART_RX		// ʹ��usart���ж�		
	NVIC_InitTypeDef NVIC_InitStructure = USART_NVIC_DEFAULT;
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQ[com];	//��Ӧ�ж�����
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(COM_USART[com], USART_IT_RXNE, ENABLE);
	#endif	

	USART_Cmd(COM_USART[com], ENABLE);	//��� ʹ�ܴ���
}


void USART1_IRQHandler(void)
{
	static u8 c = 0;	
	
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{		
	    c=USART1->DR;
		
		//��߽����Ǹ������������Ƽ���˲�����һ���ж��о���ʹ�ñ�־�ж������Ƽ�ִ��
		//������䣬�������оƬ������16�ֽ����ҵĻ������������ܹ����ü���Ӯ�ģ����
		//��ģ���ģʽ�����ݻ����޷���ӡ��ȥ��ÿ�ν��յ�һ������ʱ��ӡ������������һ���ַ���ʱ��
	  	printf("%c",c);    //�����ܵ�������ֱ�ӷ��ش�ӡ

	}
	USART1->DR;	//���Parity error �ֲ�988 PE
}




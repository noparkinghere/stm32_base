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
#include "sys.h"
#include "exti.h"
#include "timer.h"


/* usart������ض��� */
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



#define EN_USART_RX		1		//�Ƿ����������ж�
#define USART_DATA_LEN	8		//ÿ�η���8��λ������
#define BAUD_RATE		115200	//������115200

/* ���ƴ��ڹܽŵĸߵ͵�ƽ */
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


/* ͨѶ��ʼ�� */
void COM_Init(void)		
{
	USART_Configure();

//	USART_Configure(COM_USART3, 115200);
	
}

/* ����IO�ܽ����� */
void USART_Configure(void)
{

	RCC_AHB1PeriphClockCmd(TX1_PORT_RCC, ENABLE); 
	RCC_AHB1PeriphClockCmd(RX1_PORT_RCC, ENABLE); 
//	RCC_APB2PeriphClockCmd(USART1_RCC, ENABLE);

	/* ��ʼ��IO�� */
	GPIO_InitTypeDef GPIO_RX_InitStructure = KEY_GPIO_DEFAULT;	//ģ��ʹ�ô���ʱ��ֱ�����ó�IO�ڼ���
	GPIO_RX_InitStructure.GPIO_Pin = RX1_PIN;
	GPIO_Init(RX1_PORT, &GPIO_RX_InitStructure); 

	/* GPIO��RX�ڳ�ʼ�� */
	GPIO_InitTypeDef GPIO_TX_InitStructure = LED_GPIO_DEFAULT;
	GPIO_TX_InitStructure.GPIO_Pin = TX1_PIN;
	GPIO_Init(TX1_PORT, &GPIO_TX_InitStructure); 
	
	/*��Ϊ������Ҫ��ʼΪ�ߵ�ƽ*/
	TX_HIGH();
	RX_HIGH();	

	EXTIX_KeyInit();       			


}


/* ������ʱʱ�䣬��Ҫ�������ò����� */
void delay_com(u32 baud)
{		
	u32 temp;	    	 
	SysTick->LOAD =  SystemCoreClock / 8 / baud; //ʱ�����	  		 
	SysTick->VAL = 0x00;        //��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
	do
	{
		temp = SysTick->CTRL;
	}while(temp & 0x01 && !(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL = 0X00;       //��ռ�����	 
}


/* ������������һ���ֽڵ����� */
void UART_SendByte(u8 data)
{
	TX_LOW();	// ��ʼλ
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
	
	TX_HIGH();		// ֹͣλ
	
	// ÿһ��ֹͣ������ɺ󣬻���һ�νϳ��ļ��ʱ��
	UART_DELAY();
	UART_DELAY();
}



/* �ַ�����ӡ���� */
void my_printf(char * str, ...)
{
	while (*str != '\0')
	{
		UART_SendByte((u8)*str++);
	}
}



/* ������������һ���ֽڵ����� */
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//ȫ��������ͬ������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//ȫ��������ͬ������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
}






/**-------------------------------------------------------
  * @������ EXTI15_10_IRQHandler
  * @����   �����ⲿ�ж���10-15���жϣ�����2��3�жϴ�����
  * @����   ��
  * @����ֵ ��
***------------------------------------------------------*/
void EXTI15_10_IRQHandler(void) /* bit & add */
{
	/* about key2 bit*/
    if(EXTI_GetITStatus(RX1_EXTI_LINE) != RESET)
    {
		/* ÿ�������ݽ���ʱ��������ʱ�������������ݲɼ���ʱ�� */

		/* ���û��Ҫ����arr��ֻ��Ҫÿ��ʹ�ܼ��� */
//		TIM3->CR1 &= ~(1 < 7);			//�����޸�ARR���Ĵ���
//		TIM3->ARR =	UART_TIME_OUT;		//���½�ֵд��ARR��
		TIM3->CNT = 0;
		TIM_Cmd(TIMER_NUM[TIMER3], ENABLE); //ʹ�ܶ�ʱ��3

		TIM3_Init_Ctrl(ENABLE);

		g_TimeOut = 0;
		
		
		g_byStore[point++] = UART_GetByte();
		
		/*���ж�����ģ���ģʽ�����ݻ����޷���ӡ��ȥ��ÿ�ν��յ�һ������ʱ��ӡ��
		����������һ���ַ���ʱ�䣬һ����ñ�־λ�ķ���������������ʵ�ֲ���Ϊ��*/
//		my_printf("right");

//		cnt++;

        /* ����жϹ����־λ������ᱻ��Ϊ�ж�û�б������ѭ���ٴν����ж� */
      	EXTI_ClearITPendingBit(RX1_EXTI_LINE);
    } 
}





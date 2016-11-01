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

#define RX_HIGH()		GPIO_SetBits(RX1_PORT, RX1_PIN)

#define TX_HIGH()		GPIO_SetBits(TX1_PORT, TX1_PIN)
#define TX_LOW()		GPIO_ResetBits(TX1_PORT, TX1_PIN)

#define	UART_DELAY()	delay_com()



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



#define USART_NUM	2




char ComRev[6];		// ���ڽ�������



/** Default config for LED GPIO init structure. */
#define LED_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_OUT,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}


/* ͨѶ��ʼ�� */
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

	/* ���� ����������ʼ���ı��� */
	GPIO_InitTypeDef GPIO_InitStructure = LED_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = RX1_PIN;
	GPIO_Init(RX1_PORT, &GPIO_InitStructure); 

	// GPIO��RX�ڳ�ʼ��
	GPIO_InitStructure.GPIO_Pin = TX1_PIN;
	GPIO_Init(TX1_PORT, &GPIO_InitStructure); 
	
	/*��Ϊ������Ҫ��ʼΪ�ߵ�ƽ*/
	TX_HIGH();
	RX_HIGH();	

}



void delay_com(void)
{		
	u32 temp;	    	 
	SysTick->LOAD =  SystemCoreClock / 8 / 115200; //ʱ�����	  		 
	SysTick->VAL = 0x00;        //��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
	do
	{
		temp = SysTick->CTRL;
	}while(temp & 0x01 && !(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL = 0X00;       //��ռ�����	 
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
	
	// ֵ��ע������ڷ�����Ϻ�
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






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
	Description: 	��������ʼ������				
	Calls: 			GPIO�ڳ�ʼ��
	Called By:		
	Input: 			��
	Output: 		��
	Return: 		��
*************************************************/
void BEEP_Init(void)
{   

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��

	/* ��ʼ����������Ӧ���� */
	GPIO_InitTypeDef  GPIO_InitStructure = BEEP_GPIO_DEFAULT;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIO

	GPIO_ResetBits(GPIOF,GPIO_Pin_6);  //��������Ӧ����GPIOF8������Ч����
}



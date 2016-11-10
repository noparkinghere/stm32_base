#include "exti.h"
#include "key.h"



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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x07;	//ȫ��������ͬ������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x07;			//ȫ��������ͬ������ȼ�
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

        /* ����жϹ����־λ������ᱻ��Ϊ�ж�û�б������ѭ���ٴν����ж� */
      	EXTI_ClearITPendingBit(EXTI_Line13);
    } 
	 	  
}












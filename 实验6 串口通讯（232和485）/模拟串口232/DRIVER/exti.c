#include "exti.h"
#include "key.h"

#define KEY1_BUTTON_EXTI_LINE            EXTI_Line0
#define KEY1_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOA
#define KEY1_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource0
#define KEY1_BUTTON_EXTI_IRQn            EXTI0_IRQn  

#define KEY2_BUTTON_EXTI_LINE            EXTI_Line13
#define KEY2_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOC
#define KEY2_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource13
#define KEY2_BUTTON_EXTI_IRQn            EXTI15_10_IRQn   

#define KEY3_BUTTON_EXTI_LINE            EXTI_Line11
#define KEY3_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOF
#define KEY3_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource11
#define KEY3_BUTTON_EXTI_IRQn            EXTI15_10_IRQn 

#define KEY4_BUTTON_EXTI_LINE            EXTI_Line9
#define KEY4_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOI
#define KEY4_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource9
#define KEY4_BUTTON_EXTI_IRQn            EXTI9_5_IRQn 



const uint16_t BUTTON_PORT_SOURCE[KEY_NUM] = {KEY1_BUTTON_EXTI_PORT_SOURCE, KEY2_BUTTON_EXTI_PORT_SOURCE, KEY3_BUTTON_EXTI_PORT_SOURCE, KEY4_BUTTON_EXTI_PORT_SOURCE};
const uint16_t BUTTON_PIN_SOURCE[KEY_NUM] = {KEY1_BUTTON_EXTI_PIN_SOURCE, KEY2_BUTTON_EXTI_PIN_SOURCE, KEY3_BUTTON_EXTI_PIN_SOURCE, KEY4_BUTTON_EXTI_PIN_SOURCE}; 
const uint16_t BUTTON_IRQn[KEY_NUM] = {KEY1_BUTTON_EXTI_IRQn, KEY2_BUTTON_EXTI_IRQn, KEY3_BUTTON_EXTI_IRQn, KEY4_BUTTON_EXTI_IRQn};
const uint16_t BUTTON_EXTI_LINE[KEY_NUM] = {KEY1_BUTTON_EXTI_LINE, KEY2_BUTTON_EXTI_LINE, KEY3_BUTTON_EXTI_LINE, KEY4_BUTTON_EXTI_LINE};




void EXTIX_KeyInit(Button_TypeDef Button)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Connect Button EXTI Line to Button GPIO Pin */
	SYSCFG_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

	/* Configure Button EXTI line */
	EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x07;	//ȫ��������ͬ������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x07;			//ȫ��������ͬ������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  

}



/**-------------------------------------------------------
  * @������ EXTI3_IRQHandler
  * @����   �����ⲿ�ж���4���жϣ�����1�жϴ�����
  * @����   ��
  * @����ֵ ��
***------------------------------------------------------*/
void EXTI0_IRQHandler(void) /* functions */
{
	/* about key1 fun*/
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)	//�ж���ȷ���ж������ɲ���
    {
		/* �ӳ�ȥ�� */
		KeyDelay();
		if(!KEY1())
		{   
			while(!KEY1());	 // �ȴ������ͷ�
			
			KeyFun();

			KeyDelay(); // �ӳ�ȥ��
		}     

        /* Clear the EXTI Line 0 */
        /* ����жϹ����־λ������ᱻ��Ϊ�ж�û�б������ѭ���ٴν����ж� */
      	EXTI_ClearITPendingBit(EXTI_Line0);
    }
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
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
		/* �ӳ�ȥ�� */
		KeyDelay();
		if(!KEY2())
		{
			while(!KEY2());	 // �ȴ������ͷ�
			
			KeyBit();

			KeyDelay(); // �ӳ�ȥ��
		}     

        /* Clear the EXTI Line 0 */
        /* ����жϹ����־λ������ᱻ��Ϊ�ж�û�б������ѭ���ٴν����ж� */
      	EXTI_ClearITPendingBit(EXTI_Line13);
    }
	/* about key3 add*/
	else if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
		/* �ӳ�ȥ�� */
		KeyDelay();
		if(!KEY3())
		{
			while(!KEY3());	 // �ȴ������ͷ�
			
			KeyAdd();
			
			KeyDelay(); // �ӳ�ȥ��
		}

		/* Clear the EXTI Line 0 */
		/* ����жϹ����־λ������ᱻ��Ϊ�ж�û�б������ѭ���ٴν����ж� */
		EXTI_ClearITPendingBit(EXTI_Line11);
    }
      
	  
	  
}

/**-------------------------------------------------------
  * @������ EXTI9_5_IRQHandler
  * @����   �����ⲿ�ж���0���жϣ�����4�жϴ�����
  * @����   ��
  * @����ֵ ��
 **------------------------------------------------------*/
void EXTI9_5_IRQHandler(void) /* start */
{
	/* about key4 start*/
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
		/* �ӳ�ȥ�� */
		KeyDelay();
		if(!KEY4())
		{
			while(!KEY4());	 // �ȴ������ͷ�

			KeyStart();
			
			KeyDelay(); // �ӳ�ȥ��
		}

		/* ����жϹ����־λ������ᱻ��Ϊ�ж�û�б������ѭ���ٴν����ж� */
		EXTI_ClearITPendingBit(EXTI_Line9);
    }
}


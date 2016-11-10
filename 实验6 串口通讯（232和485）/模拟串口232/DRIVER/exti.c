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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x07;	//全部采用相同最低优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x07;			//全部采用相同最低优先级
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

        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
      	EXTI_ClearITPendingBit(EXTI_Line13);
    } 
	 	  
}












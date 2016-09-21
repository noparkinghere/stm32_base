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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x07;	//全部采用相同最低优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x07;			//全部采用相同最低优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  

}



/**-------------------------------------------------------
  * @函数名 EXTI3_IRQHandler
  * @功能   处理外部中断线4的中断，按键1中断处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void EXTI0_IRQHandler(void) /* functions */
{
	/* about key1 fun*/
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)	//中断明确，判断条件可不加
    {
		/* 延迟去抖 */
		KeyDelay();
		if(!KEY1())
		{   
			while(!KEY1());	 // 等待按键释放
			
			KeyFun();

			KeyDelay(); // 延迟去抖
		}     

        /* Clear the EXTI Line 0 */
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
      	EXTI_ClearITPendingBit(EXTI_Line0);
    }
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
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
		/* 延迟去抖 */
		KeyDelay();
		if(!KEY2())
		{
			while(!KEY2());	 // 等待按键释放
			
			KeyBit();

			KeyDelay(); // 延迟去抖
		}     

        /* Clear the EXTI Line 0 */
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
      	EXTI_ClearITPendingBit(EXTI_Line13);
    }
	/* about key3 add*/
	else if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
		/* 延迟去抖 */
		KeyDelay();
		if(!KEY3())
		{
			while(!KEY3());	 // 等待按键释放
			
			KeyAdd();
			
			KeyDelay(); // 延迟去抖
		}

		/* Clear the EXTI Line 0 */
		/* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
		EXTI_ClearITPendingBit(EXTI_Line11);
    }
      
	  
	  
}

/**-------------------------------------------------------
  * @函数名 EXTI9_5_IRQHandler
  * @功能   处理外部中断线0的中断，按键4中断处理函数
  * @参数   无
  * @返回值 无
 **------------------------------------------------------*/
void EXTI9_5_IRQHandler(void) /* start */
{
	/* about key4 start*/
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
		/* 延迟去抖 */
		KeyDelay();
		if(!KEY4())
		{
			while(!KEY4());	 // 等待按键释放

			KeyStart();
			
			KeyDelay(); // 延迟去抖
		}

		/* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
		EXTI_ClearITPendingBit(EXTI_Line9);
    }
}


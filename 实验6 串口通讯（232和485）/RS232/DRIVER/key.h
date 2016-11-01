#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include "led.h"


#ifdef __cplusplus
extern "C" {
#endif	



/* key引脚相关定义 */
#define KEY1_RCC	RCC_AHB1Periph_GPIOA
#define KEY1_PORT	GPIOA
#define KEY1_PIN	GPIO_Pin_0

#define KEY2_RCC	RCC_AHB1Periph_GPIOC
#define KEY2_PORT	GPIOC
#define KEY2_PIN	GPIO_Pin_13

#define KEY3_RCC	RCC_AHB1Periph_GPIOF
#define KEY3_PORT	GPIOF
#define KEY3_PIN	GPIO_Pin_11

#define KEY4_RCC	RCC_AHB1Periph_GPIOI
#define KEY4_PORT	GPIOI
#define KEY4_PIN	GPIO_Pin_9


/* 各个按键定义 */
#define KEY1() 		GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN) 	//PA0
#define KEY2() 		GPIO_ReadInputDataBit(KEY2_PORT, KEY2_PIN)	//PC13 
#define KEY3() 		GPIO_ReadInputDataBit(KEY3_PORT, KEY3_PIN) 	//PF11
#define KEY4() 		GPIO_ReadInputDataBit(KEY4_PORT, KEY4_PIN)	//PA5

#define KEY1_PRES	1
#define KEY2_PRES	2
#define KEY3_PRES	3
#define KEY4_PRES	4

#define KEY_NUM		4


/* 软件防抖设置时间（10~25ms），这边数值根据各个芯片不同设置不同 */
#define KEY_DELAY_TIME		2000000



/** 按键定义 **/
typedef enum 
{  
	KEY_FUNCTION = 0,	 
	KEY_BIT = 1,
	KEY_ADD = 2,  //Tamper
	KEY_START = 3   //Wakeup
} Button_TypeDef;



//extern u8 g_FunState;


u8 KeyScan(void);
void KeyDelay(void);
void KeyFun(void);
void KeyBit(void);
void KeyAdd(void);
void KeyStart(void);
void KEY_Init(void);
void KEY_Configure(Button_TypeDef Button);
void StartTimeOver(void);





#ifdef __cplusplus
}
#endif

#endif


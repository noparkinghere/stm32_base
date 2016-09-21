#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"



#ifdef __cplusplus
extern "C" {
#endif	



/* LED灯相关定义 */
#define LED_NUM                         4                       /*STM32神舟王439IGT的LED数量*/

/*LED使用的GPIO管脚*/
#define LED1_RCC	RCC_AHB1Periph_GPIOF
#define LED1_PORT	GPIOF
#define LED1_PIN	GPIO_Pin_10

#define LED2_RCC	RCC_AHB1Periph_GPIOF
#define LED2_PORT	GPIOF
#define LED2_PIN	GPIO_Pin_9

#define LED3_RCC	RCC_AHB1Periph_GPIOF
#define LED3_PORT	GPIOF
#define LED3_PIN	GPIO_Pin_8

#define LED4_RCC	RCC_AHB1Periph_GPIOI
#define LED4_PORT	GPIOF
#define LED4_PIN	GPIO_Pin_7


#define LED1_OFF()			GPIO_SetBits(LED1_PORT, LED1_PIN)
#define LED2_OFF()			GPIO_SetBits(LED2_PORT, LED2_PIN)
#define LED3_OFF()			GPIO_SetBits(LED3_PORT, LED3_PIN)
#define LED4_OFF()			GPIO_SetBits(LED4_PORT, LED4_PIN)

#define LED1_ON()			GPIO_ResetBits(LED1_PORT, LED1_PIN)
#define LED2_ON()			GPIO_ResetBits(LED2_PORT, LED2_PIN)
#define LED3_ON()			GPIO_ResetBits(LED3_PORT, LED3_PIN)
#define LED4_ON()			GPIO_ResetBits(LED4_PORT, LED4_PIN)


/** 按键定义 **/
typedef enum 
{  
	LED1 = 0,	 
	LED2 = 1,
	LED3 = 2,  //Tamper
	LED4 = 3   //Wakeup
} LED_TypeDef;


/* 常量申明 */
extern const uint32_t LED_CLK[LED_NUM];
extern GPIO_TypeDef * LED_PORT[LED_NUM]; 
extern const uint16_t LED_PIN[LED_NUM]; 


void LedTurnOffALL(void);
void LedTurnOnALL(void);
void LED_Init(void);
void LedBlink(GPIO_TypeDef *port, uint16_t pin);
void LED_Configure(LED_TypeDef led);
void LED_TurnOn(u8 led);
void LED_TurnOff(u8 led);


#ifdef __cplusplus
}
#endif

#endif

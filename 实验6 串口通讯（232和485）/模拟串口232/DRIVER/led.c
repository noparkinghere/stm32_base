#include "led.h"


/** Default config for LED GPIO init structure. */
#define LED_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_OUT,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}

/* ��Ϊ������ʹ�� */
const uint32_t LED_CLK[LED_NUM] = {LED1_RCC, LED2_RCC, LED3_RCC, LED4_RCC};
GPIO_TypeDef* LED_PORT[LED_NUM] = {LED1_PORT, LED2_PORT, LED3_PORT, LED4_PORT}; 
const uint16_t LED_PIN[LED_NUM] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN}; 



/* Turn Off All LEDs */
void LedTurnOffALL(void)
{
	LED1_OFF();
	LED2_OFF();
	LED3_OFF();
	LED4_OFF();
}

/* Turn Off Select LED */
void LedTurnOnALL(void)
{
	LED1_ON();
	LED2_ON();
	LED3_ON();
	LED4_ON();
}


void LedBlink(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_ToggleBits(port, pin);
}


/* ��ʼ��PF7-PF10Ϊled�ڣ�LED IO��ʼ�� */
void LED_Init(void)
{    	 
	LED_Configure(LED1);
	LED_Configure(LED2);
	LED_Configure(LED3);
	LED_Configure(LED4);

	LedTurnOffALL();	//������IO�ں������е�Ϩ��
}


void LED_Configure(LED_TypeDef led)
{

	RCC_AHB1PeriphClockCmd(LED_CLK[led], ENABLE);//ʹ��ʱ��

	/* ����GPIO������һ��Ĭ�ϲ���Ϊ��Ӧ���ã���������˴�������ã�������Ҫ�����޸��������� */
	GPIO_InitTypeDef  GPIO_InitStructure = LED_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = LED_PIN[led];
	GPIO_Init(LED_PORT[led], &GPIO_InitStructure);//��ʼ��
}

void LED_TurnOn(u8 led)
{
	GPIO_ResetBits(LED_PORT[led], LED_PIN[led]);
}

void LED_TurnOff(u8 led)
{
	GPIO_SetBits(LED_PORT[led], LED_PIN[led]);
}



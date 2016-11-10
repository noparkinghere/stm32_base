/*******************************************************
 * ����1Ϊ���ܰ��������ϵ��л�������������
 * ����2Ϊѡ��λ��������ÿ������λ����ѡ��
 * ����3Ϊ�Ӱ�������ÿ��λ���мӣ��ð���������������
 * ����4Ϊ�������������°���4�������������ֵ���������š�
 *******************************************************/

#include "key.h"
#include "exti.h"



#define VALUE_NUM 		2
#define TIME_BIT_NUM	2
#define START_FUN		2		//start�����Ĺ���


/** Default config for KEY GPIO init structure. */
#define KEY_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_IN,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}


/* ��Ϊ������ʹ�� */
GPIO_TypeDef* BUTTON_PORT[KEY_NUM] = {KEY1_PORT, KEY2_PORT, KEY3_PORT, KEY4_PORT}; 
const uint32_t BUTTON_CLK[KEY_NUM] = {KEY1_RCC, KEY2_RCC, KEY3_RCC, KEY4_RCC};
const uint16_t BUTTON_PIN[KEY_NUM] = {KEY1_PIN, KEY2_PIN, KEY3_PIN, KEY4_PIN}; 


u8 g_FunState = 0;
u8 g_Bit = 0;



/* ������ʼ������������CPU��IO���ţ��������ʱ�� */
void KEY_Init(void)
{
	KEY_Configure(KEY_FUNCTION);       			
	KEY_Configure(KEY_BIT);       			
	KEY_Configure(KEY_ADD);       			
	KEY_Configure(KEY_START);       			

	EXTIX_KeyInit(KEY_FUNCTION);       			
	EXTIX_KeyInit(KEY_BIT);       			
	EXTIX_KeyInit(KEY_ADD);       			
	EXTIX_KeyInit(KEY_START);  
}


/* ������ð����������� */
void KEY_Configure(Button_TypeDef Button)
{

	/* ��߷ֿ�����ʹ�ܳ�ʼ���ĺô��Ǹ�����ÿ��ֻʹ����Ҫ�Ŀ��Խ����ܺĵ� */
//	RCC_AHB1PeriphClockCmd(KEY1_RCC | KEY2_RCC | KEY3_RCC | KEY4_RCC, ENABLE);

	/* Configure KEY1 Button */
	RCC_AHB1PeriphClockCmd(BUTTON_CLK[Button], ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure = KEY_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
	GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

}


/* �жϰ���״̬�����ҵõ���ֵ */
u8 KeyScan(void)
{
 /* ��������ʱΪ�͵�ƽ���������������ı�ָʾ��״̬ */
 
 	if(!KEY1() || !KEY2() || !KEY3() || !KEY4())
	{
		if(!KEY1())
        {   
            /* �ӳ�ȥ�� */
            KeyDelay();
            if(!KEY1())
            {   
				LED1_ON();   //������Ӧ��LED��
                
				while(!KEY1());	 // �ȴ������ͷ�
               
				KeyDelay(); // �ӳ�ȥ��
            }
        }
		else if(!KEY2())
        {   
            /* �ӳ�ȥ�� */
            KeyDelay();
            if(!KEY2())
            {   
				LED2_ON();   //������Ӧ��LED��
                
				while(!KEY2());	 // �ȴ������ͷ�
               
				KeyDelay(); // �ӳ�ȥ��
            }
        }
		else if(!KEY3())
        {   
            /* �ӳ�ȥ�� */
            KeyDelay();
            if(!KEY3())
            {   
				LED3_ON();   //������Ӧ��LED��
                
				while(!KEY3());	 // �ȴ������ͷ�
               
				KeyDelay(); // �ӳ�ȥ��
            }
        }		
		else if(!KEY4())
        {   
            /* �ӳ�ȥ�� */
            KeyDelay();
            if(!KEY4())
            {   
				LED1_ON();   //������Ӧ��LED��
                
				while(!KEY4());	 // �ȴ������ͷ�
               
				KeyDelay(); // �ӳ�ȥ��
            }
        }		
	}
    
 	return 0;// �ް�������
	
}

/* ���ʵ�ֵİ���������ʱ */
void KeyDelay(void)
{
	u32 cnt = KEY_DELAY_TIME;
	
	for (; cnt != 0; cnt--)
	;
}


/* ����1����ʱ����ز��� */
void KeyFun(void)
{
	LedTurnOffALL();							
	LED1_ON();   //������Ӧ��LED��	

	
}

/* ����2����ʱ����ز��� */
void KeyBit(void)
{
	LedTurnOffALL();
	LED2_ON();   //������Ӧ��LED��	

}


/* ����3����ʱ����ز��� */
void KeyAdd(void)
{
	LedTurnOffALL();
	LED3_ON();   //������Ӧ��LED��
}


/* ����4����ʱ����ز��� */
void KeyStart(void)
{
	LedTurnOffALL();
	LED4_ON();   //������Ӧ��LED��

}





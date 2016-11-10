/*******************************************************
 * 按键1为功能按键，不断地切换各个功能设置
 * 按键2为选择位按键，对每个数据位进行选择
 * 按键3为加按键，对每个位进行加，该按键具有连按功能
 * 按键4为启动按键，按下按键4则读入所有设置值，启动阀门。
 *******************************************************/

#include "key.h"
#include "exti.h"



#define VALUE_NUM 		2
#define TIME_BIT_NUM	2
#define START_FUN		2		//start按键的功能


/** Default config for KEY GPIO init structure. */
#define KEY_GPIO_DEFAULT							\
{													\
	GPIO_Pin_0,										\
	GPIO_Mode_IN,									\
	GPIO_Speed_100MHz,								\
	GPIO_OType_PP,									\
	GPIO_PuPd_UP									\
}


/* 作为常量来使用 */
GPIO_TypeDef* BUTTON_PORT[KEY_NUM] = {KEY1_PORT, KEY2_PORT, KEY3_PORT, KEY4_PORT}; 
const uint32_t BUTTON_CLK[KEY_NUM] = {KEY1_RCC, KEY2_RCC, KEY3_RCC, KEY4_RCC};
const uint16_t BUTTON_PIN[KEY_NUM] = {KEY1_PIN, KEY2_PIN, KEY3_PIN, KEY4_PIN}; 


u8 g_FunState = 0;
u8 g_Bit = 0;



/* 按键初始化函数，配置CPU的IO引脚，开启相关时钟 */
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


/* 逐个配置按键基本设置 */
void KEY_Configure(Button_TypeDef Button)
{

	/* 这边分开进行使能初始化的好处是更加灵活，每次只使能需要的可以降低能耗等 */
//	RCC_AHB1PeriphClockCmd(KEY1_RCC | KEY2_RCC | KEY3_RCC | KEY4_RCC, ENABLE);

	/* Configure KEY1 Button */
	RCC_AHB1PeriphClockCmd(BUTTON_CLK[Button], ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure = KEY_GPIO_DEFAULT;
	GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
	GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

}


/* 判断按键状态，并且得到键值 */
u8 KeyScan(void)
{
 /* 按键按下时为低电平，如果按键按下则改变指示灯状态 */
 
 	if(!KEY1() || !KEY2() || !KEY3() || !KEY4())
	{
		if(!KEY1())
        {   
            /* 延迟去抖 */
            KeyDelay();
            if(!KEY1())
            {   
				LED1_ON();   //点亮对应的LED灯
                
				while(!KEY1());	 // 等待按键释放
               
				KeyDelay(); // 延迟去抖
            }
        }
		else if(!KEY2())
        {   
            /* 延迟去抖 */
            KeyDelay();
            if(!KEY2())
            {   
				LED2_ON();   //点亮对应的LED灯
                
				while(!KEY2());	 // 等待按键释放
               
				KeyDelay(); // 延迟去抖
            }
        }
		else if(!KEY3())
        {   
            /* 延迟去抖 */
            KeyDelay();
            if(!KEY3())
            {   
				LED3_ON();   //点亮对应的LED灯
                
				while(!KEY3());	 // 等待按键释放
               
				KeyDelay(); // 延迟去抖
            }
        }		
		else if(!KEY4())
        {   
            /* 延迟去抖 */
            KeyDelay();
            if(!KEY4())
            {   
				LED1_ON();   //点亮对应的LED灯
                
				while(!KEY4());	 // 等待按键释放
               
				KeyDelay(); // 延迟去抖
            }
        }		
	}
    
 	return 0;// 无按键按下
	
}

/* 软件实现的按键防抖延时 */
void KeyDelay(void)
{
	u32 cnt = KEY_DELAY_TIME;
	
	for (; cnt != 0; cnt--)
	;
}


/* 按键1按下时的相关操作 */
void KeyFun(void)
{
	LedTurnOffALL();							
	LED1_ON();   //点亮对应的LED灯	

	
}

/* 按键2按下时的相关操作 */
void KeyBit(void)
{
	LedTurnOffALL();
	LED2_ON();   //点亮对应的LED灯	

}


/* 按键3按下时的相关操作 */
void KeyAdd(void)
{
	LedTurnOffALL();
	LED3_ON();   //点亮对应的LED灯
}


/* 按键4按下时的相关操作 */
void KeyStart(void)
{
	LedTurnOffALL();
	LED4_ON();   //点亮对应的LED灯

}





/****************************** (C) COPYRIGHT 2016 *******************************
 *
 *  	���ܣ�MCUʱ��������غ������жϷ�����
 *		ע�⣺�������жϵ���ع���
 * 
 ********************************************************************************/

#include "timer.h"
#include "led.h"
#include "key.h"

#define OVER_TIME 300		// ����ʱ�䣺300s



#define TIMER_NVIC_DEFAULT				\
{										\
	TIM2_IRQn,							\
	0xf,								\
	0xf,								\
	ENABLE,								\
}



#define TIM_INIT_DEFAULT				\
{										\
	4499,								\
	TIM_CounterMode_Up,					\
	9999,								\
	TIM_CKD_DIV1,						\
	0x00								\
}


TIM_TypeDef * TIMER_NUM[4] = {TIM2, TIM3, TIM4, TIM5};


void TIM_Init(void)
{
	/* t=10000*1/(180M/4*2/9000) */
	TIM_Configure(TIMER3, 10000, 9000);
	
}



/***************************************************************
	ͨ�ö�ʱ���жϳ�ʼ��
	arr���Զ���װֵ��
	psc��ʱ��Ԥ��Ƶ��
	��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
	Ft=��ʱ������Ƶ��,��λ:Mhz
	����ʹ�õ��Ƕ�ʱ��3!
***************************************************************/
void TIM_Configure(TIMER_TypeDef num, u16 arr,u16 psc)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  // ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = TIM_INIT_DEFAULT;
	
	/* ��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����arr�κ�Ϊarr-1*/
	TIM_TimeBaseInitStructure.TIM_Period = arr - 1;
	
	/* �������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1 */
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;  //��ʱ����Ƶ
	TIM_TimeBaseInit(TIMER_NUM[num], &TIM_TimeBaseInitStructure);//��ʼ��TIMER_NUM[num]
	TIM_ITConfig(TIMER_NUM[num], TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIMER_NUM[num], ENABLE); //ʹ�ܶ�ʱ��3
	
	
	/* ��ʱ���жϹ��ܣ�������Ҫ���Ե�����Ϊ���� */
	NVIC_InitTypeDef NVIC_InitStructure = TIMER_NVIC_DEFAULT;
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_Init(&NVIC_InitStructure);
	
}

/* ��ʱ��3�жϷ����� */
void TIM3_IRQHandler(void)
{
	static u16 cnt = 0;
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		if (cnt == OVER_TIME-1)		// �趨ʱ��ΪOVER_TIME��
		{
			LedTurnOffALL();	// ���еƵ�������ʾ�û���������
			cnt = 0;
			StartTimeOver();		// �û��������ݣ��л�����ģʽ
			
		}
		else 
		{
			cnt++;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}

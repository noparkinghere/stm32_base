#ifndef __EXTI_H
#define __EXIT_H
	 
#include "sys.h"  	
#include "key.h"

#ifdef __cplusplus
extern "C" {
#endif	


#include "stm32f4xx.h"





void EXTIX_Init(void);	 					    
void NVIC_GroupConfig(void);
void EXTIX_KeyInit(Button_TypeDef Button);	//�����ⲿ�жϳ�ʼ��		






#ifdef __cplusplus
}
#endif


#endif


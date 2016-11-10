#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"



#ifdef __cplusplus
extern "C" {
#endif	


extern u8 g_TimeOut;



/** ´®¿Ú¶¨Òå **/
typedef enum 
{  
	TIMER2 = 0,
	TIMER3 = 1,
	TIMER4 = 2,
	TIMER5 = 3
} TIMER_TypeDef;



extern TIM_TypeDef * TIMER_NUM[4];

void TIM_Configure(TIMER_TypeDef num, u16 arr,u16 psc);
void TIM_Init(void);
void TIM3_Init_Ctrl(u8 state);

#ifdef __cplusplus
}
#endif


#endif

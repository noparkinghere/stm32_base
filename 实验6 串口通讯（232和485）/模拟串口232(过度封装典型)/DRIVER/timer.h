#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"



#ifdef __cplusplus
extern "C" {
#endif	



/** ´®¿Ú¶¨Òå **/
typedef enum 
{  
	TIMER2 = 0,
	TIMER3 = 1,
	TIMER4 = 2,
	TIMER5 = 3
} TIMER_TypeDef;





void TIM_Configure(TIMER_TypeDef num, u16 arr,u16 psc);
void TIM_Init(void);


#ifdef __cplusplus
}
#endif


#endif

#ifndef __COM_H
#define __COM_H
#include "stm32f4xx.h"



#ifdef __cplusplus
extern "C" {
#endif	




/** 串口定义 **/
typedef enum 
{  
	COM_USART1 = 0,	 		//通讯方式1
	COM_USART3 = 1
} COM_TypeDef;





void COM_Init(void);
void USART_Configure(COM_TypeDef usart, u32 bound);



#ifdef __cplusplus
}
#endif

#endif


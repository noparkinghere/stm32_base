#ifndef __EXTI_H
#define __EXIT_H
	 
#include "sys.h"  	
#include "key.h"

#ifdef __cplusplus
extern "C" {
#endif	


#include "stm32f4xx.h"


#define RX1_PORT_SOURCE		GPIO_PortSourceGPIOA
#define RX1_PIN_SOURCE		GPIO_PinSource10
#define RX1_EXTI_LINE		EXTI_Line10
#define RX1_EXTI_IRQn 		EXTI15_10_IRQn



void EXTIX_KeyInit(void);






#ifdef __cplusplus
}
#endif


#endif


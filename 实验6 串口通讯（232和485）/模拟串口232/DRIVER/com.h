#ifndef __COM_H
#define __COM_H
#include "stm32f4xx.h"


#ifdef __cplusplus
extern "C" {
#endif	



#define UART_TIME_OUT (8000)

extern u8 point;


void COM_Init(void);
void my_printf(char * str, ...);
void Xprintf(void);

#ifdef __cplusplus
}
#endif

#endif


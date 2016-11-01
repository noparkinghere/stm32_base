#ifndef __COM_H
#define __COM_H
#include "stm32f4xx.h"



#ifdef __cplusplus
extern "C" {
#endif	







void COM_Init(void);
void USART_Configure(void);

void UART_SendData(u8 data);
void delay_com(void);
void my_printf(char * str, ...);


#ifdef __cplusplus
}
#endif

#endif


#ifndef __TEST_H
#define __TEST_H


#include "stm32f4xx.h"
#include "sys.h"
#include "com.h"




#ifdef __cplusplus
extern "C" {
#endif	


#define SIGNALPORT			gpioPortB
#define SIGNALPIN			7

/* ³õÊ¼»¯ioÒý½Å£¬ÈÃLEDÏ¨Ãð */
#define SIGNALTESTINIT() 	GPIO_PinModeSet(SIGNALPORT, SIGNALPIN, gpioModePushPull, 0)
#define SIGNALTEST() 		GPIO_PinOutToggle(SIGNALPORT, SIGNALPIN)
#define SIGNALON() 			(GPIO->P[SIGNALPORT].DOUTSET = 1 << SIGNALPIN)
#define SIGNALOFF() 		(GPIO->P[SIGNALPORT].DOUTCLR = 1 << SIGNALPIN)

//#define SIGNALON() 		GPIO_PinOutSet(gpioPortB, SIGNALPIN)
//#define SIGNALOFF() 		GPIO_PinOutClear(gpioPortB, SIGNALPIN)

//#define SIGNALON() 			GPIO_PinOutToggle(gpioPortB, SIGNALPIN)
//#define SIGNALOFF() 		GPIO_PinOutToggle(gpioPortB, SIGNALPIN)



#ifdef __cplusplus
}
#endif


#endif

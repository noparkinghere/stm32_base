#ifndef __BEEP_H
#define __BEEP_H	 

#include "sys.h" 



#ifdef __cplusplus
extern "C" {
#endif	


#define BEEP PFout(6)	// 位带操作方便蜂鸣器控制IO

void BEEP_Init(void);//初始化	


#ifdef __cplusplus
}
#endif

	 				    
#endif

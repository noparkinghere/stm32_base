#ifndef __BEEP_H
#define __BEEP_H	 

#include "sys.h" 



#ifdef __cplusplus
extern "C" {
#endif	


#define BEEP PFout(6)	// λ�������������������IO

void BEEP_Init(void);//��ʼ��	


#ifdef __cplusplus
}
#endif

	 				    
#endif

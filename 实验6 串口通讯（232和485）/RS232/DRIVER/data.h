#ifndef __DATA_H
#define __DATA_H

#include "stm32f4xx.h"




#ifdef __cplusplus
extern "C" {
#endif	


#define STRUBASEVALUE_LEN	6
#define STRUTIMEVALUE_LEN	2

typedef struct 
{
	float Value;
	u8 Bit;
}StruBaseValue;

typedef struct 
{
	u8 Value;
	u8 Bit;
}StruTimeValue;


extern StruBaseValue g_OldValue;
extern StruTimeValue g_Time;
extern StruBaseValue g_NewValue;
extern float g_StdOldValue;
extern float g_StdNewValue;
extern u8 g_DiagnoseRes;
extern float g_CalDeviation;


void InitData(void);
u32 FunMultiBit(u8 Bit);
void ValueBitAdd(float *Value, u8 Bit);
void TimeBitAdd(u8 *Value, u8 Bit);
u8 GetBitValue(float Value, u8 Bit);
u8 GetBitTime(u16 Value, u8 Bit);
void CalDeviation(void);
u8 DiagnoseData(void);
void ComPrint(void);
void GetStdData(void);


#ifdef __cplusplus
}
#endif

#endif

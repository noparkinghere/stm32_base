#include "data.h"
#include "test.h"
#include "com.h"
#include <stdio.h>
#include <math.h>



#define TIMEOUT_VALUE	100
#define STD_VALUE	0.01

StruBaseValue g_OldValue;
StruTimeValue g_Time;
StruBaseValue g_NewValue;

float g_StdOldValue;
float g_StdNewValue;
u8 g_DiagnoseRes;
float g_CalDeviation;

/* 将这些全局的数据进行初始化，有个固定值 */
void InitData(void)
{
	g_OldValue.Value = 0.0;
	g_OldValue.Bit = 0;
	g_NewValue.Value = 0.0;
	g_NewValue.Bit = 0;
	g_Time.Value = 5;
	g_Time.Bit = 0;
}

/* 按下按键后，新老数据内容每次自动增加1 */
void ValueBitAdd(float *Value, u8 Bit)
{
	*Value += FunMultiBit(Bit) * 0.01;		//每次将某位值加1

	if (GetBitValue(*Value, Bit) == 0)		//判断是否进位了
	{
		*Value -= FunMultiBit(Bit) * 0.1;	//将进位的值减去
	}

}


/* 按下按键后，时间每次自动增加1 */
void TimeBitAdd(u8 *Value, u8 Bit)
{
	*Value += FunMultiBit(Bit);
	
	if (GetBitTime(*Value, Bit) == 0)		//判断是否进位了
	{
		*Value -= FunMultiBit(Bit) * 10;	//将进位的值减去
	}
	*Value %= TIMEOUT_VALUE;

}


/* 仅用于位数值换算 */
u32 FunMultiBit(u8 Bit)
{
	u32 res = 1;
	for (; Bit > 0; Bit--)
	{
		res *= 10;
	}
	return res;
}


/* 获取新老value值的第bit+1位的值 */
u8 GetBitValue(float Value, u8 Bit)
{
	u32 tmp = round(Value*100);		//注意浮点型转换时四舍五入，否则会出错	
	
	for (; Bit > 0; Bit--)
	{
		tmp /= 10;
	}
	
	return (tmp % 10);
}


/* 获取Time值的第bit+1位的值 */
u8 GetBitTime(u16 Value, u8 Bit)
{
	for (; Bit > 0; Bit--)
	{
		Value /= 10;
	}
	
	return (Value % 10);
}

/* 判定是否合格 */
u8 DiagnoseData(void)
{
	if (g_CalDeviation < (float)STD_VALUE && g_CalDeviation > -(float)STD_VALUE)
	{
		printf("合格\n");
		return 0;
	}
	else
	{
		printf("不合格\n");	
		return 1;
	}

}


/* 计算误差值 */
void CalDeviation(void)
{
	g_CalDeviation = (g_NewValue.Value-g_OldValue.Value) / (g_StdNewValue-g_StdOldValue) - (float)1.0;

	printf("Ratio : %.2f\n", g_CalDeviation);	

}

void ComPrint(void)
{
	printf("OldValue:%.2f\t", g_OldValue.Value);
	printf("Time:%d\t", g_Time.Value);
	printf("OldValue:%.2f\n", g_NewValue.Value);
}

/* 获取标准数据 */
//void GetStdData(void)
//{
//	static u8 c = 0;

//	if (c == 0)
//	{
//		scanf("%f", &g_StdOldValue);
//		c++;
//	}
//	else 
//	{
//		scanf("%f", &g_StdNewValue);
//		c = 0;
//	}
//}

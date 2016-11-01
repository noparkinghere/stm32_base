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

/* ����Щȫ�ֵ����ݽ��г�ʼ�����и��̶�ֵ */
void InitData(void)
{
	g_OldValue.Value = 0.0;
	g_OldValue.Bit = 0;
	g_NewValue.Value = 0.0;
	g_NewValue.Bit = 0;
	g_Time.Value = 5;
	g_Time.Bit = 0;
}

/* ���°�����������������ÿ���Զ�����1 */
void ValueBitAdd(float *Value, u8 Bit)
{
	*Value += FunMultiBit(Bit) * 0.01;		//ÿ�ν�ĳλֵ��1

	if (GetBitValue(*Value, Bit) == 0)		//�ж��Ƿ��λ��
	{
		*Value -= FunMultiBit(Bit) * 0.1;	//����λ��ֵ��ȥ
	}

}


/* ���°�����ʱ��ÿ���Զ�����1 */
void TimeBitAdd(u8 *Value, u8 Bit)
{
	*Value += FunMultiBit(Bit);
	
	if (GetBitTime(*Value, Bit) == 0)		//�ж��Ƿ��λ��
	{
		*Value -= FunMultiBit(Bit) * 10;	//����λ��ֵ��ȥ
	}
	*Value %= TIMEOUT_VALUE;

}


/* ������λ��ֵ���� */
u32 FunMultiBit(u8 Bit)
{
	u32 res = 1;
	for (; Bit > 0; Bit--)
	{
		res *= 10;
	}
	return res;
}


/* ��ȡ����valueֵ�ĵ�bit+1λ��ֵ */
u8 GetBitValue(float Value, u8 Bit)
{
	u32 tmp = round(Value*100);		//ע�⸡����ת��ʱ�������룬��������	
	
	for (; Bit > 0; Bit--)
	{
		tmp /= 10;
	}
	
	return (tmp % 10);
}


/* ��ȡTimeֵ�ĵ�bit+1λ��ֵ */
u8 GetBitTime(u16 Value, u8 Bit)
{
	for (; Bit > 0; Bit--)
	{
		Value /= 10;
	}
	
	return (Value % 10);
}

/* �ж��Ƿ�ϸ� */
u8 DiagnoseData(void)
{
	if (g_CalDeviation < (float)STD_VALUE && g_CalDeviation > -(float)STD_VALUE)
	{
		printf("�ϸ�\n");
		return 0;
	}
	else
	{
		printf("���ϸ�\n");	
		return 1;
	}

}


/* �������ֵ */
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

/* ��ȡ��׼���� */
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

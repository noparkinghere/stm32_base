#ifndef __SYS_H
#define __SYS_H
#include "stm32f4xx.h"



#ifdef __cplusplus
extern "C" {
#endif																	    
	 
/*******************************************************
 * λ������,ʵ��51���Ƶ�GPIO���ƹ���
 * ����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
 * IO�ڲ����궨�壬������M3��M4�ں�
 * �����Ӧ�ĵ�ַ����ȥ�鿴GPIOX�ṹ���ж�Ӧ��Ա
 ******************************************************/
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr & 0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

/* IO�ڵ�ַӳ��,��ƱȽ�ͨ�õ���ʽ���ձ�������stm32��оƬ */
#define GPIOA_ODR_Addr    ((uint32_t)&GPIOA->ODR) //0x40020020
#define GPIOB_ODR_Addr    ((uint32_t)&GPIOB->ODR) //0x40020420 
#define GPIOC_ODR_Addr    ((uint32_t)&GPIOC->ODR) 
#define GPIOD_ODR_Addr    ((uint32_t)&GPIOD->ODR) 
#define GPIOE_ODR_Addr    ((uint32_t)&GPIOE->ODR) 
#define GPIOF_ODR_Addr    ((uint32_t)&GPIOF->ODR) 
#define GPIOG_ODR_Addr    ((uint32_t)&GPIOG->ODR)     
#define GPIOH_ODR_Addr    ((uint32_t)&GPIOH->ODR)  
#define GPIOI_ODR_Addr    ((uint32_t)&GPIOI->ODR)   


#define GPIOA_IDR_Addr    ((uint32_t)&GPIOA->IDR)  //0x40020016
#define GPIOB_IDR_Addr    ((uint32_t)&GPIOB->IDR)
#define GPIOC_IDR_Addr    ((uint32_t)&GPIOC->IDR)
#define GPIOD_IDR_Addr    ((uint32_t)&GPIOD->IDR)
#define GPIOE_IDR_Addr    ((uint32_t)&GPIOE->IDR)
#define GPIOF_IDR_Addr    ((uint32_t)&GPIOF->IDR)
#define GPIOG_IDR_Addr    ((uint32_t)&GPIOG->IDR)
#define GPIOH_IDR_Addr    ((uint32_t)&GPIOH->IDR)  
#define GPIOI_IDR_Addr    ((uint32_t)&GPIOI->IDR)
 
/* IO�ڲ�����ֻ�Ե�һ��IO�ڣ�ȷ��n��ֵС��16! */
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 
#define PAoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOA_ODR_Addr,n)

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 
#define PBoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOB_ODR_Addr,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 
#define PCoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOC_ODR_Addr,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 
#define PDoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOD_ODR_Addr,n)

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����
#define PEoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOE_ODR_Addr,n)

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����
#define PFoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOF_ODR_Addr,n)

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����
#define PGoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOG_ODR_Addr,n)

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //��� 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //����
#define PHoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOH_ODR_Addr,n)

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //��� 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //����
#define PIoutAdd(n)		(volatile unsigned long  *)BITBAND(GPIOI_ODR_Addr,n)


/**************************************************************************************/

#define DELAY_ABOUT_200MS 0x3FFFFF


/* GPIO settings */



/**************************************************************************************/

void Delay100msSoft(void);	 // ����׼��ʱ����Լ0.2s
void delay_init(void);
void NVIC_Configuration(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void DelayTest(u8 cnt);


#ifdef __cplusplus
}
#endif

#endif

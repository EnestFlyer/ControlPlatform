#ifndef _USART_H_
#define _USART_H_

#include "../../SYSTEM/sys/sys.h"

#define BUF_USART1 100
#define BUF_USART2 100
#define BUF_USART3 100
#define BUF_USART4 100
#define BUF_USART5 100


#define Rx1Length 100
#define Rx2Length 100
#define Rx3Length 100
#define Rx4Length 100
#define Rx5Length 100

extern u8 Rx1Buf[Rx1Length];     //���ջ���,���USART_REC_LEN���ֽ�.	
extern u8 Rx2Buf[Rx2Length];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u8 Rx3Buf[Rx3Length];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u8 Rx4Buf[Rx4Length];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u8 Rx5Buf[Rx5Length];     //���ջ���,���USART_REC_LEN���ֽ�.

extern u16 Rx1Flag;       //����״̬���	  
extern u16 Rx2Flag;       //����״̬���	  
extern u16 Rx3Flag;       //����״̬���	  
extern u16 Rx4Flag;       //����״̬���	  
extern u16 Rx5Flag;       //����״̬���	  

extern void USART1_Init(u32 bound);
extern void USART2_Init(u32 bound);
extern void USART3_Init(u32 bound);
extern void USART4_Init(u32 bound);
extern void USART5_Init(u32 bound);

extern void printf1(char *fmt, ...);
extern void printf2(char *fmt, ...);
extern void printf3(char *fmt, ...);


#endif


#ifndef _SPI_H_
#define _SPI_H_

#include "../../SYSTEM/sys/sys.h"
						  
void SPI1_Init(void);			 //��ʼ��SPI��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�

#endif

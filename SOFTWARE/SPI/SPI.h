#ifndef _SPI_H_
#define _SPI_H_

#include "../../SYSTEM/sys/sys.h"
						  
void SPI1_Init(void);			 //初始化SPI口
void SPI1_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI总线读写一个字节

#endif

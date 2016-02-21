////////////////////////////////////////////////////////////////
//用USART 3做无线串口
//
////////////////////////////////////////////////////////////////
#include "../../SOFTWARE/PlaneAuto/PlaneAuto.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../HARDWARE/MCP41010/MCP41010.h"
#include "../../SYSTEM/delay/delay.h"
#include  "string.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"

void Plane_UNLOCK()
{
	SetChannelValue(__ACCE,1100);
	SetChannelValue(__YAW,1950);
	SetChannelValue(__ROLL,1100);
	SetChannelValue(__PITCH,1100);
}


void Plane_LOCK()
{
	SetChannelValue(__ACCE,1100);
	SetChannelValue(__YAW,1100);
	SetChannelValue(__ROLL,1950);
	SetChannelValue(__PITCH,1100);
}

void Plane_LAND()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////
extern u16 USART_RX3_STA;
extern u8 Rx3Buf[Rx3Length];
u8 FlagOfCatch=0;

u8 Plane_LAUNCH()
{
	int len=0;
	int t=0;
	u8 flag=0;//接满标志，置位为接满
	u8 temp[100]={0};//缓冲池
	char command='O';//命令字
	
	while(1)
	{
		if(USART_RX3_STA&0x8000)
		{					   
			len=USART_RX3_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				temp[t]=Rx3Buf[t];
				while((USART3->SR&0X40)==0);//等待发送结束
			}
			flag=1;
			USART_RX3_STA=0;
		}
		
		
		
		
		
	}

	return 1;
}


float CurrentOut_X=0;	//这次输出的值
float LastOut_X=0;	//上次输出的值
float Kp_X=0;	//比例系数
float Ki_X=0;	//积分系数
float Kd_X=0;	//微分系数
float ErrCurrent_X=0;	//当次误差
float ErrLast1_X=0;	//上一次误差
float ErrLast2_X=0;	//上两次误差

u8 Plane_PID(int X_value,int Y_value,int D_val)//也要对距离进行pid调控
{
	int bias_X=0;
	float pErr_X=0;
	float iErr_X=0;
	float dErr_X=0;
	
	ErrCurrent_X=X_value;
	pErr_X=ErrCurrent_X-ErrLast1_X;//比例误差(等于当前误差减去前一次的误差)
	iErr_X=ErrCurrent_X;//积分误差(等于当前误差值)
	dErr_X=ErrCurrent_X-ErrLast1_X*2+ErrLast2_X;//微分误差(等于当前误差减去前一次2倍误差再加上前两次的误差)

	ErrLast2_X=ErrLast1_X;
	ErrLast1_X=ErrCurrent_X;
	
	CurrentOut_X=LastOut_X+Kp_X*pErr_X+Ki_X*iErr_X+Kd_X*dErr_X;
	LastOut_X=CurrentOut_X;
	SetChannelValue(__YAW,1500);
	return 1;
}
//暂时只对X进行调控，既是只有yaw


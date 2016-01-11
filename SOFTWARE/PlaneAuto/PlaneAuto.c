////////////////////////////////////////////////////////////////
//��USART 3�����ߴ���
//
////////////////////////////////////////////////////////////////
#include "../../SOFTWARE/PlaneAuto/PlaneAuto.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../HARDWARE/MCP41010/MCP41010.h"
#include "../../SYSTEM/delay/delay.h"
#include  "string.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"


void Plane_Up(long UpSpeed)
{
	
}//���ţ�UpSpeed���������ٶ�
void Plane_Down(long DownSpeed)
{
	
}//���ţ�DownSpeed�����½��ٶ�
void Plane_Yaw(long YawSpeed)
{
	
}//ƫ����YawSpeedƫ���ٶ� 
void Plane_Roll(long RollSpeed)
{	
	
}//������RollSpeed�����ٶ�/������
void Plane_Pitch(long PitchSpeed)
{
	
}//�����ǣ�PitchSpeed/ǰ����


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
	u8 flag=0;//������־����λΪ����
	u8 temp[100]={0};//�����
	char command='O';//������
	
	SetChannelValue(__ACCE,1600);//��������
	delay_ms(1000);delay_ms(1000);
	SetChannelValue(__YAW,1600);
	while(!FlagOfCatch)
	{
		if(USART_RX3_STA&0x8000)
		{					   
			len=USART_RX3_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(t=0;t<len;t++)
			{
				temp[t]=Rx3Buf[t];
				while((USART3->SR&0X40)==0);//�ȴ����ͽ���
			}
			flag=1;
			USART_RX3_STA=0;
		}
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='S')
			{
				printf1("S=%d\n",ValueOfMea(temp));//for test
				FlagOfCatch=ValueOfMea(temp);
			}
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
	}
	SetChannelValue(__PITCH,1600);
	SetChannelValue(__ACCE,1500);
	return 1;
}



u8 Plane_PID(int X_value,int Y_value)
{
	if((X_value<THE_ERR_X)&&(Y_value<THE_ERR_Y))
	{
		
	}//�ڷ�ΧȦ֮��,��С�ٶ�����
	else
	{
		
	}//�ڷ�ΧȦ֮�⣬�Դ��ٶ�����
	return 1;
}


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
	
	while(1)
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
		
		
		
		
		
	}

	return 1;
}


float CurrentOut_X=0;	//��������ֵ
float LastOut_X=0;	//�ϴ������ֵ
float Kp_X=0;	//����ϵ��
float Ki_X=0;	//����ϵ��
float Kd_X=0;	//΢��ϵ��
float ErrCurrent_X=0;	//�������
float ErrLast1_X=0;	//��һ�����
float ErrLast2_X=0;	//���������

u8 Plane_PID(int X_value,int Y_value,int D_val)//ҲҪ�Ծ������pid����
{
	int bias_X=0;
	float pErr_X=0;
	float iErr_X=0;
	float dErr_X=0;
	
	ErrCurrent_X=X_value;
	pErr_X=ErrCurrent_X-ErrLast1_X;//�������(���ڵ�ǰ����ȥǰһ�ε����)
	iErr_X=ErrCurrent_X;//�������(���ڵ�ǰ���ֵ)
	dErr_X=ErrCurrent_X-ErrLast1_X*2+ErrLast2_X;//΢�����(���ڵ�ǰ����ȥǰһ��2������ټ���ǰ���ε����)

	ErrLast2_X=ErrLast1_X;
	ErrLast1_X=ErrCurrent_X;
	
	CurrentOut_X=LastOut_X+Kp_X*pErr_X+Ki_X*iErr_X+Kd_X*dErr_X;
	LastOut_X=CurrentOut_X;
	SetChannelValue(__YAW,1500);
	return 1;
}
//��ʱֻ��X���е��أ�����ֻ��yaw


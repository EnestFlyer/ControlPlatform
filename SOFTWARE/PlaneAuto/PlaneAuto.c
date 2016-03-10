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
#include "../../SOFTWARE/EXTI/exti.h"

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

void Plane_Init()
{
	//Ĭ�����ֶ�ģʽ������ҲҪ��ʼ����λ����ֵ
	ACCE_ORI=ORI_ENABLE;
	YAW_ORI=ORI_ENABLE;
	ROLL_ORI=ORI_ENABLE;
	PITCH_ORI=ORI_ENABLE;
		
	ACCE_MCU=MCU_DISABLE;
	YAW_MCU=MCU_DISABLE;
	ROLL_MCU=MCU_DISABLE;
	PITCH_MCU=MCU_DISABLE;
	
	SetChannelValue(__ACCE,1500);
	SetChannelValue(__YAW,1500);
	SetChannelValue(__PITCH,1500);
	SetChannelValue(__ROLL,1500);//�ɻ�ͨ��ֵ��ʼ��
	
}



//float CurrentOut_X = 0;	//��������ֵ
//float LastOut_X = 0;	//�ϴ������ֵ
//float Kp_X = 20;	//����ϵ��
//float Ki_X = 0.5;	//����ϵ��
//float Kd_X = 0.1;	//΢��ϵ��
//float ErrCurrent_X = 0;	//�������
//float ErrLast1_X = 0;	//��һ�����
//float ErrLast2_X = 0;	//���������

PID pid_X;
PID pid_Y;
PID pid_D;//����pid����


void PID_Init()
{
	pid_X.Kp = 10;
	pid_X.Ki = 0.016;
	pid_X.Kd = 0.2;
	
	pid_Y.Kp = 10;
	pid_Y.Ki = 0.016;
	pid_Y.Kd = 0.2;
	
	pid_D.Kp = 0;
	pid_D.Ki = 0;
	pid_D.Kd = 0;
	
	pid_X.err_current = 0;
	pid_X.err_last1 = 0;
	pid_X.err_last2 = 0;
	
	pid_Y.err_current = 0;
	pid_Y.err_last1 = 0;
	pid_Y.err_last2 = 0;
	
	pid_D.err_current = 0;
	pid_D.err_last1 = 0;
	pid_D.err_last2 = 0;
}
	
	
u8 Plane_PID(int X_value,int Y_value,int D_value)//ҲҪ�Ծ������pid����
{
	float pErr_X = 0;
	float iErr_X = 0;
	float dErr_X = 0;
	float pErr_Y = 0;
	float iErr_Y = 0;
	float dErr_Y = 0;
	float pErr_D = 0;
	float iErr_D = 0;
	float dErr_D = 0;
	const float px = 1;
	const float py = 1;
	const float pd = 1;
  pid_X.mid_value = 1556;//���������ֵ
	pid_Y.mid_value = 1556;
	pid_D.mid_value = 1556;
  pid_X.err_current = X_value;//��ǰ���
  pid_Y.err_current = Y_value;//��ǰ���
	pid_D.err_current = D_value;
	
	pErr_X = pid_X.err_current-pid_X.err_last1;
	iErr_X = pid_X.err_current;
	dErr_X = pid_X.err_current-2*pid_X.err_last1+pid_X.err_last2;
	
	pErr_Y = pid_Y.err_current-pid_Y.err_last1;
	iErr_Y = pid_Y.err_current;
	dErr_Y = pid_Y.err_current-2*pid_Y.err_last1+pid_Y.err_last2;
	
	pErr_D = pid_D.err_current-pid_D.err_last1;
	iErr_D = pid_D.err_current;
	dErr_D = pid_D.err_current-2*pid_D.err_last1+pid_D.err_last2;
//	printf1("perr=%f\r\n",pErr_X);
//	printf1("ierr=%f\r\n",iErr_X);
//	printf1("derr=%f\r\n",dErr_X);
	pid_X.delta_output = pid_X.Kp*pErr_X+pid_X.Ki*iErr_X+pid_X.Kd*dErr_X;
	pid_X.err_last2 = pid_X.err_last1;
	pid_X.err_last1 = pid_X.err_current;
	
	pid_Y.delta_output = pid_Y.Kp*pErr_Y+pid_Y.Ki*iErr_Y+pid_Y.Kd*dErr_Y;
	pid_Y.err_last2 = pid_Y.err_last1;
	pid_Y.err_last1 = pid_Y.err_current;
	
	pid_D.delta_output = pid_D.Kp*pErr_D+pid_D.Ki*iErr_D+pid_D.Kd*dErr_D;
	pid_D.err_last2 = pid_D.err_last1;
	pid_D.err_last1 = pid_D.err_current;

//	printf1("delta = %f\r\n",pid_X.delta_output);
	SetChannelValue(__YAW,pid_X.mid_value+pid_X.delta_output*px);//yaw���
  SetChannelValue(__ACCE,pid_Y.mid_value+pid_Y.delta_output*py);//�������
	return 1;
}
//��ʱֻ��X���е��أ�����ֻ��yaw



////	const int mid_value=1556;
////	int 	bias_X = 0;
//	float pErr_X = 0;
//	float iErr_X = 0;
//	float dErr_X = 0;
////	
////	ErrCurrent_X = X_value;
////	pErr_X = ErrCurrent_X-ErrLast1_X;//�������(���ڵ�ǰ����ȥǰһ�ε����)
////	iErr_X = ErrCurrent_X;//�������(���ڵ�ǰ���ֵ)
////	dErr_X = ErrCurrent_X-ErrLast1_X*2+ErrLast2_X;//΢�����(���ڵ�ǰ����ȥǰһ��2������ټ���ǰ���ε����)

////	ErrLast2_X = ErrLast1_X;
////	ErrLast1_X = ErrCurrent_X;
////	
////	CurrentOut_X = LastOut_X+Kp_X*pErr_X+Ki_X*iErr_X+Kd_X*dErr_X;
////	LastOut_X = CurrentOut_X;
//	
////	SetChannelValue(__YAW,mid_value+X_value);//yaw���
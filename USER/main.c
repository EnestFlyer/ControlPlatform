#include "stm32f10x.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../HARDWARE/MCP41010/MCP41010.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include  "string.h"
#include "../../SOFTWARE/PlaneAuto/PlaneAuto.h"
#include "../../SOFTWARE/EXTI/exti.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"
#include "../../SOFTWARE/SelfTest/SelfTest.h"
#include "../../HARDWARE/OLED/oled.h"

extern u16 USART_RX3_STA;
extern u8 Rx3Buf[Rx3Length];
int X_val=0;//����ڱ�ץ�����Xƫ����
int Y_val=0;//����ڱ�ץ�����Yƫ����
int D_val=65526;//�����ʼ��Ϊ���޴�
int main(void)
{
	int len=0;
	int t=0;
	int flag=0;//������־����λΪ����
	u8 temp[100]={0};//�����
	char command='O';//������
	u8 counter=0;
	int testvalue=1000;
	int x=-64;
	delay_init(72);
	USART1_Init(115200);//���ڵ���
	USART3_Init(115200);//���ڽ���Զ�˴�������
	MCP41010_Init();//��ʼ�����ֵ�λ��
	EXTIX_Init();//�����ⲿ�ж�
	TEST_Init();//����ģʽ���������л�
  Plane_Init();
	ResetOLED();
	OLED_Init();
	OLED_ShowString(35,20,"READY",24);
	OLED_Refresh_Gram();
	delay_ms(1000);
	OLED_Clear();
	OLED_DrawAxes(64,32);
//	while(1)
//	{
//		SetChannelValue(__ACCE,testvalue);
//		testvalue+=100;
//		if(testvalue==2000) testvalue=1000;
//		delay_ms(1000);
//	}//���Ե����Ĳ��Դ��룬ʹ��ʱע�͵���
	//////////////////////////////���ϳ�ʼ��///////////////////////////////////////////////
	//while(SelfTest()==0);
	/////////////////////////////�����Լ죬��������������������/////////////////////////////
	//while(!Plane_LAUNCH()) ;//�Զ����ģʽ����ɳɹ�����Ŀ��֮��ʼ�Զ����ڡ�
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
			//printf1("%s\r\n",temp);//������
			USART_RX3_STA=0;
		}
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='X')
			{
				printf1("X=%d\r\n",ValueOfMea(temp));//for test
				OLED_ShowTrace(X_val,Y_val);
				X_val=ValueOfMea(temp);
				counter++;
			}
			else if(command=='Y')
			{
				printf1("Y=%d\r\n",ValueOfMea(temp));//for test
				OLED_ShowTrace(X_val,Y_val);
				Y_val=ValueOfMea(temp);	
				counter++;
			}
			
			else if(command=='D')//����̫���˾�ֻ��ƫ������Ҫȥpitch
			{
				printf1("D=%d\r\n",ValueOfMea(temp));//for test
				D_val=ValueOfMea(temp);
			}
			
			memset(temp,0,sizeof(u8)*100);
			flag=0;
			
			if(counter==2)//����X��Y����ʱ�ſ�ʼ�Զ����ڡ�
			{
				
				Plane_PID(X_val,Y_val,D_val);
				OLED_DispTrace(X_val,Y_val);
				counter=0;
			}
		}
	}
	return 1;
}




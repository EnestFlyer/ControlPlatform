#include "stm32f10x.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../HARDWARE/MCP41010/MCP41010.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include  "string.h"
#include "../../SOFTWARE/PlaneAuto/PlaneAuto.h"
#include "../../SOFTWARE/EXTI/exti.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"




extern u16 USART_RX3_STA;
extern u8 Rx3Buf[Rx3Length];
int X_val=0;//����ڱ�ץ�����Xƫ����
int Y_val=0;//����ڱ�ץ�����Yƫ����


int main(void)
{
	int len=0;
	int t=0;
	int flag=0;//������־����λΪ����
	u8 temp[100]={0};//�����
	char command='O';//������
	u8 counter=0;
		
	delay_init(72);
	USART1_Init(115200);//���ڵ���
	USART3_Init(19200);//���ڽ���Զ�˴�������
	MCP41010_Init();

	{
	#ifdef __TEST_MODE_
	TEST_Init();
	EXTIX_Init();
	#endif
	}
	//while(!Plane_LAUNCH()) ;
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
			printf1("%s\n",temp);
		}
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='X')
			{
				//printf1("X=%d\n",ValueOfMea(temp));//for test
				X_val=ValueOfMea(temp);
				counter++;
			}
			else if(command=='Y')
			{
				//printf1("Y=%d\n",ValueOfMea(temp));//for test
				Y_val=ValueOfMea(temp);	
				counter++;
			}
			else if(command=='D')//����̫���˾�ֻ��ƫ������Ҫȥpitch
			{
				printf1("D=%d\n",ValueOfMea(temp));//for test
			}
			else if(command=='S')
			{
				printf1("S=%d\n",ValueOfMea(temp));//for test
			}			
			memset(temp,0,sizeof(u8)*100);
			flag=0;
//			if(counter==2)//����X��Y����ʱ�ſ�ʼ�Զ����ڡ�
//			{
//				Plane_PID(X_val,Y_val);
//				counter=0;
//			}
		}
	}
	return 1;
}




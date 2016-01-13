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
int X_val=0;//相对于被抓物体的X偏移量
int Y_val=0;//相对于被抓物体的Y偏移量


int main(void)
{
	int len=0;
	int t=0;
	int flag=0;//接满标志，置位为接满
	u8 temp[100]={0};//缓冲池
	char command='O';//命令字
	u8 counter=0;
		
	delay_init(72);
	USART1_Init(115200);//用于调试
	USART3_Init(19200);//用于接受远端串口命令
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
			len=USART_RX3_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				temp[t]=Rx3Buf[t];
				while((USART3->SR&0X40)==0);//等待发送结束
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
			else if(command=='D')//距离太近了就只是偏航而不要去pitch
			{
				printf1("D=%d\n",ValueOfMea(temp));//for test
			}
			else if(command=='S')
			{
				printf1("S=%d\n",ValueOfMea(temp));//for test
			}			
			memset(temp,0,sizeof(u8)*100);
			flag=0;
//			if(counter==2)//捕获到X和Y数据时才开始自动调节。
//			{
//				Plane_PID(X_val,Y_val);
//				counter=0;
//			}
		}
	}
	return 1;
}




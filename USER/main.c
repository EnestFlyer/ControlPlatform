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



extern u16 USART_RX3_STA;
extern u8 Rx3Buf[Rx3Length];
int X_val=0;//相对于被抓物体的X偏移量
int Y_val=0;//相对于被抓物体的Y偏移量
int D_val=65526;//距离初始化为无限大
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
	printf1("ready\r\n");
	{
		#ifdef __TEST_MODE_
		EXTIX_Init();
		TEST_Init();
		printf1("ok\r\n");
		#endif
	}
	//////////////////////////////以上初始化///////////////////////////////////////////////
	while(SelfTest()==0);
	/////////////////////////////以上自检，包括开发环境和数据链/////////////////////////////
	//while(!Plane_LAUNCH()) ;//自动起飞模式，起飞成功捕获到目标之后开始自动调节。
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
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='X')
			{
				#ifdef __PRINT_TEST_MODE
					printf1("X=%d\r\n",ValueOfMea(temp));//for test
				#endif
				X_val=ValueOfMea(temp);
				counter++;
			}
			else if(command=='Y')
			{
				#ifdef __PRINT_TEST_MODE
					printf1("Y=%d\r\n",ValueOfMea(temp));//for test
				#endif
				Y_val=ValueOfMea(temp);	
				counter++;
			}
			
			else if(command=='D')//距离太近了就只是偏航而不要去pitch
			{
				#ifdef __PRINT_TEST_MODE
					printf1("D=%d\r\n",ValueOfMea(temp));//for test
				#endif
				D_val=ValueOfMea(temp);
			}
			
			memset(temp,0,sizeof(u8)*100);
			flag=0;
			
			if(counter==2)//捕获到X和Y数据时才开始自动调节。
			{
				Plane_PID(X_val,Y_val,D_val);
				counter=0;
			}
		}
	}
	return 1;
}




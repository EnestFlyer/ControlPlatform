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
	//int testvalue=1000;
	//int x=-64;
	u8 reg_recv=0;
	//接受命令寄存器，LSB置位表示接收到X，LSB+1置位表示接收到Y，+2置位
	//表示接收到D
	
	///////////////////////////////////////////////////////////
	delay_init(72);
	USART1_Init(115200);//用于调试
	USART3_Init(115200);//用于接受远端串口命令
	MCP41010_Init();//初始化数字电位器
	EXTIX_Init();//开启外部中断
	PID_Init();//pid参数初始化
	TEST_Init();//测试模式，用于秒切换
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
//		SetChannelValue(__YAW,testvalue);
//		testvalue+=100;
//		if(testvalue==2000) testvalue=1000;
//		delay_ms(1000);
//	}//测试电阻板的测试代码，使用时注释掉。
	//////////////////////////////以上初始化///////////////////////////////////////////////
	//while(SelfTest()==0);
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
			//printf1("%s\r\n",temp);//调试用
			USART_RX3_STA=0;
		}
		
		if(flag==1)
		{
			command=TempOrPressure(temp);
			if(command=='X')
			{
				X_val=ValueOfMea(temp);
				printf1("X=%d\r\n",X_val);//for test
				reg_recv |= 0x01;//表示接收到X
			}
			else if(command=='Y')
			{
				Y_val=ValueOfMea(temp);
				printf1("Y=%d\r\n",Y_val);//for test
				reg_recv |= 0x02;
			}
			else if(command=='D')//距离太近了就只是偏航而不要去pitch
			{
				D_val=ValueOfMea(temp);
				printf1("D=%d\r\n",D_val);//for test
				reg_recv |= 0x04;
			}
			memset(temp,0,sizeof(u8)*100);
			flag=0;
			if((reg_recv&0x03) == 0x03)//捕获到X和Y数据时才开始自动调节。
			{
				Plane_PID(X_val,Y_val,D_val);
				printf1("ok\r\n");
				OLED_ShowTrace(X_val,Y_val);
				reg_recv = 0;
			}
		}
		
		
		
	}
	return 1;
}




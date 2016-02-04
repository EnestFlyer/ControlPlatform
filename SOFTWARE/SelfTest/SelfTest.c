#include "../../SOFTWARE/SelfTest/SelfTest.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/USART/USART.h"
#include "../../SYSTEM/delay/delay.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"
#include "../../SOFTWARE/StrToNum/StrToNum.h"
#include "../../HARDWARE/E17_TTL500/E17_TTL500.h"
#include "string.h"

extern u16 USART_RX3_STA;
extern u8 Rx3Buf[Rx3Length];

u8 SelfTest()//成功返回1
{
	int len=0;
	int t=0;
	u8 temp[100]={0};//缓冲池
	int flag=0;//接满标志，置位为接满
	char command='O';//命令字
	u8 value=0;
	
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
			if(command=='S')
			{
				value=ValueOfMea(temp);
				#ifdef __PRINT_TEST_MODE
					printf1("data chain test :S=%d\r\n",value);
				#endif
				//将自检信息打印出来
				break;
			}
			
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}	
	}
	
	#ifdef __TRANSPARENT_MODE
		printf3("\"S\":\"%ld\"\r\n",7);
	#endif
	
	#ifdef __COMMAND_MODE
		E17_SendMsg(CMD_S_PARAM,7);
	#endif
	flag=0;
	command='0';
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
			if(command=='S')
			{
				if(ValueOfMea(temp)==8)
				{
					break;
				}
			}
			
			memset(temp,0,sizeof(u8)*100);
			flag=0;
		}
	}//握手结束，自检完成，开始起飞
	
	return 1;
}









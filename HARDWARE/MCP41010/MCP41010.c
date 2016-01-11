#include "../../HARDWARE/MCP41010/MCP41010.h"
#include "../../SYSTEM/sys/sys.h"
#include "../../SYSTEM/delay/delay.h"

/*****************************���������ֵ�λ��������***************************************/

////////////////////////////////////////////////////////
//���ܣ�����MCP41010�Ĺܽų�ʼ��
//#define MCP41010_ACCE_CS PAout(4)
//#define MCP41010_ACCE_SCK PAout(5)
//#define MCP41010_ACCE_SDA PAout(6)//����

//#define MCP41010_YAW_CS PCout(6)
//#define MCP41010_YAW_SCK PCout(7)
//#define MCP41010_YAW_SDA PCout(8)//ƫ��


//#define MCP41010_ROLL_CS PEout(7)
//#define MCP41010_ROLL_SCK PEout(8)
//#define MCP41010_ROLL_SDA PEout(9)//����

//#define MCP41010_PITCH_CS PEout(10)
//#define MCP41010_PITCH_SCK PEout(11)
//#define MCP41010_PITCH_SDA PEout(12)//ǰ��
///////////////////////////////////////////////////////
void MCP41010_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//ƫ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);//����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);//ǰ��
}


////////////////////////////////////////////////////////
//���ܣ���ͨ��ֵ������ֵ
//������u8 whichChl��ʾͨ��ѡ��  1(__ACCE)��ʾACCE  2(__YAW)��ʾYAW  3(__ROLL)��ʾROLL 4(__PITCH)��ʾPITCH   long CHlValue ��ʾ��Ӧ����ֵ����1000-2000
//���أ�0��ʾ����  1��ʾ��ȷ
///////////////////////////////////////////////////////

u8 SetChannelValue(u8 whichChl,long ChlValue)
{
		if(ChlValue<1000||ChlValue>2000)
			return 0;
		if(whichChl>4)
			return 0;
		
		switch(whichChl)
		{
			case 1:MCP41010_SetResistor(1,(long)((double)(ChlValue-BASE_VALUE_ACCE)/PROPORTION_ACCE));break;
			case 2:MCP41010_SetResistor(2,(long)((double)(ChlValue-BASE_VALUE_YAW)/PROPORTION_YAW));break;
			case 3:MCP41010_SetResistor(3,(long)((double)(ChlValue-BASE_VALUE_ROLL)/PROPORTION_ROLL));break;
			case 4:MCP41010_SetResistor(4,(long)((double)(ChlValue-BASE_VALUE_PITCH)/PROPORTION_PITCH));break;
		}
		return 1;
}


////////////////////////////////////////////////////////
//���ܣ����ø���ͨ������ֵ
//������which ��ʾѡ���Ǹ�ͨ����1 ��ʾACCE��2��ʾYAW��3��ʾROLL��4��ʾPITCH
//���أ�0��ʾ����1��ʾ��ȷ
///////////////////////////////////////////////////////

u8 MCP41010_SetResistor(u8 which,long val)
{
		if(val>10000||val<0)
			return 0;
		switch(which)
		{
			case 1:Set_ACCE_Resistor(19,256-(int)(val-RESISTOR_W_ACCE)*256/RESISTOR_VALUE_ACCE);return 1;
			case 2:Set_YAW_Resistor(19,256-(int)(val-RESISTOR_W_YAW)*256/RESISTOR_VALUE_YAW);return 1;
			case 3:Set_ROLL_Resistor(19,256-(int)(val-RESISTOR_W_ROLL)*256/RESISTOR_VALUE_ROLL);return 1;
			case 4:Set_PITCH_Resistor(19,256-(int)(val-RESISTOR_W_PITCH)*256/RESISTOR_VALUE_PITCH);return 1;
			default:return 0;
		}
}


//MSB��ǰ��LSB�ں�
static void Set_ACCE_Resistor(u8 command,u8 data)
{
	u8 i=0;
	u8 temp=0;
	
	MCP41010_ACCE_CS=1;
	MCP41010_ACCE_SCK=1;
	delay_us(1);
	MCP41010_ACCE_SDA=0;
	
	delay_us(1);
	MCP41010_ACCE_CS=0;
	delay_us(1);
	for(i=0;i<8;i++)
	{
		MCP41010_ACCE_SCK=0;
		delay_us(1);
		temp=command&0x80;
		MCP41010_ACCE_SDA=temp>>7;
		delay_us(1);
		MCP41010_ACCE_SCK=1;
		delay_us(1);
		command=command<<1;
	}
	temp=0;
	for(i=0;i<8;i++)
	{
		MCP41010_ACCE_SCK=0;
		delay_us(1);
		temp=data&0x80;
		MCP41010_ACCE_SDA=temp>>7;
		delay_us(1);
		MCP41010_ACCE_SCK=1;
		delay_us(1);
		data=data<<1;
	}
	MCP41010_ACCE_CS=1;//ʹ��
	delay_us(1);
	MCP41010_ACCE_CS=0;//ʹ��
}
	
//MSB��ǰ��LSB�ں�
static void Set_YAW_Resistor(u8 command,u8 data)
{
	u8 i=0;
	u8 temp=0;
	
	MCP41010_YAW_CS=1;
	MCP41010_YAW_SCK=1;
	delay_us(1);
	MCP41010_YAW_SDA=0;
	
	delay_us(1);
	MCP41010_YAW_CS=0;
	delay_us(1);
	for(i=0;i<8;i++)
	{
		MCP41010_YAW_SCK=0;
		delay_us(1);
		temp=command&0x80;
		MCP41010_YAW_SDA=temp>>7;
		delay_us(1);
		MCP41010_YAW_SCK=1;
		delay_us(1);
		command=command<<1;
	}
	temp=0;
	for(i=0;i<8;i++)
	{
		MCP41010_YAW_SCK=0;
		delay_us(1);
		temp=data&0x80;
		MCP41010_YAW_SDA=temp>>7;
		delay_us(1);
		MCP41010_YAW_SCK=1;
		delay_us(1);
		data=data<<1;
	}
	MCP41010_YAW_CS=1;//ʹ��
	delay_us(1);
	MCP41010_YAW_CS=0;//ʹ��
}

//MSB��ǰ��LSB�ں�
static void Set_ROLL_Resistor(u8 command,u8 data)
{
	u8 i=0;
	u8 temp=0;
	
	MCP41010_ROLL_CS=1;
	MCP41010_ROLL_SCK=1;
	delay_us(1);
	MCP41010_ROLL_SDA=0;
	
	delay_us(1);
	MCP41010_ROLL_CS=0;
	delay_us(1);
	for(i=0;i<8;i++)
	{
		MCP41010_ROLL_SCK=0;
		delay_us(1);
		temp=command&0x80;
		MCP41010_ROLL_SDA=temp>>7;
		delay_us(1);
		MCP41010_ROLL_SCK=1;
		delay_us(1);
		command=command<<1;
	}
	temp=0;
	for(i=0;i<8;i++)
	{
		MCP41010_ROLL_SCK=0;
		delay_us(1);
		temp=data&0x80;
		MCP41010_ROLL_SDA=temp>>7;
		delay_us(1);
		MCP41010_ROLL_SCK=1;
		delay_us(1);
		data=data<<1;
	}
	MCP41010_ROLL_CS=1;//ʹ��
	delay_us(1);
	MCP41010_ROLL_CS=0;//ʹ��
}


//MSB��ǰ��LSB�ں�
static void Set_PITCH_Resistor(u8 command,u8 data)
{
	u8 i=0;
	u8 temp=0;
	
	MCP41010_PITCH_CS=1;
	MCP41010_PITCH_SCK=1;
	delay_us(1);
	MCP41010_PITCH_SDA=0;
	
	delay_us(1);
	MCP41010_PITCH_CS=0;
	delay_us(1);
	for(i=0;i<8;i++)
	{
		MCP41010_PITCH_SCK=0;
		delay_us(1);
		temp=command&0x80;
		MCP41010_PITCH_SDA=temp>>7;
		delay_us(1);
		MCP41010_PITCH_SCK=1;
		delay_us(1);
		command=command<<1;
	}
	temp=0;
	for(i=0;i<8;i++)
	{
		MCP41010_PITCH_SCK=0;
		delay_us(1);
		temp=data&0x80;
		MCP41010_PITCH_SDA=temp>>7;
		delay_us(1);
		MCP41010_PITCH_SCK=1;
		delay_us(1);
		data=data<<1;
	}
	MCP41010_PITCH_CS=1;//ʹ��
	delay_us(1);
	MCP41010_PITCH_CS=0;//ʹ��
}




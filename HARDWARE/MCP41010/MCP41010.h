#ifndef _EMBEDDED_H_
#define _EMBEDDED_H_

#include "../../SYSTEM/sys/sys.h"


#define MCP41010_ACCE_CS PAout(4)
#define MCP41010_ACCE_SCK PAout(5)
#define MCP41010_ACCE_SDA PAout(6)//����

#define MCP41010_YAW_CS PCout(6)
#define MCP41010_YAW_SCK PCout(7)
#define MCP41010_YAW_SDA PCout(8)//ƫ��


#define MCP41010_ROLL_CS PEout(7)
#define MCP41010_ROLL_SCK PEout(8)
#define MCP41010_ROLL_SDA PEout(9)//����

#define MCP41010_PITCH_CS PEout(10)
#define MCP41010_PITCH_SCK PEout(11)
#define MCP41010_PITCH_SDA PEout(12)//ǰ��


#define RESISTOR_VALUE_ACCE 9290 //����ֵ10K
#define RESISTOR_VALUE_YAW 9170 //����ֵ10K
#define RESISTOR_VALUE_ROLL 9140 //����ֵ10K
#define RESISTOR_VALUE_PITCH 9150 //����ֵ10K

#define RESISTOR_W_ACCE 0 //��ͷ����
#define RESISTOR_W_YAW 0 //��ͷ����
#define RESISTOR_W_ROLL 0 //��ͷ����
#define RESISTOR_W_PITCH 0 //��ͷ����


#define PROPORTION_ACCE 	0.10989//ͨ��ֵ�����ֵ�ı�ֵ,������
#define PROPORTION_YAW 		0.10946//ͨ��ֵ�����ֵ�ı�ֵ�������
#define PROPORTION_ROLL 	0.10754//ͨ��ֵ�����ֵ�ı�ֵ�������
#define PROPORTION_PITCH 	0.11288//ͨ��ֵ�����ֵ�ı�ֵ,������

#define BASE_VALUE_ACCE 1031.4
#define BASE_VALUE_YAW 1031.4
#define BASE_VALUE_ROLL 1031.4
#define BASE_VALUE_PITCH 1038.3




/*************���ֵ�λ��MCP41010������*******************/
void MCP41010_Init(void);
u8 MCP41010_SetResistor(u8 which,long val);
u8 SetChannelValue(u8 whichChl,long ChlValue);
static void Set_ACCE_Resistor(u8 command,u8 data);
static void Set_YAW_Resistor(u8 command,u8 data);
static void Set_ROLL_Resistor(u8 command,u8 data);
static void Set_PITCH_Resistor(u8 command,u8 data);
	




#endif


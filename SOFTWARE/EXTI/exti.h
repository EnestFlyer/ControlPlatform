#ifndef __EXTI_H_
#define __EXTI_H_ 

#include "../../SYSTEM/sys/sys.h"

#define LED_ACCE 				PEout(0)
#define LED_YAW 		 	  PEout(1)
#define LED_ROLL 				PEout(2)
#define LED_PITCH 			PEout(3)
#define LED_ALL 				PEout(4)
//LED initiate
//LED共地，点亮为手动控制，灭为自动控制

#define KEY_ACCE			  PCin(0)
#define KEY_YAW 				PCin(1)
#define KEY_ROLL 				PCin(2)
#define KEY_PITCH 			PCin(3)
#define KEY_ALL 				PCin(4)
//按键

#define ACCE_MCU 				PDout(0)
#define ACCE_ORI 				PDout(1)

#define YAW_MCU 				PDout(2)
#define YAW_ORI				  PDout(3)

#define ROLL_MCU 				PDout(4)
#define ROLL_ORI 				PDout(5)

#define PITCH_MCU 			PDout(6)
#define PITCH_ORI			  PDout(7)
//cd4066控制端,高电平导通，低电平截止

#define LED_ON 1
#define LED_OFF 0
#define MCU_ENABLE 1
#define ORI_ENABLE 1
#define MCU_DISABLE 0
#define ORI_DISABLE 0

void EXTIX_Init(void);//IO初始化
void TEST_Init(void);
		 					    
#endif


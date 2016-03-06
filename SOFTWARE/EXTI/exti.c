#include "../../SYSTEM/USART/USART.h"
#include "../../SYSTEM/delay/delay.h"
#include "stm32f10x_exti.h"
#include "../../SOFTWARE/EXTI/exti.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"

//用于测试版模式
#ifdef __TEST_MODE_


void TEST_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//PD0-PD7 用于给cd4066控制用。

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//PE0-PE4 LED,自动控制时灭，手动控制时亮,LED共地
	if(KEY_ACCE==1) LED_ACCE=LED_ON;
	if(KEY_YAW==1) LED_YAW=LED_ON;
	if(KEY_ROLL==1) LED_ROLL=LED_ON;
	if(KEY_PITCH==1) LED_PITCH=LED_ON;
	if(KEY_ALL==1) LED_ALL=LED_ON;
	
	if(KEY_ACCE==0) LED_ACCE=LED_OFF;
	if(KEY_YAW==0) LED_YAW=LED_OFF;
	if(KEY_ROLL==0) LED_ROLL=LED_OFF;
	if(KEY_PITCH==0) LED_PITCH=LED_OFF;
	if(KEY_ALL==0) LED_ALL=LED_OFF;
	
	//表示实际的初始化led状态
		
}

//外部中断初始化函数
void EXTIX_Init(void)
{
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
	/****************************PC0******************************/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	/****************************PC1************************************/
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	/****************************PC2************************************/
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
	/****************************PC3************************************/
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
	/****************************PC4************************************/
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void EXTI0_IRQHandler(void)
{
	delay_ms(30);
	if(KEY_ACCE==1)//手动控制
	{
		LED_ACCE=LED_ON;
		ACCE_ORI=ORI_ENABLE;
		ACCE_MCU=MCU_DISABLE;
	}
	else 
	{
	  LED_ACCE=LED_OFF;
		ACCE_ORI=ORI_DISABLE;
		ACCE_MCU=MCU_ENABLE;
	}		
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

void EXTI1_IRQHandler(void)
{
	delay_ms(30);
	if(KEY_YAW==1)//手动控制
	{
		LED_YAW=LED_ON;
		YAW_ORI=ORI_ENABLE;
		YAW_MCU=MCU_DISABLE;
	}
	else 
	{
	  LED_YAW=LED_OFF;
		YAW_ORI=ORI_DISABLE;
		YAW_MCU=MCU_ENABLE;
	}		
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI0线路挂起位
}

void EXTI2_IRQHandler(void)
{
	delay_ms(30);
	if(KEY_ROLL==1)
	{
		LED_ROLL=LED_ON;
		ROLL_ORI=ORI_ENABLE;
		ROLL_MCU=MCU_DISABLE;
	}
	else 
	{
	  LED_ROLL=LED_OFF;
		ROLL_ORI=ORI_DISABLE;
		ROLL_MCU=MCU_ENABLE;
	}		
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除EXTI0线路挂起位
}

void EXTI3_IRQHandler(void)
{
	delay_ms(30);
	if(KEY_PITCH==1)
	{
		LED_PITCH=LED_ON;
		PITCH_ORI=ORI_ENABLE;
		PITCH_MCU=MCU_DISABLE;
	}
	else 
	{
	  LED_PITCH=LED_OFF;
		PITCH_ORI=ORI_DISABLE;
		PITCH_MCU=MCU_ENABLE;
	}		
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除EXTI0线路挂起位
}

void EXTI4_IRQHandler(void)//ALL
{
	delay_ms(30);
	if(KEY_ALL==1)//ALL IN HAND
	{
		LED_ALL=LED_ON;
		ACCE_ORI=ORI_ENABLE;
		YAW_ORI=ORI_ENABLE;
		ROLL_ORI=ORI_ENABLE;
		PITCH_ORI=ORI_ENABLE;
		
		ACCE_MCU=MCU_DISABLE;
		YAW_MCU=MCU_DISABLE;
		ROLL_MCU=MCU_DISABLE;
		PITCH_MCU=MCU_DISABLE;
	}
	else 
	{
	  LED_ALL=LED_OFF;
		ACCE_ORI=ORI_DISABLE;
		YAW_ORI=ORI_DISABLE;
		ROLL_ORI=ORI_DISABLE;
		PITCH_ORI=ORI_DISABLE;
		
		ACCE_MCU=MCU_ENABLE;
		YAW_MCU=MCU_ENABLE;
		ROLL_MCU=MCU_ENABLE;
		PITCH_MCU=MCU_ENABLE;
		{
			if(KEY_ACCE==1)//手动控制
			{
				LED_ACCE=LED_ON;
				ACCE_ORI=ORI_ENABLE;
				ACCE_MCU=MCU_DISABLE;
			}
			else 
			{
				LED_ACCE=LED_OFF;
				ACCE_ORI=ORI_DISABLE;
				ACCE_MCU=MCU_ENABLE;
			}	
			
			if(KEY_YAW==1)//手动控制
			{
				LED_YAW=LED_ON;
				YAW_ORI=ORI_ENABLE;
				YAW_MCU=MCU_DISABLE;
			}
			else 
			{
				LED_YAW=LED_OFF;
				YAW_ORI=ORI_DISABLE;
				YAW_MCU=MCU_ENABLE;
			}
			
			if(KEY_ROLL==1)
			{
				LED_ROLL=LED_ON;
				ROLL_ORI=ORI_ENABLE;
				ROLL_MCU=MCU_DISABLE;
			}
			else 
			{
				LED_ROLL=LED_OFF;
				ROLL_ORI=ORI_DISABLE;
				ROLL_MCU=MCU_ENABLE;
			}
			
			if(KEY_PITCH==1)
			{
				LED_PITCH=LED_ON;
				PITCH_ORI=ORI_ENABLE;
				PITCH_MCU=MCU_DISABLE;
			}
			else 
			{
				LED_PITCH=LED_OFF;
				PITCH_ORI=ORI_DISABLE;
				PITCH_MCU=MCU_ENABLE;
			}		
	
		}
	}		
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除EXTI0线路挂起位
}



#endif

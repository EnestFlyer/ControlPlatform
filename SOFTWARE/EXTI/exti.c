#include "../../SYSTEM/USART/USART.h"
#include "../../SYSTEM/delay/delay.h"
#include "stm32f10x_exti.h"
#include "../../SOFTWARE/EXTI/exti.h"
#include "../../SOFTWARE/TEST_INC/TEST_INC.h"


#ifdef __TEST_MODE_


void TEST_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);//PC1�������ߣ�PC2��������
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);//PC3 LED,�Զ�����ʱ���ֶ�����ʱ��
}

//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	/****************************PC0******************************/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising_Falling;//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

void EXTI0_IRQHandler(void)
{
	delay_ms(100);
	if(PCin(0)==1)
	{
		HIGH_PIN=1;
		LOW_PIN=0;
		LED=1;//LED��
	}//�ֶ�����
	else if(PCin(0)==0)
	{
		HIGH_PIN=0;
		LOW_PIN=1;
		LED=0;//LED��
	}//�Զ�����
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}


#endif

/*************************************************************************************
*��д�ˣ������
*ʱ�䣺2015/7
*����8Mhz
*MCU��STM32F103ZET6
*���ܣ�����USART���ڵ�����
*API�ӿں�����
(1)USARTx_Init(u32 bound)
����ֵ��void
���������u32 �����ʴ�С
���ܣ���ʼ�����ڣ�x=1��2��3
(2)printfx()
����ֵ��void
���������������arg����
���ܣ���ӡ����

*���յ������������������
Rx1Buf[]
Rx2Buf[]
Rx3Buf[]
Rx4Buf[]
Rx5Buf[]
*************************************************************************************/
#include "../../SYSTEM/USART/USART.h"
#include "../../SYSTEM/sys/sys.h"
#include "stm32f10x_usart.h"
#include "stdarg.h"


////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif


//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   
u8 Rx1Buf[Rx1Length];     //���ջ���,���USART_REC_LEN���ֽ�.	
u8 Rx2Buf[Rx2Length];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 Rx3Buf[Rx3Length];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 Rx4Buf[Rx4Length];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 Rx5Buf[Rx5Length];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 Rx1Flag=0;       //����״̬���	  
u16 Rx2Flag=0;       //����״̬���	  
u16 Rx3Flag=0;       //����״̬���	  
u16 Rx4Flag=0;       //����״̬���	  
u16 Rx5Flag=0;       //����״̬���	  

/*******************************************************************
�����Ǵ��ڳ�ʼ������USARTx_Init(u32 bound)
*******************************************************************/
void USART1_Init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	  USART_DeInit(USART1);  //��λ����1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	  NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	 USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}

void USART2_Init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART1��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	  NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	 USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

}


//��ʼ��IO ����1 
//bound:������
void USART3_Init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART1��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 

}
/*******************************************************************
�����Ǵ��ڽ����жϺ���USARTx_IRQHandler(void) 
*******************************************************************/
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
					Rx1Buf[Rx1Flag]=Res ;
					Rx1Flag++;
					if(Rx1Flag>Rx1Length) Rx1Flag=0;				
  }								
} 

void USART2_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
					Rx2Buf[Rx2Flag]=Res ;
					Rx2Flag++;
					if(Rx2Flag>Rx2Length) Rx2Flag=0;				
  }								
} 
	
u16 USART_RX3_STA=0; //����USART 3����flag
///////////////////////////////////////////////////////////////////////////////
//if(USART_RX3_STA&0x8000)
//		{					   
//			len=USART_RX3_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			for(t=0;t<len;t++)
//			{
//				temp[t]=Rx3Buf[t];
//				while((USART3->SR&0X40)==0);//�ȴ����ͽ���
//			}
//			flag=1;
//			USART_RX3_STA=0;
//		}
///////////////////////////////////////////////////////////////////////////////
//ע�⣺��Ҫ����������ʾ
//���磺 printf("\"X\":\"%d\"\r\n");//������\r\n��β
void USART3_IRQHandler(void)                	//����3�жϷ������
	{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
		
		if((USART_RX3_STA&0x8000)==0)//����δ���
			{
			if(USART_RX3_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)
					USART_RX3_STA=0;//���մ���,���¿�ʼ
				else 
					USART_RX3_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)
					USART_RX3_STA|=0x4000;
				else
					{
					Rx3Buf[USART_RX3_STA&0X3FFF]=Res ;
					USART_RX3_STA++;
					if(USART_RX3_STA>(Rx3Length-1))USART_RX3_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 
} 




/*******************************************************************
�����Ǵ��ڴ�ӡ����printfx()
*******************************************************************/
void printf1(char *fmt, ...) 
 { 
 char buffer[BUF_USART1+1];  
 u8 i = 0; 
 va_list arg_ptr; 
 va_start(arg_ptr, fmt);   
 vsnprintf(buffer,BUF_USART1+1,fmt,arg_ptr); 
 USART_ClearFlag(USART1,USART_FLAG_TC);

 while ((i <BUF_USART1) && buffer[i]) 
 { 
         USART_SendData(USART1, (u8) buffer[i++]); 
 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);  
 } 
 va_end(arg_ptr); 
 } 
 
void printf2(char *fmt, ...) 
 { 
 char buffer[BUF_USART2+1];  
 u8 i = 0; 
 va_list arg_ptr; 
 va_start(arg_ptr, fmt);   
 vsnprintf(buffer,BUF_USART2+1,fmt,arg_ptr); 
 USART_ClearFlag(USART2,USART_FLAG_TC);

 while ((i <BUF_USART2) && buffer[i]) 
 { 
         USART_SendData(USART2, (u8) buffer[i++]); 
 while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);  
 } 
 va_end(arg_ptr); 
 } 
 
void printf3(char *fmt, ...) 
 { 
 char buffer[BUF_USART3+1];  
 u8 i = 0; 
 va_list arg_ptr; 
 va_start(arg_ptr, fmt);   
 vsnprintf(buffer,BUF_USART3+1,fmt,arg_ptr); 
 USART_ClearFlag(USART3,USART_FLAG_TC);

 while ((i <BUF_USART3) && buffer[i]) 
 { 
         USART_SendData(USART3, (u8) buffer[i++]); 
 while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);  
 } 
 va_end(arg_ptr); 
 } 


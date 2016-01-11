#ifndef _PLANEAUTO_H_
#define _PLANEAUTO_H_

#include "../../SYSTEM/sys/sys.h"

#define ACCE_PROPORTION 	0		//ͨ��ֵ�������½��ٶȵı�ֵ
#define YAW_PROPORTION 		0		//ͨ��ֵ��ƫ���ٶ�֮��ı�ֵ
#define	ROLL_PROPORTION   0		//ͨ��ֵ�뷭���ٶȵı�ֵ
#define PITCH_RPOPORTION	0		//ͨ��ֵ�븩���ٶ�֮��ı�ֵ

#define THE_ERR_X 0		//��ΧȦX��δ���ԣ����Ժ������
#define THE_ERR_Y 0		//��ΧȦY��δ���ԣ����Ժ������

#define __ACCE 1
#define __YAW 2
#define __ROLL 3
#define __PITCH 4

/*******************************************************/
void Plane_Up(long UpSpeed);					//���ţ�UpSpeed���������ٶ�
void Plane_Down(long DownSpeed);			//���ţ�DownSpeed�����½��ٶ�
void Plane_Yaw(long YawSpeed);				//ƫ����YawSpeedƫ���ٶ� 
void Plane_Roll(long RollSpeed);			//������RollSpeed�����ٶ�/������
void Plane_Pitch(long PitchSpeed);		//�����ǣ�PitchSpeed/ǰ����


u8 Plane_PID(int X_value,int Y_value);//����������Ӧ��ʹ���������������Ȧ��
void Plane_UNLOCK(void);
void Plane_LOCK(void);
u8 Plane_LAUNCH(void);

#endif


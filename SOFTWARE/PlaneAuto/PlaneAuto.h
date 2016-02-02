#ifndef _PLANEAUTO_H_
#define _PLANEAUTO_H_

#include "../../SYSTEM/sys/sys.h"

#define ACCE_PROPORTION 	0		//通道值与上升下降速度的比值
#define YAW_PROPORTION 		0		//通道值与偏航速度之间的比值
#define	ROLL_PROPORTION   0		//通道值与翻滚速度的比值
#define PITCH_RPOPORTION	0		//通道值与俯仰速度之间的比值

#define THE_ERR_X 0		//误差范围圈X，未测试，测试后填参数
#define THE_ERR_Y 0		//误差范围圈Y，未测试，测试后填参数

#define __ACCE 1
#define __YAW 2
#define __ROLL 3
#define __PITCH 4

/*******************************************************/
u8 Plane_PID(int X_value,int Y_value,int D_val);//飞行器自适应，使得物体总是在误差圈内
void Plane_UNLOCK(void);
void Plane_LOCK(void);
u8 Plane_LAUNCH(void);

#endif


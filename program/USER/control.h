#ifndef CONTROL_H
#define CONTROL_H

#include <stm32f10x_tim.h>

#define VL 718 //左轮默认速度
#define VR 717 //右轮默认速度
#define MAXV 0	//最大转速
#define STOP 899 //停转
#define LMOTOR(v) TIM_SetCompare3(TIM1, v)//控制左电机转速
#define RMOTOR(v) TIM_SetCompare2(TIM1, v)//控制右电机转速
#define TURN_L_90 turnLInSitu(560) //原地左转90°
#define TURN_R_90 turnRInSitu(610) //原地右转90°

void setSpeed(unsigned int vl, unsigned int vr); //设置左右轮转速
void modifySpeed(float newVl, float newRl);//修改速度值并应用
void lForward(void);
void rForward(void);
void lRevers(void);
void rRevers(void);
void forward(void);//电机正转
void revers(void);//电机反转
void goSt(void);//保持小车在路上行驶
void reverse(unsigned int time);//倒车
void turnLInSitu(unsigned int time);//原地左转
void turnRInSitu(unsigned int time);//原地右转
void rCorrection(float lRatio, unsigned int time);//向右修正 0<ratio<1
void lCorrection(float rRatio, unsigned int time);//向左修正 0<ratio<1
void correction(float lRatio, float rRatio, unsigned int time);//左右同时修正

#endif //CONTROL

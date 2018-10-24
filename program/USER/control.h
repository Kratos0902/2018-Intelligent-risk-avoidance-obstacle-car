#ifndef CONTROL_H
#define CONTROL_H

#include <stm32f10x_tim.h>

#define VL 718 //����Ĭ���ٶ�
#define VR 717 //����Ĭ���ٶ�
#define MAXV 0	//���ת��
#define STOP 899 //ͣת
#define LMOTOR(v) TIM_SetCompare3(TIM1, v)//��������ת��
#define RMOTOR(v) TIM_SetCompare2(TIM1, v)//�����ҵ��ת��
#define TURN_L_90 turnLInSitu(560) //ԭ����ת90��
#define TURN_R_90 turnRInSitu(610) //ԭ����ת90��

void setSpeed(unsigned int vl, unsigned int vr); //����������ת��
void modifySpeed(float newVl, float newRl);//�޸��ٶ�ֵ��Ӧ��
void lForward(void);
void rForward(void);
void lRevers(void);
void rRevers(void);
void forward(void);//�����ת
void revers(void);//�����ת
void goSt(void);//����С����·����ʻ
void reverse(unsigned int time);//����
void turnLInSitu(unsigned int time);//ԭ����ת
void turnRInSitu(unsigned int time);//ԭ����ת
void rCorrection(float lRatio, unsigned int time);//�������� 0<ratio<1
void lCorrection(float rRatio, unsigned int time);//�������� 0<ratio<1
void correction(float lRatio, float rRatio, unsigned int time);//����ͬʱ����

#endif //CONTROL

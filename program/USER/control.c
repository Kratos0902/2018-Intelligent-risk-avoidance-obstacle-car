#include <stm32f10x_tim.h>
#include <delay.h>
#include "sys.h"
#include "config.h"
#include "control.h"

void setSpeed(const unsigned int vl, const unsigned int vr) //����������ת��
{
	RMOTOR(vr);
	LMOTOR(vl);
}

void modifySpeed(const float newVl, const float newRl)//�޸��ٶ�ֵ��Ӧ��
{
	vl = newVl;
	vr = newRl;
	setSpeed(vl, vr);
}

void lForward()//������ת
{
	AIN1 = 1;
	AIN2 = 0;
}

void rForward()//�ҵ����ת
{
	BIN1 = 1;
	BIN2 = 0;
}

void lRevers()//������ת
{
	AIN1 = 0;
	AIN2 = 1;
}

void rRevers()//�ҵ����ת
{
	BIN1 = 0;
	BIN2 = 1;
}

void forward()//���������ת
{
	lForward();
	rForward();
}

void revers()//���������ת
{
	lRevers();
	rRevers();
}

void goSt()//����С����·����ʻ
{
	if (LPS && !RPS)
		correction(0.86, 1.15, 100);
	else if (!LPS && RPS)
		correction(1.15, 0.86, 100);
}

 void turnLInSitu(const unsigned int time)//ԭ����ת
{
	rRevers();
	delay_ms(time);
	rForward();
}

void turnRInSitu(const unsigned int time)//ԭ����ת
{
	lRevers();
	delay_ms(time);
	lForward();
}

void rCorrection(const float lRatio, const unsigned int time)//��������time��ʱ�� 0<ratio<1
{
	setSpeed(vl * lRatio, vr);
	delay_ms(time);
	setSpeed(vl, vr);
}

void lCorrection(const float rRatio, const unsigned int time)//��������time��ʱ�� 0<ratio<1
{
	setSpeed(vl, vr * rRatio);
	delay_ms(time);
	setSpeed(vl, vr);
}

void correction(const float lRatio, const float rRatio, const unsigned int time)//����ͬʱ����time��ʱ�� 0<XRatio<1
{
	setSpeed(vl * lRatio, vr * rRatio);
	delay_ms(time);
	setSpeed(vl, vr);
}

void reverse(unsigned int time)//����
{
	revers();
	setSpeed(vl * 0.99, vr);
	while (time--)
		delay_ms(100);
	forward();
	setSpeed(vl, vr);
}

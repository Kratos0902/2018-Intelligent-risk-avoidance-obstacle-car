#include <stm32f10x_tim.h>
#include <delay.h>
#include "sys.h"
#include "config.h"
#include "control.h"

void setSpeed(const unsigned int vl, const unsigned int vr) //设置左右轮转速
{
	RMOTOR(vr);
	LMOTOR(vl);
}

void modifySpeed(const float newVl, const float newRl)//修改速度值并应用
{
	vl = newVl;
	vr = newRl;
	setSpeed(vl, vr);
}

void lForward()//左电机正转
{
	AIN1 = 1;
	AIN2 = 0;
}

void rForward()//右电机正转
{
	BIN1 = 1;
	BIN2 = 0;
}

void lRevers()//左电机反转
{
	AIN1 = 0;
	AIN2 = 1;
}

void rRevers()//右电机反转
{
	BIN1 = 0;
	BIN2 = 1;
}

void forward()//两个电机正转
{
	lForward();
	rForward();
}

void revers()//两个电机反转
{
	lRevers();
	rRevers();
}

void goSt()//保持小车在路上行驶
{
	if (LPS && !RPS)
		correction(0.86, 1.15, 100);
	else if (!LPS && RPS)
		correction(1.15, 0.86, 100);
}

 void turnLInSitu(const unsigned int time)//原地左转
{
	rRevers();
	delay_ms(time);
	rForward();
}

void turnRInSitu(const unsigned int time)//原地右转
{
	lRevers();
	delay_ms(time);
	lForward();
}

void rCorrection(const float lRatio, const unsigned int time)//向右修正time段时间 0<ratio<1
{
	setSpeed(vl * lRatio, vr);
	delay_ms(time);
	setSpeed(vl, vr);
}

void lCorrection(const float rRatio, const unsigned int time)//向左修正time段时间 0<ratio<1
{
	setSpeed(vl, vr * rRatio);
	delay_ms(time);
	setSpeed(vl, vr);
}

void correction(const float lRatio, const float rRatio, const unsigned int time)//左右同时修正time段时间 0<XRatio<1
{
	setSpeed(vl * lRatio, vr * rRatio);
	delay_ms(time);
	setSpeed(vl, vr);
}

void reverse(unsigned int time)//倒车
{
	revers();
	setSpeed(vl * 0.99, vr);
	while (time--)
		delay_ms(100);
	forward();
	setSpeed(vl, vr);
}

/*
 * *用于STM32F103RC
 */
#include <stm32f10x_tim.h>
#include "delay.h"
#include "sys.h"
#include "config.h"
#include "control.h"
#include "pwm.h"

unsigned int vl = VL;//电机初始转速
unsigned int vr = VR;

int main()
{
	u8 position = 0;//位置标记
	u8 lastPosition = 0;//位置变化标志位
	u8 risingEdge = 1;//上升沿标志位

	delay_init();//延时函数初始化
	motorInit(); //初始化电机接口
	photoInit(); //初始化光电开关
	tim1PwmInit(899, 0);//不分频 PWM频率=72000/(899+1)=80Khz  数字越小速度越快（范围 0~899）
	forward();//设置电机正转
	modifySpeed(VL * 0.9, VR * 0.9);//在第一段路提速

	while (1)
	{
		goSt();
		if (!risingEdge && !FPS)
			risingEdge = 1;
		if (FPS && risingEdge) //只有上升沿才能触发position的值递增
		{
			position++;
			risingEdge = 0;
		}
		if (position && lastPosition != position)
		{
			lastPosition = position;
			switch (position)
			{
			case 1:
				delay_ms(2000);//避开出发点的黑线
				break;
			case 2:
				modifySpeed(VL, VR);//恢复默认速度
				reverse(14);//检测不到前方的路，进行倒车并准备转弯
				TURN_L_90;
				setSpeed(VL, vr * 0.99);//控制车体偏左前进
				break;
			case 3:
				TURN_L_90;
				correction(0.92, 1.05, 500);
				setSpeed(VL * 0.985, vr);//控制车体沿右边行驶
				break;
			case 4:
				TURN_R_90;
				correction(0.94, 1.05, 300);
				modifySpeed(VL * 0.97, VR);
				break;
			case 5:
				TURN_L_90;
				correction(1.04, 0.935, 200);
				modifySpeed(VL * 0.94, VR);
				break;
			case 6:
				TURN_L_90;
				delay_ms(600);
				modifySpeed(VL * 1.02, VR);
				break;
			case 7://到梯形处拐弯
				modifySpeed(VL, VR * 0.98);
				TURN_R_90;
				modifySpeed(VL * 0.96, VR);
				break;
			case 8:
				modifySpeed(VL, VR);
				turnLInSitu(500);
				break;
			case 9:
				reverse(2);
				TURN_L_90;
				break;
			default:
				position = 1;
				break;
			}
		}
		if (position == 2 && (!LMS1 || !LMS2))//在位置2发现障碍物
		{
			TURN_R_90;
		}
		else if (position == 3 && (!LMS1 || !LMS2 || !RMS))
		{
			setSpeed(vl, vr);
			TURN_L_90;
		}
		else if (position == 5 && (!LMS1 || !LMS2))
		{
			delay_ms(20);
			TURN_L_90;
			rCorrection(0.8, 200);
			while (!FPS)
				;
			turnRInSitu(400);//向右稍转
			modifySpeed(VL * 1.05, VR * 0.97);
		}
	}
}

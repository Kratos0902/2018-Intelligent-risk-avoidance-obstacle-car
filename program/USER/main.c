/*
 * *����STM32F103RC
 */
#include <stm32f10x_tim.h>
#include "delay.h"
#include "sys.h"
#include "config.h"
#include "control.h"
#include "pwm.h"

unsigned int vl = VL;//�����ʼת��
unsigned int vr = VR;

int main()
{
	u8 position = 0;//λ�ñ��
	u8 lastPosition = 0;//λ�ñ仯��־λ
	u8 risingEdge = 1;//�����ر�־λ

	delay_init();//��ʱ������ʼ��
	motorInit(); //��ʼ������ӿ�
	photoInit(); //��ʼ����翪��
	tim1PwmInit(899, 0);//����Ƶ PWMƵ��=72000/(899+1)=80Khz  ����ԽС�ٶ�Խ�죨��Χ 0~899��
	forward();//���õ����ת
	modifySpeed(VL * 0.9, VR * 0.9);//�ڵ�һ��·����

	while (1)
	{
		goSt();
		if (!risingEdge && !FPS)
			risingEdge = 1;
		if (FPS && risingEdge) //ֻ�������ز��ܴ���position��ֵ����
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
				delay_ms(2000);//�ܿ�������ĺ���
				break;
			case 2:
				modifySpeed(VL, VR);//�ָ�Ĭ���ٶ�
				reverse(14);//��ⲻ��ǰ����·�����е�����׼��ת��
				TURN_L_90;
				setSpeed(VL, vr * 0.99);//���Ƴ���ƫ��ǰ��
				break;
			case 3:
				TURN_L_90;
				correction(0.92, 1.05, 500);
				setSpeed(VL * 0.985, vr);//���Ƴ������ұ���ʻ
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
			case 7://�����δ�����
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
		if (position == 2 && (!LMS1 || !LMS2))//��λ��2�����ϰ���
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
			turnRInSitu(400);//������ת
			modifySpeed(VL * 1.05, VR * 0.97);
		}
	}
}

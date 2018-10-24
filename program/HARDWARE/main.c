#include "optoelectronic_switch.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include <stm32f10x_tim.h>
//�������������
#define AIN1 PAout(4)
#define AIN2 PAout(6)
#define BIN1 PBout(4)
#define BIN2 PBout(6)
//��������
#define FPS PCin(5)
#define LPS PCin(6)
#define RPS PCin(7)
#define LSAPS PCin(8)
#define RSAPS PCin(9)


int main()
{
	u16 pwmVal = 0;
	u8 dir = 1;
	delay_init();	    	 //��ʱ������ʼ��	  
	pwmInit();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	motorInit();
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 1;
	BIN2 = 0;

	tim1PwmInit(899, 0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
//	tim3PwmInit(899, 0);
	while (1)
	{
		delay_ms(10);
		if (dir)
			pwmVal += 10;
		else
			pwmVal -= 10;

		if (pwmVal > 100)
			dir = 0;
		if (pwmVal == 0)
			dir = 1;
		TIM_SetCompare1(TIM1, pwmVal);
		TIM_SetCompare3(TIM1, pwmVal);
		if (FPS == 1)
		{
			TIM_SetCompare1(TIM1, 100);
			TIM_SetCompare3(TIM1, 0);
			delay_ms(2000);
		}
	}
}


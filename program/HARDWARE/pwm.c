#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>
#include "pwm.h"

//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void  motorInit(void)
{
	GPIO_InitTypeDef gpioInitStructureA;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpioInitStructureA.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpioInitStructureA.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStructureA);
	GPIO_SetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
}

void photoInit(void)
{
	GPIO_InitTypeDef gpioInitStructureB;

	RCC_APB2PeriphClockCmd(SIGNAL_CLK, ENABLE);
	gpioInitStructureB.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	gpioInitStructureB.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(SIGNAL_PORT, &gpioInitStructureB);
}

void tim1PwmInit(const u16 arr, const u16 psc)
{
	GPIO_InitTypeDef gpioInitStructure;
	TIM_TimeBaseInitTypeDef  timTimeBaseStructure;
	TIM_OCInitTypeDef  timOcInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����ʱ��ʹ��

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	gpioInitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //TIM_CH1
	gpioInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStructure);

	timTimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	timTimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	timTimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	timTimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &timTimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	timOcInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	timOcInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	timOcInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	timOcInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM1, &timOcInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC3Init(TIM1, &timOcInitStructure);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);	//MOE �����ʹ��	

	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
}

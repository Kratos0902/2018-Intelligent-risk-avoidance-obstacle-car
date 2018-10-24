#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>
#include "pwm.h"

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设时钟使能

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	gpioInitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //TIM_CH1
	gpioInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStructure);

	timTimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	timTimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	timTimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	timTimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &timTimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	timOcInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	timOcInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	timOcInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	timOcInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM1, &timOcInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC3Init(TIM1, &timOcInitStructure);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);	//MOE 主输出使能	

	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}

#include "optoelectronic_switch.h"
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>	   

void pwmInit(void)
{
	GPIO_InitTypeDef  gpioInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟

	gpioInitStructure.GPIO_Pin = GPIO_Pin_8;
	gpioInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);

	gpioInitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &gpioInitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
}

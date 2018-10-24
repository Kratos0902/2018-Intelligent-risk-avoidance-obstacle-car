#ifndef PWM_H
#define PWM_H

#include "sys.h"

#define SIGNAL_PORT GPIOB
#define SIGNAL_CLK RCC_APB2Periph_GPIOB

void tim1PwmInit(u16 arr, u16 psc);
void motorInit(void);
void photoInit(void);

#endif //PWM_H


#ifndef TIM_H_
#define TIM_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void TIM1_PWM_Init(void);
void TIM0_Init(void);
void TIM2_Init(void);
void PWM_Set(unsigned char pro_100, unsigned int f_nHZ);

#endif /* TIM_H_ */
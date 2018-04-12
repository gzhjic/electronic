#include "TIM.h"


/* 定时器0初始化*/
void TIM0_Init(void)
{
	TCCR0 = 0X05;	//1024分频
	TCNT0 = 68;		//约24sm进入一次中断
	TIMSK |= 1;		//溢出中断使能
}


/*定时器2初始化*/
void TIM2_Init(void)
{
	TCCR2 = 4;		//64分频
	TCNT2 = 131;	//1ms进入一次中断
	TIMSK |= 1<<6;	//溢出中断使能
}


/*定时器1PWM输出初始化*/
void TIM1_PWM_Init(void)
{
	DDRD |= 1<<5;
	TCCR1A = 0X82;	//比较匹配时为0，快速PWM模式
	TCCR1B = 0X1A;  //快速PWM模式，8分频
	ICR1 =	1000;	//周期1ms
	OCR1A = 900;
}


/************************************
	PWM设置函数  
	pro_100:占空比(0-100)
	f_nHZ:  频率nHZ
***********************************/
void PWM_Set(unsigned char pro_100, unsigned int f_nHZ)
{
	ICR1 = (unsigned int)(1000000/f_nHZ);
	OCR1A = ((float)pro_100/100)*ICR1;
} 


#include "tim.h"


void timer0_init(void)
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;
    TMOD &= ~0x0f;
    ET0 = 1;
    TR0 = 1;
}


void timer1_init(void)
{
    TH1 = 0;
    TL1 = 0;
    TMOD &= ~0xf0;
    ET1 = 0;
    TR1 = 0;
}


void timer2_init(void)		//10微秒@12.000MHz
{
    T2L = 0xF6;		//设置定时初值
	T2H = 0xFF;		//设置定时初值
    AUXR |= 0x10; 
    IE2 |= 0x04;
}




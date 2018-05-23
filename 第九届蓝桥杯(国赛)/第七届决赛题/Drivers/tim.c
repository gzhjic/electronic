#include "tim.h"


void timer0_init(void)
{
    TH0 = 0x00;
    TL0 = 0x00;
    TMOD &= ~0x0f;
    TMOD |= 0x04;
    TR0 = 1;
}


void timer1_init(void)
{
    TH1 = (65536-1000)/256;
    TL1 = (65536-1000)%256;
    TMOD &= ~0xf0;
    ET1 = 1;
    TR1 = 1;
}


void timer2_init(void)  //1毫秒@11.0592MHz
{
    AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0x66;		    //设置定时初值
	T2H = 0xFC;		    //设置定时初值
	AUXR |= 0x10;		//定时器2开始计时
    IE2 |= 0x04;
}




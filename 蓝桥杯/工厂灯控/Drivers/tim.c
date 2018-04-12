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
    TH1 = (65536-1000)/256;
    TL1 = (65536-1000)%256;
    TMOD &= ~0xf0;
    ET1 = 1;
    TR1 = 1;
}


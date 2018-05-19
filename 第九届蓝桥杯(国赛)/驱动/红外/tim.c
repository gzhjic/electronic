#include "tim.h"


void timer0_init(void)
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;
    TMOD &= ~0x0f;
    ET0 = 1;
    TR0 = 1;
}


void ext0_init(void)
{
    EX0=1;
	IT0=1;
}
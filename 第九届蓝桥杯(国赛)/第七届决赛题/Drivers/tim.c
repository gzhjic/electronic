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


void timer2_init(void)  //1����@11.0592MHz
{
    AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	T2L = 0x66;		    //���ö�ʱ��ֵ
	T2H = 0xFC;		    //���ö�ʱ��ֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
    IE2 |= 0x04;
}




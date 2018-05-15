#include <stc15f2k60s2.h> 
#include <absacc.h>
#include <intrins.h>
#include "display.h"
#include "tim.h"
#include "sonic.h"

uint dat;

/* º¯ÊýÉùÃ÷ */ 
void init(void);
void board_init(void);
void Delay10ms();

void main(void)
{
    init();
    while(1)
    {
        dat = sonic_get();
        Delay10ms();
    }
}


void init(void)
{
    EA = 0;
    board_init();
    timer0_init();
    timer1_init();
    timer2_init();
    EA = 1;
}


void board_init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0X00;
    XBYTE[0XC000] = 0XFF;
    XBYTE[0XE000] = 0XFF;
}


void timer0_isr(void) interrupt 1
{
    display_smg(0,0,dat/100,dat%100);
}


void timer2_isr(void) interrupt 12
{
    sonic_sent();
}


void Delay10ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 117;
	j = 184;
	do
	{
		while (--j);
	} while (--i);
}


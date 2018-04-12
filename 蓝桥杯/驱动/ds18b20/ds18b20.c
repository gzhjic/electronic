#include "ds18b20.h"
#include "intrins.h"

sbit dq=P1^4;

void Delay480us()		//@12.000MHz
{
	unsigned char i, j;

	i = 6;
	j = 151;
	do
	{
		while (--j);
	} while (--i);
}

void Delay65us()		//@12.000MHz
{
	unsigned char i, j;

	i = 1;
	j = 191;
	do
	{
		while (--j);
	} while (--i);
}


void init(void)
{
    dq=0;
    Delay480us();
    dq=1;
    Delay480us();
}


void write(uchar dat)
{
    uchar i;
    for(i=0;i<8;i++)
    {
        dq=0;
        dq=dat&0x01;
        Delay65us();
        dq=1;
        dat>>=1;
    }
}

uchar read(void)
{
    uchar i,dat;
    for(i=0;i<8;i++)
    {
        dq=0;
        dat>>=1;
        dq=1;
        if(dq)
            dat|=0x80;
        Delay65us();
    }
    return dat;
}


uchar Get_Temp(void)
{
    uchar l,h;
    init();
    write(0xcc);
    write(0x44);
    init();
    write(0xcc);
    write(0xbe);
    l=read();
    h=read();
    return (l>>4)|(h<<4);
}
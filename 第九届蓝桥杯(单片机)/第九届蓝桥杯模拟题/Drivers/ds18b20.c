#include "ds18b20.h"

static void Delay480us()		//@12.000MHz
{
	unsigned char i, j;

	i = 6;
	j = 151;
	do
	{
		while (--j);
	} while (--i);
}

static void Delay60us()		//@12.000MHz
{
	unsigned char i, j;

	i = 1;
	j = 191;
	do
	{
		while (--j);
	} while (--i);
}



static void ds_init(void)
{
    DQ = 0;
    Delay480us();
    DQ = 1;
    Delay480us();
}

static void ds_write(uchar dat)
{
    uchar i;
    for(i=0;i<8;i++)
    {
        DQ = 0;
        DQ = dat&0x01;
        Delay60us();
        DQ = 1;
        dat>>=1;
    }
   // Delay60us();
}

static uchar ds_read(void)
{
    uchar i,dat;
    for(i=0;i<8;i++)
    {
        dat>>=1;
        DQ = 0;
        DQ = 1;
        if(DQ)
            dat|=0x80;
        else
            dat|=0x00;
        Delay60us();
    }
    return dat;
}

uint get_temp(void)
{
    uchar h,l;
    float dat;
    ds_init();
    ds_write(0xcc);
    ds_write(0x44);
    Delay480us();
    ds_init();
    ds_write(0xcc);
    ds_write(0xbe);
    l = ds_read();
    h = ds_read();
    dat = ((h<<8)+l)*6.25;
    return dat;
}
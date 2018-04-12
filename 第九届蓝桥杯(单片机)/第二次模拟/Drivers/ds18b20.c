
#include "stc15f2k60s2.h"
#include "absacc.h"
#include "intrins.h"
#include "ds18b20.h"

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


void init_ds18b20(void)
{
	 DQ=0;
	 Delay480us();
	 DQ=1;
	 Delay480us();
}

void write_ds18b20(uchar dat)
{
	uchar k;
	for(k=0;k<8;k++)
	{
		DQ=0;
		DQ=dat&0x01;
		Delay65us();
		DQ=1;
		dat>>=1;	 
	}
	Delay65us();
}

uchar read_ds18b20(void)
{
	uchar k,temp;
	for(k=0;k<8;k++)
	{	
		temp>>=1;
		DQ=0; 
		DQ=1;
		if(DQ==1)
		temp|=0x80;
		else
		temp|=0x00;
		Delay65us();
	}
	return temp;
}

uchar get_temp(void)
{
	uchar a,b,c;
	init_ds18b20();
	write_ds18b20(0xCC);
	write_ds18b20(0x44);

	Delay480us();
	
	init_ds18b20();
	write_ds18b20(0xCC);
	write_ds18b20(0xbe);

	a=read_ds18b20();
	b=read_ds18b20();
	c=(a>>4)|(b<<4);
	return c;		
}

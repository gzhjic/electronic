
#include "i2c.h"


sbit scl=P2^0;
sbit sda=P2^1;

void delay5us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	_nop_();
	i = 12;
	while (--i);
}

void start(void)
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
	sda=0;
	delay5us();		
}

void stop(void)
{
	sda=0;
	delay5us();
	scl=1;
	delay5us();
	sda=1;
	delay5us();
}

void ack(void)
{
	uchar i;
	scl=1;
	delay5us();
	while((sda==1)&&(i<200))i++;
	scl=0;
	delay5us();
}

void noack(void)
{
	scl=1;
	delay5us();
	sda=1;
	delay5us();
	scl=0;
	delay5us();
}


void write_byte(uchar dat)
{
	uchar z;
	scl=0;	
	for(z=0;z<8;z++)
	{		
		delay5us();		
		if(dat&0x80)
		sda=1;
		else
		sda=0;
		dat<<=1;
		delay5us();
		scl=1;
		delay5us();
		scl=0;
	}
	//sda=1;
}

uchar read_byte(void)
{
	uchar z,dat;
	scl=0;
	delay5us();
	sda=1;
	delay5us();
	for(z=0;z<8;z++)
	{
		scl=1;
		dat<<=1;
		delay5us();
		if(sda)
		dat|=1;
		scl=0;
		delay5us();
	}
	return dat;	
}

void write_at24c02(uchar add,uchar dat)
{
	start();
	write_byte(0xa0);
	ack();
	write_byte(add);
	ack();
	write_byte(dat);
	ack();
	stop();
}

uchar read_at24c02(uchar add)
{
	uchar dat;
	//init();
	start();
	write_byte(0xa0);
	ack();
	write_byte(add);
	ack();
	start();
	write_byte(0xa1);
	ack();
	dat=read_byte();
	noack();
	stop();
	return dat;	
}
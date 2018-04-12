#include "i2c.h"

void Delay5us()		//@12.000MHz
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
    Delay5us();
    scl=1;
    Delay5us();
    sda=0;
}

void stop(void)
{
    sda=0;
    Delay5us();
    scl=1;
    Delay5us();
    sda=1;
}


void ack(void)
{
    uchar i=200;
    scl=1;
    Delay5us();
    while(sda==1&&i--);
    Delay5us();
    scl=0;
}

void noack(void)
{
    uchar i=200;
    scl=1;
    Delay5us();
    sda=1;
    Delay5us();
    scl=0;
}


void byte_write(uchar dat)
{
    uchar i;

    for(i=0;i<8;i++)
    {   
        scl=0;
        Delay5us();
        if(dat&0x80)
            sda=1;
        else
            sda=0;
        dat<<=1;
        Delay5us();
        scl=1;
        Delay5us();
        
    }
    scl=0;
   
}


uchar byte_read(void)
{
    uchar i,dat;
     sda=1;
    for(i=0;i<8;i++)
    {
        scl=1;
        dat<<=1;
        Delay5us();
        if(sda==1)
            dat++;
        Delay5us();
        scl=0;
        Delay5us();
    }
    return dat;
}


void Write_At24c02(uchar add,uchar dat)
{
    start();
    byte_write(0xa0);
    ack();
    byte_write(add);
    ack();
    byte_write(dat);
    ack();
    stop();
}

uchar  Read_At24c02(uchar add)
{
    uchar dat;
    start();
    byte_write(0xa0);
    ack();
    byte_write(add);
    ack();
    start();
    byte_write(0xa1);
    ack();
    dat=byte_read();
    noack();
    stop();
    return dat;
}
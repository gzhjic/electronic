#include "iic.h"

sbit scl = P2^0;
sbit sda = P2^1;


void Delay5us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 12;
	while (--i);
}


void iic_start(void)
{
    sda = 1;
    Delay5us();
    scl = 1;
    Delay5us();
    sda = 0;
    Delay5us();
}


void iic_stop(void)
{
    sda = 0;
    Delay5us();
    scl = 1;
    Delay5us();
    sda = 1;
    Delay5us();
}


void iic_ack(void)
{
    uchar i = 200;
    scl = 1;
    Delay5us();
    while(sda&&i--);
    Delay5us();
    scl = 0;
}


void iic_nack(void)
{
    scl = 1;
    Delay5us();
    sda = 1;
    Delay5us();
    scl = 0;
    Delay5us();
}


void iic_mack(void)
{
    sda = 0;
    Delay5us();
    scl = 1;
    Delay5us();
    scl = 0;
    Delay5us();
    sda = 1;
}


void iic_write(uchar dat)
{
    uchar i;
    for(i = 0; i < 8; i++)
    {
        scl = 0;
        Delay5us();
        if(dat&0x80)
            sda = 1;
        else
            sda = 0;
        Delay5us();
        scl = 1;
        dat<<=1;
    }
    scl = 0;
}


uchar iic_read(void)
{
    uchar i,dat;
    sda = 1;
    for(i = 0; i < 8 ; i++)
    {
        dat<<=1;
        scl = 1;
        Delay5us();
        if(sda)
            dat |= 1;
        Delay5us();
        scl = 0;
        Delay5us();
    }
    return dat;
}


void Write_At24c02(uchar add,uchar dat)
{
    iic_start();
    iic_write(0xa0);
    iic_ack();
    iic_write(add);
    iic_ack();
    iic_write(dat);
    iic_ack();
    iic_stop();
}


void at24c02_read_buffer(uchar add,uchar *dat, uchar num)
{
    uchar i;
    iic_start();
    iic_write(0xa0);
    iic_ack();
    iic_write(add);
    iic_ack();
    iic_start();
    iic_write(0xa1);
    iic_ack();
    for(i = 0;i<num;i++)
    {
        *dat = iic_read();
        iic_mack();
        dat++;
    }
    iic_nack();
    iic_stop();
}


uchar dac_read(uchar add)
{
    uchar temp;
    iic_start();
    iic_write(0x90);
    iic_ack();
    iic_write(add);
    iic_ack();
    iic_start();
    iic_write(0x91);
    iic_ack();
    temp = iic_read();
    iic_nack();
    iic_stop();
    return temp;
}

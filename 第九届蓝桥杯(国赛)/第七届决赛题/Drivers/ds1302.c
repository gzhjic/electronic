#include "ds1302.h"

sbit io = P2^3;
sbit sck = P1^7;
sbit rst = P1^3;

static uchar hex_bcd(uchar dat)
{
    return dat/10*16+dat%10;
}

static uchar bcd_hex(uchar dat)
{
    return dat/16*10+dat%16;
}

static void write(uchar dat)
{
    uchar i;
    for(i=0;i<8;i++)
    {
        sck = 0;
        io = dat&1;
        dat>>=1;
        sck = 1;
        
    }
}


static uchar read(void)
{
    uchar i,dat;
    io = 1;
    for(i=0;i<8;i++)
    {
        dat>>=1;
        sck = 0;
        if(io)
            dat|=0x80;
        sck = 1;
    }
    return dat;
}


void ds1302_write(uchar add,uchar dat)
{
    rst = 0;
    io = 0;
    sck = 0;
    rst = 1;
    dat = hex_bcd(dat);
    write(add);
    write(dat);
    rst = 0;
}

uchar ds1302_read(uchar add)
{
    uchar dat;
    rst = 0;
    io = 0;
    sck = 0;
    rst = 1;
    dat = hex_bcd(dat);
    write(add);
    dat = read();
    rst = 0;
    return bcd_hex(dat);
}


void ds1302_init(void)
{
    ds1302_write(0x8e,0);
    ds1302_write(ds_w_sec,0);
    ds1302_write(ds_w_min,59);
    ds1302_write(ds_w_hour,23);
    ds1302_write(0x8e,0x80);
}




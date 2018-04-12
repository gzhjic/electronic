#include "ds1302.h"

void byte_write(uchar dat)
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

uchar byte_read(void)
{
    uchar i,dat;
    for(i=0;i<8;i++)
    {
        dat>>=1;
        sck = 0;
        if(io == 1)
            dat|=0x80;
        sck = 1;
    }
    return dat;
}

uchar hex_to_bcd(uchar dat)
{
    return (dat/10)*16+(dat%10);
}

uchar bcd_to_hex(uchar dat)
{
    return (dat/16)*10+(dat%16);
}

void write_ds1302(uchar addr,uchar dat)
{
    dat = hex_to_bcd(dat);
    rst = 0;
    sck = 0;
    io = 0;
    rst = 1;
    byte_write(addr);
    byte_write(dat);
    rst = 0;
}

uchar read_ds1302(uchar addr)
{
    
    rst = 0;
    sck = 0;
    io=0;
    rst = 1;
    byte_write(addr);

    return bcd_to_hex(byte_read());
}

void set_time(void)
{
    write_ds1302(0x8e,0);
    write_ds1302(0x80,10);
    write_ds1302(0x8e,0);
    write_ds1302(0x82,10);
    write_ds1302(0x84,12);
    write_ds1302(0x86,10);
    write_ds1302(0x88,3);
    write_ds1302(0x8a,6);
    write_ds1302(0x8c,5);
    write_ds1302(0x8e,0x80);
}
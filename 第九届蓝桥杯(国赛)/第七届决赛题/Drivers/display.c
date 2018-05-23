#include "display.h"


const uchar smg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf,0xc6,0x8e};


void Display_Time(uchar hour,uchar min,uchar sec,uchar flash)
{
	static uchar i;
    uchar buf[8];
    
    if(flash == 1)
    {
        buf[0] = smg_code[SMG_OFF];
        buf[1] = smg_code[SMG_OFF];
    }
    else
    {
        buf[0] = smg_code[hour/10];
        buf[1] = smg_code[hour%10];
    }
    buf[2] = smg_code[SMG_G];
    if(flash == 2)
    {
        buf[3] = smg_code[SMG_OFF];
        buf[4] = smg_code[SMG_OFF];
    }
    else
    {
        buf[3] = smg_code[min/10];
        buf[4] = smg_code[min%10];
    }
    buf[5] = smg_code[SMG_G];
    if(flash ==3)
    {
        buf[6] = smg_code[SMG_OFF];
        buf[7] = smg_code[SMG_OFF];
    }
    else
    {
        buf[6] = smg_code[sec/10];
        buf[7] = smg_code[sec%10];
    }
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


void Display_mV(uint mv)
{
    static uchar i;
    uchar buf[8];
    
    buf[0] = smg_code[SMG_G];
    buf[1] = smg_code[1];
    buf[2] = smg_code[SMG_G];
    buf[3] = smg_code[SMG_OFF];
    buf[4] = smg_code[mv/1000];
    buf[5] = smg_code[mv/100%10];
    buf[6] = smg_code[mv/10%10];
    buf[7] = smg_code[mv%10];
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


void Display_Set(uint top,uint button,uchar flash)
{
    static uchar i;
    uchar buf[8];
    
    if(flash ==1)
    {
        buf[0] = smg_code[SMG_OFF];
        buf[1] = smg_code[SMG_OFF];
        buf[2] = smg_code[SMG_OFF];
        buf[3] = smg_code[SMG_OFF];
    }
    else
    {
        buf[0] = smg_code[top/1000];
        buf[1] = smg_code[top/100%10];
        buf[2] = smg_code[top/10%10];
        buf[3] = smg_code[top%10];
    }
    if(flash ==2)
    {
        buf[4] = smg_code[SMG_OFF];
        buf[5] = smg_code[SMG_OFF];
        buf[6] = smg_code[SMG_OFF];
        buf[7] = smg_code[SMG_OFF];
    }
    else
    {
        buf[4] = smg_code[button/1000];
        buf[5] = smg_code[button/100%10];
        buf[6] = smg_code[button/10%10];
        buf[7] = smg_code[button%10];
    }
    
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


void Display_F(uint f)
{
    static uchar i;
    uchar buf[8];
    
    buf[0] = smg_code[SMG_G];
    buf[1] = smg_code[2];
    buf[2] = smg_code[SMG_G];
    buf[3] = smg_code[f/10000];
    buf[4] = smg_code[f/1000%10];
    buf[5] = smg_code[f/100%10];
    buf[6] = smg_code[f/10%10];
    buf[7] = smg_code[f%10];
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


void Display_Type(uchar type)
{
    static uchar i;
    uchar buf[2];
    
    buf[0] = smg_code[0];
    buf[1] = smg_code[type];

    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<(6+i);
    XBYTE[0XE000] = buf[i];
    
    if(++i>=2)
        i = 0;
}

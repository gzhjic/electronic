#include "display.h"


const uchar smg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf,0xc6,0x8e};


void display_c(uint sum1,uint sum2)
{
	static uchar i;
    uchar buf[8];
    
    buf[0] = smg_code[SMG_C];
    buf[1] = smg_code[SMG_OFF];
    buf[2] = smg_code[sum1/100];
    buf[3] = smg_code[sum1/10%10];
    buf[4] = smg_code[sum1%10];
    buf[5] = smg_code[sum2/100];
    buf[6] = smg_code[sum2/10%10];
    buf[7] = smg_code[sum2%10];
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


void display_b(uchar num, uint sum)
{
	static uchar i;
    uchar buf[8];
    
    buf[0] = smg_code[num];
    buf[1] = smg_code[SMG_OFF];
    buf[2] = smg_code[SMG_OFF];
    buf[3] = smg_code[SMG_OFF];
    buf[4] = smg_code[SMG_OFF];
    buf[5] = smg_code[sum/100];
    buf[6] = smg_code[sum/10%10];
    buf[7] = smg_code[sum%10];
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


void display_f(uchar sum)
{
	static uchar i;
    uchar buf[8];
    
    buf[0] = smg_code[SMG_F];
    buf[1] = smg_code[SMG_OFF];
    buf[2] = smg_code[SMG_OFF];
    buf[3] = smg_code[SMG_OFF];
    buf[4] = smg_code[SMG_OFF];
    buf[5] = smg_code[SMG_OFF];
    buf[6] = smg_code[sum/10];
    buf[7] = smg_code[sum%10];
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


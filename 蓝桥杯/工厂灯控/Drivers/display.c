#include "display.h"


const uchar smg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf,0xc6};


void display_time(uchar h,uchar m,uchar s)
{
	static uchar i;
    uchar buf[8];
    
    buf[0] = smg_code[h/10];
    buf[1] = smg_code[h%10];
    buf[2] = smg_code[SMG_G];
    buf[3] = smg_code[m/10];
    buf[4] = smg_code[m%10];
    buf[5] = smg_code[SMG_G];
    buf[6] = smg_code[s/10];
    buf[7] = smg_code[s%10];
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}


void display_test(uchar w)
{
    XBYTE[0XE000] = 0;
    XBYTE[0XC000] = w;
}

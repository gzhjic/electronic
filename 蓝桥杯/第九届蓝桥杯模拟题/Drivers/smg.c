#include "smg.h"

const uchar smg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf,0xc6};

static void smg_display
                (uchar sum1, uchar sum2,
                 uchar sum3, uchar sum4,
                 uchar sum5, uchar sum6,
                 uchar sum7, uchar sum8)

{
    static uchar i;
    uchar buf[8];
    
    buf[0] = smg_code[sum1];
    buf[1] = smg_code[sum2];
    buf[2] = smg_code[sum3];
    buf[3] = smg_code[sum4];
    buf[4] = smg_code[sum5];
    buf[5] = smg_code[sum6];
    buf[6] = smg_code[sum7];
    buf[7] = smg_code[sum8];
    
    XBYTE[0XE000] = 0xff;
    XBYTE[0XC000] = 1<<i;
    XBYTE[0XE000] = buf[i];
    
    if(++i>=8)
        i = 0;
}

void smg_dis_time(uchar hour, uchar min, uchar sec, uchar flash)
{
    switch (flash)
    {
        case 0:
            smg_display(hour/10,
                        hour%10,
                        smg_g,
                        min/10,
                        min%10,
                        smg_g,
                        sec/10,
                        sec%10);
            break;
        
        case smg_flash_hour :
            smg_display(smg_off,
                        smg_off,
                        smg_g,
                        min/10,
                        min%10,
                        smg_g,
                        sec/10,
                        sec%10);
            break;
        
        case smg_flash_min :
            smg_display(hour/10,
                        hour%10,
                        smg_g,
                        smg_off,
                        smg_off,
                        smg_g,
                        sec/10,
                        sec%10);
            break;
        
        case smg_flash_sec:
            smg_display(hour/10,
                        hour%10,
                        smg_g,
                        min/10,
                        min%10,
                        smg_g,
                        smg_off,
                        smg_off);
    }
}

void smg_dis_temp(uchar temp)
{
    smg_display(smg_off,
                smg_off,
                smg_off,
                smg_off,
                smg_off,
                temp/10,
                temp%10,
                smg_c);
}

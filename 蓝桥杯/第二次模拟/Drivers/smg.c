#include "smg.h"

uchar smg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf,0xc6};

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


void dis_time(uchar hour, uchar min, uchar sec)
{
    smg_display(hour/10,
                hour%10,
                SMG_G,
                min/10,
                min%10,
                SMG_G,
                sec/10,
                sec%10);
}

void dis_worring(uchar mod, uchar min, uchar sec)
{
    smg_display(SMG_G,
                mod,
                SMG_G,
                min/10,
                min%10,
                SMG_G,
                sec/10,
                sec%10);
}


void dis_temp(uchar min, uchar max,uchar temp)
{
    smg_display(min/10,
                min%10,
                SMG_G,
                max/10,
                max%10,
                SMG_G,
                temp/10,
                temp%10);
}


void dis_set(uchar min_h, uchar min_l,
              uchar max_h, uchar max_l,
              uchar temp, uchar flash)
{
    switch(flash)
    {
        case 0:
            smg_display(min_h,
                        min_l,
                        SMG_G,
                        max_h,
                        max_l,
                        SMG_G,
                        temp/10,
                        temp%10);
            break;
        
        case 1:
            smg_display(SMG_OFF,
                        min_l,
                        SMG_G,
                        max_h,
                        max_l,
                        SMG_G,
                        temp/10,
                        temp%10);
            break;
        
        case 2:
            smg_display(min_h,
                        SMG_OFF,
                        SMG_G,
                        max_h,
                        max_l,
                        SMG_G,
                        temp/10,
                        temp%10);
            break;
        
        case 3:
            smg_display(min_h,
                        min_l,
                        SMG_G,
                        SMG_OFF,
                        max_l,
                        SMG_G,
                        temp/10,
                        temp%10);
            break;
        
        case 4:
            smg_display(min_h,
                        min_l,
                        SMG_G,
                        max_h,
                        SMG_OFF,
                        SMG_G,
                        temp/10,
                        temp%10);
            break;
    }
    
}
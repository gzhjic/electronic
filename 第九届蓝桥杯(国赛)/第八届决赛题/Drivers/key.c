#include "key.h"

bit flag;

void key_on(void)
{
    static uchar i;
    P3 = 0x0f;
    if( (P3&0x0f) != 0x0f)
    {
        if(i >= 30)
        {
            i = 30;
            flag = 1;
        }
        else
            i++;
    }
    else
    {
        i = 0;
        flag = 0;
    }
}


uchar key_scanf(void)
{
    uchar num=0;
    if(flag)
    {
        if     (P30 == 0)
        {
            num =  S7_ON;
            while(flag);
        }
        else if(P31 == 0)
        {
            num =  S6_ON;
            while(flag);
        }
        else if(P32 == 0)
        {
            num =  S5_ON;
            while(flag);
        }
        else if(P33 == 0)
        {
            num =  S4_ON;
            while(flag);
        }
    }
    return num;
}
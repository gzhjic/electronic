#include "key.h"

bit key_on(void)
{
    bit flag;
    static uchar i;
    P3 = 0x0f;
    if( (P3&0x0f) != 0x0f)
    {
        if(i >= 15)
        {
            i = 15;
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
    return flag;
}


uchar key_scanf(void)
{
    if     (P30 == 0)
        return S7_ON;
    else if(P31 == 0)
        return S6_ON;
    else if(P32 == 0)
        return S5_ON;
    else if(P33 == 0)
        return S4_ON;
    else
        return 0;
}
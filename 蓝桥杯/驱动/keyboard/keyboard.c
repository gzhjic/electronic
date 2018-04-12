
#include "key.h"

bit key_flag;

static unsigned char GetKey(void)
{
    unsigned char i;
    P42 = 1;
    P44 = 1;
    for(i=0;i<4;i++)
    {   
        P3=~(1<<i);
        if     (P44 == 0)    return i*4+1;
        else if(P42 == 0)    return i*4+2;
        else if(P35 == 0)    return i*4+3;
        else if(P34 == 0)    return i*4+4;
    }
    return 0;
}


void key_on(void)
{
    static uchar count;
    if(GetKey()>0)
    {
        if(count<15)
            count++;
        else
        {
            count = 16;
            key_flag = 1;
        }
    }
    else
    {
        key_flag = 0;
        count = 0;
    }
}


uchar key(void)
{
    uchar key_num = 0;
    if(key_flag)
    {
        key_num = GetKey();
        while(key_flag);
    }
    return key_num;
}




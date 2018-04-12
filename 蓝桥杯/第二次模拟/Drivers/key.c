#include "key.h"

extern bit key_flag;    //引用主文件的变量


/*获取键值*/
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


/*对按键滤波消抖*/
bit key_on(void)
{
    static unsigned char j;
    static bit k;
    if(GetKey()>0)             //如果有按下，对按键进行 15*定时器时间的滤波
    {
        if(j>=15)              
            k=1;                //滤波完成
        else
            j++;
    }
    else
    {
        j=0;                    //如果抖动，舍弃信号重新采样
        k=0;
    }
    return k;
}


unsigned char key_scanf(void)
{
    unsigned char b;
    if(key_flag==1)
    {
        b = GetKey();
        while(key_flag==1);
    }
    return b;
}
#include "sonic.h"

sbit SONIC_TX = P1^0;  //发射引脚
sbit SONIC_RX = P1^1;  //接收引脚

static bit sent_flag;

void sonic_sent(void)
{
    static uchar i;
    if(sent_flag)
    {
        SONIC_TX = ~SONIC_TX;
        if(++i>=8)
        {
            i = 0;
            sent_flag = 0;
        }
    }
}


// 200毫秒更新一次数据
uint sonic_get(void)
{
	uint t = 0;
    static uint dat;
    if(!sent_flag)
    {
        TH1 = 0;
        TL1 = 0;
        sent_flag = 1;              //发生8个方波启动超声波模块
        TR1 = 1;                    //开始定时
        while((SONIC_RX==1)&&(TF1==0));   //等待收到脉冲   
        TR1 = 0;                    //关闭定时
        
        if((TF1 == 1))              //无返回|(TH1 & 0x10)
        {
            TF1 = 0;                //没有检测到返回信号，定时器溢出清零
            dat = 9999;            //无返回
        }
        else 
        {
            t = TH1;
            t <<= 8;
            t |= TL1;
            dat = (uint)(t*0.017); //计算距离	
        }
    }
    return dat;
} 
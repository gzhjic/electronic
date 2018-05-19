#include "display.h"
#include "tim.h"
#include "irda.h"

extern long frame_data;
uchar frame_cnt;
extern bit frame_flag;
uchar isr_cnt;
uchar key_val;

/* 函数声明 */ 
void init(void);
void board_init(void);


void main(void)
{
    init();
    while(1)
    {
        ext0_port = ir;
        if(frame_flag == 1)
            key_val = irda_process();
    }
}


void init(void)
{
    EA = 0;
    board_init();
    timer0_init();
    ext0_init();
    EA = 1;
}


void board_init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0X00;
    XBYTE[0XC000] = 0XFF;
    XBYTE[0XE000] = 0XFF;
}


void timer0_isr(void) interrupt 1
{
    display_smg(frame_cnt,isr_cnt,key_val/100,key_val%100);
}


void ext0_isr(void) interrupt 0
{
    uchar pluse_time = 0;
    bit leader_code_flag = 0;
    uchar irda_data = 0;
    
    while(1)
    {
        if(ir)
        {
            pluse_time = get_pluse_time();
            if(pluse_time >= 250)
                break;                                  //>5ms不是有用信号跳出循环
            if(pluse_time >= 200 && pluse_time < 250)   //获得前导位 4ms-4.5ms
                leader_code_flag = 1;
            else if(pluse_time >= 10 && pluse_time<50)  //0.2ms-1ms 数据0
                irda_data = 0;
            else if(pluse_time >= 50 && pluse_time<100) //1ms-2ms   数据1
                irda_data = 1;
            else if(pluse_time>=100 &&pluse_time <= 200)//2ms-4ms 连发码，第二次中断出现
            {
                frame_flag = 1;                         //一帧数据接收完成
                frame_cnt++;                            //按键次数+1
                isr_cnt++;                              //进中断次数+1
                break;
            }
            
            if(leader_code_flag)                        //在第一次中断中完成
            {
                frame_data <<= 1;
                frame_data += irda_data;
                frame_cnt = 0;
                isr_cnt = 1;
            }
        }
    }
}

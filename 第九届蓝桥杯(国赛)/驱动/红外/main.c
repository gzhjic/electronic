#include "display.h"
#include "tim.h"
#include "irda.h"

extern long frame_data;
uchar frame_cnt;
extern bit frame_flag;
uchar isr_cnt;
uchar key_val;

/* �������� */ 
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
                break;                                  //>5ms���������ź�����ѭ��
            if(pluse_time >= 200 && pluse_time < 250)   //���ǰ��λ 4ms-4.5ms
                leader_code_flag = 1;
            else if(pluse_time >= 10 && pluse_time<50)  //0.2ms-1ms ����0
                irda_data = 0;
            else if(pluse_time >= 50 && pluse_time<100) //1ms-2ms   ����1
                irda_data = 1;
            else if(pluse_time>=100 &&pluse_time <= 200)//2ms-4ms �����룬�ڶ����жϳ���
            {
                frame_flag = 1;                         //һ֡���ݽ������
                frame_cnt++;                            //��������+1
                isr_cnt++;                              //���жϴ���+1
                break;
            }
            
            if(leader_code_flag)                        //�ڵ�һ���ж������
            {
                frame_data <<= 1;
                frame_data += irda_data;
                frame_cnt = 0;
                isr_cnt = 1;
            }
        }
    }
}

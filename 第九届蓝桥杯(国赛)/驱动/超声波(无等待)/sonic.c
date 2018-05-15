#include "sonic.h"

sbit SONIC_TX = P1^0;  //��������
sbit SONIC_RX = P1^1;  //��������

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


// 200�������һ������
uint sonic_get(void)
{
	uint t = 0;
    static uint dat;
    if(!sent_flag)
    {
        TH1 = 0;
        TL1 = 0;
        sent_flag = 1;              //����8����������������ģ��
        TR1 = 1;                    //��ʼ��ʱ
        while((SONIC_RX==1)&&(TF1==0));   //�ȴ��յ�����   
        TR1 = 0;                    //�رն�ʱ
        
        if((TF1 == 1))              //�޷���|(TH1 & 0x10)
        {
            TF1 = 0;                //û�м�⵽�����źţ���ʱ���������
            dat = 9999;            //�޷���
        }
        else 
        {
            t = TH1;
            t <<= 8;
            t |= TL1;
            dat = (uint)(t*0.017); //�������	
        }
    }
    return dat;
} 
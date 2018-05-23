#include "tim.h"
#include "display.h"
#include "key.h"
#include "iic.h"
#include "ds1302.h"
#include "tool.h"


/* �궨�� */
#define r_type  0
#define r_hour  1
#define r_min   2
#define r_sec   3
#define r_max   4
#define r_m     5
/* �������� */
enum{
    mod_time,       //��ʾʱ��ģʽ
    mod_time_set,   //����ʱ��ģʽ
    mod_v,          //��ʾ��ѹģʽ
    mod_f,          //��ʾƵ��ģʽ
    mod_set,        //����������ģʽ
    mod_check       //��ʾ����ģʽ
} mode;

struct{
    uchar hour;     //ʱ
    uchar min;      //��
    uchar sec;      //��
    uchar select;   //ѡ��
}time;              //ʱ��

struct{
    uint mea;       //��õ�ѹ
    uint max;       //����ѹ
    uint min;       //��С��ѹ
    uchar select;   //ѡ��
    uchar type;     //��������
}v;                 //��ѹ

SqQueue eeprom;     //дeeprom�������

bit check_f;        //������ʾ��־
bit f_f;            //Ƶ��/����ѡ��
uchar dis_flash;    //��˸��־
uchar r_buf[6];     //��eeprom���ݻ���
uint f;             //Ƶ��
uint f_dis;         //Ƶ��/������ʾ

/* �������� */
void Init(void);
void Board_Init(void);
void Task_Time(void);
void Task_Time_Set(void);
void Time_Add(void);
void Time_Sub(void);
void Task_V(void);
void Task_F(void);
void Task_Set(void);
void Task_Check(void);
void Task_Mark(void);
void Task_Write(void);
void Task_Read(void);


/* ���ݴ����� */
void main(void)
{
    Init();
    while(1)
    {
        switch(mode)//����ģʽѡ������
        {
            case mod_time:Task_Time();break;
            case mod_time_set:Task_Time_Set();break;
            case mod_v:Task_V();break;
            case mod_f:Task_F();break;
            case mod_set:Task_Set();break;
            case mod_check:Task_Check();break;
        }
        Task_Mark();//����ѹ����
        
    }
}


/* Ƶ�ʲ���/ʱ������ */
void timer1_isr(void) interrupt 3
{
    static uint ms,s;
    if(mode == mod_f)       //Ƶ�ʲ���ģʽ��
    {
        TR0 = 1;
        if(++ms>1000)       //ÿ���һ��Ƶ��
        {
            ms = 0;
            f = (TH0*256+TL0);
            TR0 = 0;
            TH0 = 0;
            TL0 = 0;
            TR0 = 1;
        }
    }
    if(mode == mod_time_set)
    {
        if(++s>1000)        //�������˸��ʱ
        {
            s = 0;
            dis_flash = time.select;
        }
        else if(s == 500)
            dis_flash = 0;
    }
    else if(mode == mod_set)
    {
        if(++s>1000)
        {
            s = 0;
            dis_flash = v.select;
        }
        else if(s == 500)
            dis_flash = 0;
    }
    else
        dis_flash = 0;
    
    key_on();               //�����˲�
}


/* ��ʾ/eeprom�������� */
void timer2_isr(void) interrupt 12
{
    switch(mode)
    {
        case mod_time:
        case mod_time_set:
            Display_Time(time.hour,time.min,time.sec,dis_flash);
        break;//��ʾʱ��
        
        case mod_v:
            v.mea = 5000*(float)dac_read(3)/255;        
            Display_mV(v.mea);
        break;//��ʾ������ѹ
        
        case mod_f:
            Display_F(f_dis);
        break;//��ʾƵ��
        
        case mod_set:
            Display_Set(v.max,v.min,dis_flash);
        break;//���õ�ѹ
        
        case mod_check:
            if(check_f)
                Display_Time(r_buf[r_hour],r_buf[r_min],r_buf[r_sec],0);
            else
                Display_Type(r_buf[r_type]);
        break;//��ʾ����
    }        
    Task_Write();//eepromд����
}


/* ��ʼ�� */
void Init(void)
{
    EA = 0;
    init_mempool(0x0000,0x03ff);//���䶯̬�ڴ�1k
    Task_Read();                //����eeprom������
    Board_Init();               //�ص��������޹�����
    InitQueue(&eeprom);         //eeprom������г�ʼ��
//    v.max = 2000;             //Ĭ��ֵ
//    v.min = 1000;
    ds1302_init();              //ʱ��оƬ��ʼ��
    timer0_init();              //��ʱ����ʼ��
    timer1_init();
    timer2_init();
    EA = 1;                     //��ʼ
}


/* �رհ������޹����� */
void Board_Init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0X00;
    XBYTE[0XC000] = 0XFF;
    XBYTE[0XE000] = 0XFF;
}


/* ��ʾʱ������ */
void Task_Time(void)
{
    uchar key_num;
    time.hour = ds1302_read(ds_r_hour);//����ʱ��
    time.min = ds1302_read(ds_r_min);
    time.sec = ds1302_read(ds_r_sec);
    key_num = key();                    //��ȡ��ֵ
    switch(key_num)
    {
        case 13:
            time.select = 1;
            mode = mod_time_set;
        break;                          //�л�ģʽ
        
        case 5:
            mode = mod_v;
        break;
        
        case 10:
            check_f = 0;
            mode = mod_check;
        break;
        
        case 9:
            mode = mod_f;
        break;
    }
}


/* ����ʱ������ */
void Task_Time_Set(void)
{
    uchar key_num;
    key_num = key();                //��ȡ��ֵ
    switch(key_num)
    {
        case 13:
        if(++time.select>3)         //ѡ��ʱ����
            time.select = 1;
        break;
            
        case 2:
            Time_Add();             //ʱ���
        break;
        
        case 6:
            Time_Sub();             //ʱ���
        break;
        
        case 1:                     //дʱ��
            ds1302_write(ds_w_sec,time.sec);
            ds1302_write(ds_w_min,time.min);
            ds1302_write(ds_w_hour,time.hour);
            mode = mod_time;
        break;
    }
}


/* ʱ��� */
void Time_Add(void)
{
    if(time.select == 1)
    {
        if(time.hour<23)
            time.hour++;
    }
    else if(time.select == 2)
    {
        if(time.min<59)
            time.min++;
    }
    else if(time.select == 3)
    {
        if(time.sec<59)
            time.sec++;
    }
}


/* ʱ��� */
void Time_Sub(void)
{
    if(time.select == 1)
    {
        if(time.hour>0)
            time.hour--;
    }
    else if(time.select == 2)
    {
        if(time.min>0)
            time.min--;
    }
    else if(time.select == 3)
    {
        if(time.sec>0)
            time.sec--;
    }
}


/* ��ʾ��ѹ���� */
void Task_V(void)
{
    uchar key_num;
    key_num = key();
    switch(key_num)//�л�����
    {
        case 13:
            v.select = 1;
            mode = mod_set;
        break;
            
        case 5:
            mode = mod_v;
        break;
        
        case 10:
            check_f = 0;
            mode = mod_check;
        break;
        
        case 1:
            mode = mod_time;
        break;
        
        case 9:
            mode = mod_f;
        break;
    }
}


void Task_Set(void)
{
    uchar key_num;
    key_num = key();
    switch(key_num)
    {
        case 13:
            if(++v.select>2)
                v.select = 1;
        break;//ѡ��Ҫ���õĵ�ѹ
            
        case 2:
                if(v.select ==1)
                {
                    if(v.max<5000)
                        v.max+=500;
                }
                else if(v.select ==2)
                {
                    if(v.min<5000)
                        v.min+=500;
                }
        break;//��ѹ��
        
        case 6:
                if(v.select ==1)
                {
                    if(v.max>0)
                        v.max-=500;
                }
                else if(v.select ==2)
                {
                    if(v.min>0)
                        v.min-=500;
                }
        break;//��ѹ��
                
        case 5:
            r_buf[r_max] = v.max/100;
            EnQueue(&eeprom,4);
            r_buf[r_min] = v.min/100;
            EnQueue(&eeprom,5);
            mode = mod_v;
        break;//����2��дeeprom����
    }
}


/* ������ʾ���� */
void Task_Check(void)
{
    uchar key_num;
    key_num = key();
    switch(key_num)
    {
        case 13:
            check_f = ~check_f;
        break;//�л���ʾ
        
        case 5:
            mode = mod_v;
        break;
        
        case 9:
            mode = mod_f;
        break;
    }
}


/* Ƶ����ʾ���� */
void Task_F(void)
{
    uchar key_num;
    key_num = key();
    switch(key_num)//�л�����
    {
        case 13:
            f_f = ~f_f;
        break;
            
        case 5:
            mode = mod_v;
        break;
        
        case 10:
            check_f = 0;
            mode = mod_check;
        break;
        
        case 1:
            mode = mod_time;
        break;
        
        case 9:
            mode = mod_f;
        break;
    }
    if(f_f)
        f_dis = f;                  //��ʾƵ��
    else
        f_dis = 1000000*1/(float)f; //��ʾ����
}


/* ��ѹ����������� */
void Task_Mark(void)
{
   if(v.mea == v.max)               //��������
   {
       r_buf[r_type] = 1;           //����Ϊ1
       EnQueue(&eeprom, 0);
       r_buf[r_hour] = time.hour;
       EnQueue(&eeprom, 1);
       r_buf[r_min] = time.min;
       EnQueue(&eeprom, 2);
       r_buf[r_sec] = time.sec;
       EnQueue(&eeprom, 3);
   }                                //����3��eepromд����
   else if(v.mea == v.min)          //��������
   {
       r_buf[r_type] = 2;           //����Ϊ1
       EnQueue(&eeprom, 0);
       r_buf[r_hour] = time.hour;
       EnQueue(&eeprom, 1);
       r_buf[r_min] = time.min;
       EnQueue(&eeprom, 2);
       r_buf[r_sec] = time.sec;
       EnQueue(&eeprom, 3);
   }                                //����3��eepromд����
}


/* ִ��eepromд����ĺ��� */
void Task_Write(void)
{
    QElemType e;
    if(QueueLength(eeprom))         //���г��ȴ���һ
    {
        DeQueue(&eeprom, &e);       //����
        Write_At24c02(e,r_buf[e]);
    }
}


/* ��������eeprom���� */
void Task_Read(void)
{
    at24c02_read_buffer(0,r_buf,6); //��eeprom����
    v.max = r_buf[r_max]*100;       //����ת��
    v.min = r_buf[r_min]*100;
}

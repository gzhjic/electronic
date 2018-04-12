#include "ds18b20.h"
#include "ds1302.h"
#include "smg.h"
#include "key.h"

/*�궨��*/
#define mode_display 0
#define mode_set     1
#define mode_clock   2
#define mode_temp    3
#define set_hour     1
#define set_min      2
#define set_sec      3


/*��������*/
bit time_out;
bit led_flag;
bit key_flag;
uchar mode;
uchar tempurter;
uchar set_time_mode;
uchar smg_flash_mode;
uint five_sec_count;
    
struct time{
    uchar hour;
    uchar min;
    uchar sec;}
time_dis,time_set,time_clock;


/*��������*/
void init(void);
void board_init(void);
void interrupt_init(void);

void TaskDisplay(void);
void TaskSet(void);
void TaskClock(void);
void Time_OK(void);
void TimeAdd(void);
void TimeSub(void);
    
    
/*********��ʼ��**************/
void init(void)
{
    board_init();
    set_time();
    interrupt_init();
}


void board_init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0X00;
    XBYTE[0XC000] = 0XFF;
    XBYTE[0XE000] = 0XFF;
}


void interrupt_init(void)
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;
    ET0 = 1;
    TR0 = 1;
    
    TH1 = (65536-1000)/256;
    TL1 = (65536-1000)%256;
    ET1 = 1;
    TR1 = 1;
    
    EA = 1;
}


/***************************************
            ������1:��̨����
****************************************/
void main(void)
{
    init();                  //ϵͳ��ʼ��
    while(1)
	{
		switch (mode)        //��̨�����л�
        {
            case mode_display:
                /*ʱ����ʾ*/
                TaskDisplay();
                break;
            
            case mode_set:
                /*����ʱ��*/
                TaskSet();
                break;
            
            case mode_clock:
                /*��������*/
                TaskClock();
                break;
        }
        
        /*����ʱ�䵽*/
        Time_OK();
	}
}


/*****************************************
                ������2:ǰ����ʾ
*****************************************/
void timer0(void) interrupt 1
{
    TR0 = 0;
    switch (mode)
        {
            case mode_display:
                /*ʱ��*/
                smg_dis_time(time_dis.hour,
                             time_dis.min,
                             time_dis.sec,
                             0);
                break;
            
            case mode_set:
                /*����ʱ��*/
                smg_dis_time(time_set.hour,
                             time_set.min,
                             time_set.sec,
                             smg_flash_mode);
                break;
            
            case mode_clock:
                /*����*/
                smg_dis_time(time_clock.hour,
                             time_clock.min,
                             time_clock.sec,
                             smg_flash_mode);
                break;
            
            case mode_temp:
                /*�¶�*/
                smg_dis_temp(tempurter);
                break;
        }
    TR0 =1;
}


/*****************************************
                ������3:��ʱ
*****************************************/
void timer1(void) interrupt 3
{
    static uint one_sec_count;
    static uint ms_count;
    /*�����˲�����*/
    key_flag = key_on();
    /*�������˸��־*/
    if((mode == mode_set)||(mode == mode_clock))
    {
        one_sec_count++;
        if     (one_sec_count <=500)
            smg_flash_mode = 0;
        else if((one_sec_count < 1000)&&(one_sec_count>500))
            smg_flash_mode = set_time_mode;
        else if(one_sec_count > 1000)
            one_sec_count = 0;
    }
    /*����ʱ��*/
    five_sec_count--;
    if(five_sec_count >0)
    {
        ms_count++;
        if     (ms_count <= 100)
            led_flag =1;
        else if((ms_count >100)&&(ms_count<200))
            led_flag =0;
        else if(ms_count >= 200)
            ms_count = 0;
    }
    else
    {
        ms_count = 0;
        led_flag =0;
    }
}


/*********��̨����1����ʾʱ��*********/
void TaskDisplay(void)
{
    uchar key_num;
    /*����ʱ����*/
    time_dis.sec  = read_ds1302(ds_r_sec);
    time_dis.min  = read_ds1302(ds_r_min);
    time_dis.hour = read_ds1302(ds_r_hour);
    
    if(key_flag)
    {
        key_num = key_scanf();
        if(key_num == S4_ON)
        {
            while(key_flag)
            {
                mode = mode_temp;
                tempurter = get_temp()/100;
            }
            mode = mode_display;
        }
        else
        {
            while(key_flag);
            switch(key_num)
            {
                case S7_ON :
                    time_set.hour = time_dis.hour;
                    time_set.min = time_dis.min;
                    time_set.sec = time_dis.sec;
                
                    set_time_mode = set_hour;
                    mode = mode_set;
                    break;
                
                case S6_ON :
                    time_clock.hour = time_dis.hour;
                    time_clock.min = time_dis.min;
                    time_clock.sec = time_dis.sec;
                
                    set_time_mode = set_hour;
                    mode = mode_clock;
                    break;
            }
        }
    }
}

/*********��̨����2������ʱ��*********/
void TaskSet(void)
{
    uchar key_num;
    if(key_flag)
    {
        key_num = key_scanf();
        while(key_flag);
        switch(key_num)
        {
            case S7_ON :
                if(++set_time_mode >=4)
                {
                    write_ds1302(ds_w_sec,time_set.sec);
                    write_ds1302(ds_w_min,time_set.min);
                    write_ds1302(ds_w_hour,time_set.hour);
                    set_time_mode = 0;
                    mode = mode_display;
                }
                break;
            
            case S5_ON :
                TimeAdd();
                break;
            
            case S4_ON :
                TimeSub();
                break;
        }
    }
}

/*********��̨����3����������*********/
void TaskClock(void)
{
    uchar key_num;
    if(key_flag)
    {
        key_num = key_scanf();
        while(key_flag);
        switch(key_num)
        {
            case S6_ON :
                if(++set_time_mode >=4)
                {
                    set_time_mode = 0;
                    mode = mode_display;
                }
                break;
            
            case S5_ON :
                TimeAdd();
                break;
            
            case S4_ON :
                TimeSub();
                break;
        }
    }
}

/*ʱ������*/
void TimeAdd(void)
{
    if     (mode == mode_set)    //��ͬģʽ���޸Ĳ�ͬ�Ľṹ��
    {
        switch (set_time_mode)          
        {
            case set_hour :
                if(time_set.hour < 24)
                    time_set.hour++;
                break;
            
            case set_min :
                if(time_set.min < 60)
                    time_set.min++;
                break;
            
            case set_sec :
                if(time_set.sec < 60)
                    time_set.sec++;
                break;
        }
    }
    else if(mode == mode_clock)
    {
        switch (set_time_mode)
        {
            case set_hour :
                if(time_clock.hour < 24)
                    time_clock.hour++;
                break;
            
            case set_min :
                if(time_clock.min < 60)
                    time_clock.min++;
                break;
            
            case set_sec :
                if(time_clock.sec < 60)
                    time_clock.sec++;
                break;
        }
    }
    else
        return;
}


/*ʱ�����*/
void TimeSub(void)
{
    if     (mode == mode_set)
    {
        switch (set_time_mode)
        {
            case set_hour :
                if(time_set.hour > 0)
                    time_set.hour--;
                break;
            
            case set_min :
                if(time_set.min > 0)
                    time_set.min--;
                break;
            
            case set_sec :
                if(time_set.sec > 0)
                    time_set.sec--;
                break;
        }
    }
    else if(mode == mode_clock)
    {
        switch (set_time_mode)
        {
            case set_hour :
                if(time_clock.hour > 0)
                    time_clock.hour--;
                break;
            
            case set_min :
                if(time_clock.min > 0)
                    time_clock.min--;
                break;
            
            case set_sec :
                if(time_clock.sec > 0)
                    time_clock.sec--;
                break;
        }
    }
    else
        return;
}

void Time_OK(void)
{
    if  ((time_dis.hour == time_clock.hour) &&
             (time_dis.min == time_clock.min) &&
             (time_dis.sec == time_clock.sec) )
            five_sec_count = 5000;
    /*�������ⰴ�� ����ֹͣ*/
    if(key_flag)
        five_sec_count = 0;
}

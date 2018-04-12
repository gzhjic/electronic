#include "ds18b20.h"
#include "ds1302.h"
#include "key.h"
#include "smg.h"

/*变量声明*/
bit key_flag;
bit led_flash_flag;
uchar tpbuf;
uchar check_mode;
uchar smg_flash;

struct{
    uchar val_count;
    uchar val[5];
    uchar max;
    uchar min;
    uchar now;
}tempurter;

struct{
    uchar hour;
    uchar min;
    uchar sec;
}n_time, w_time, e_time;

enum {
    mode_dis_time   = 0,
    mode_worring    = 1,
    mode_error      = 2,
    mode_dis_temp   = 3,
    mode_set_temp   = 4
}mode = mode_dis_time;

/*函数声明*/
void init(void);
void borad_init(void);
void tim_init(void);
void TaskDisTime(void);
void TaskWorring(void);
void TaskError(void);
void TaskDisTemp(void);
void TaskSetTemp(void);


/*后台*/
void main(void)
{
    init();
    while(1)
    {
        switch (mode)           //任务切换
        {
            case mode_dis_time: //显示时间
                TaskDisTime(); 
                break;
            
            case mode_worring:  //警告
                TaskWorring();
                break;
            
            case mode_error:    //报警
                TaskError();
                break;
            
            case mode_dis_temp: //查询
                TaskDisTemp();
                break;
            
            case mode_set_temp: //设置
                TaskSetTemp();
                break;
        }
    }
}

/*前端显示*/
void timer0(void) interrupt 1
{
    switch (mode)
        {
            case mode_dis_time:         //显示时间和亮第一个灯
                dis_time(n_time.hour,
                         n_time.min,
                         n_time.sec);
            
                XBYTE[0X8000] = ~1;
                break;
            
            case mode_worring:           //警告开继电器
                dis_worring(1,
                            w_time.min,
                            w_time.sec);
            
                XBYTE[0X8000] = ~2;
                XBYTE[0XA000] = 0X10; 
                break;
            
            case mode_error:            //报警开蜂鸣器
                dis_worring(2,
                            e_time.min,
                            e_time.sec);
            
                if(led_flash_flag)
                    XBYTE[0X8000] = ~4;
                else
                    XBYTE[0X8000] = 0xff;
                
                XBYTE[0XA000] = 0X40; 
                break;
            
            case mode_dis_temp:         //显示查询信息
                if     (check_mode == 0)
                    dis_temp(tempurter.min,
                             tempurter.max,
                             tempurter.now);
                else if(check_mode == 1)//翻页
                    dis_worring(1,
                                w_time.min,
                                w_time.sec);
                else if(check_mode == 2)
                    dis_worring(2,
                                e_time.min,
                                e_time.sec);
                break;
            
            case mode_set_temp:         //设置报警温度
                dis_set(tempurter.val[0],
                        tempurter.val[1],
                        tempurter.val[2],
                        tempurter.val[3],
                        tempurter.now,
                        smg_flash);

                break;
        }
}

/*时基*/
void timer1(void) interrupt 3
{
    static uint one_sec_count[4]; 
    
    key_flag = key_on();
    
    one_sec_count[0]++;                 //led闪烁记时
    if     (one_sec_count[0] < 500)
        led_flash_flag = 0;
    else if(one_sec_count[0] >= 500 &&
            one_sec_count[0] <= 1000  )
        led_flash_flag = 1;
    else if(one_sec_count[0] >1000)
        one_sec_count[0] = 0;
    
    if    (mode == mode_error)              //报警模式计时
    {
        if(one_sec_count[1]++ >=1000)
        {
            one_sec_count[1] = 0;
            if(e_time.sec<60)
                e_time.sec++;
            else
            {
                e_time.sec = 0;
                if(e_time.min < 60)
                    e_time.min++;
            }
                
        }
    }
    else if(mode == mode_worring)       //警告模式记时
    {
        if(one_sec_count[2]++ >=1000)
        {
            one_sec_count[2] = 0;
            if(w_time.sec<60)
                w_time.sec++;
            else
            {
                w_time.sec = 0;
                if(w_time.min < 60)
                    w_time.min++;
            }
                
        }
    }
    else if(mode == mode_set_temp)          //数码管闪烁记时
    {
        one_sec_count[3]++;
        if     (one_sec_count[3] < 500)
            smg_flash = 0;
        else if(one_sec_count[3] >= 500 &&
                one_sec_count[3] <= 1000  )
            smg_flash = tempurter.val_count;
        else if(one_sec_count[3] >1000)
            one_sec_count[3] = 0;
    }
}

/*初始化*/
void init(void)
{
    borad_init();
    set_time();
    tim_init();
    tempurter.val[1] = 1;
    tempurter.val[2] = 5;
    tempurter.val[3] = 3;
    tempurter.val[4] = 0;
    tempurter.min = tempurter.val[1]*10+tempurter.val[2];
    tempurter.max = tempurter.val[3]*10+tempurter.val[4];
    tempurter.now = 22;
    tempurter.val_count = 1;
    EA = 1;
}

/*板初始化*/
void borad_init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0;
    XBYTE[0XC000] = 0;
    XBYTE[0XE000] = 0;
}

/*定时器初始化*/
void tim_init(void)
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;
    ET0 = 1;
    TR0 = 1;
    
    TH1 = (65536-1000)/256;
    TL1 = (65536-1000)%256;
    ET1 = 1;
    TR1 = 1;
}

/*显示时间任务*/
void TaskDisTime(void)
{
    uchar key_number;
    //读出时间
    n_time.hour = read_ds1302(DS_R_HOUR);
    n_time.min =  read_ds1302(DS_R_MIN);
    n_time.sec =  read_ds1302(DS_R_SEC);
    //读出温度并对温度滤波
    tpbuf = get_temp();
    if(tpbuf < 85)
        tempurter.now = tpbuf;
    
    if     (tempurter.min <= tempurter.now &&
       tempurter.now <= tempurter.max)
        mode = mode_worring;
    else if(tempurter.now > tempurter.max)
        mode = mode_error;
    //切换按键
    if(key_flag == 1)
    {
        key_number = key_scanf();
        if     (key_number == 13)
            mode = mode_set_temp;
        else if(key_number == 15)
            mode = mode_dis_temp;
    }
}

/*警告任务*/
void TaskWorring(void)
{
    uchar key_number;
    /*退出警告*/
    if(key_flag == 1)
    {
        key_number = key_scanf();
        if     (key_number == 16)
        {
            mode = mode_dis_time;
            XBYTE[0XA000] = 0; 
            XBYTE[0x8000] = 0xff;
        }
    }
}

/*报警任务*/
void TaskError(void)
{
    uchar key_number;
    //退出报警
    if(key_flag == 1)
    {
        key_number = key_scanf();
        if     (key_number == 16)
        {
            mode = mode_dis_time;
            XBYTE[0XA000] = 0; 
            XBYTE[0x8000] = 0xff;
        }
        
    }
}

/*查询任务*/
void TaskDisTemp(void)
{
    uchar key_number;
    //设置温度
//    tempurter.min = tempurter.val[1]*10+tempurter.val[2];
//    tempurter.max = tempurter.val[3]*10+tempurter.val[4];
    //读出温度并滤波
    tpbuf = get_temp();
    if(tpbuf < 85)
        tempurter.now = tpbuf;
    /*切换按键*/
    if(key_flag == 1)
    {
        key_number = key_scanf();
        
        if     (key_number == 16)
            mode = mode_dis_temp;
        else if(key_number == 4)
        {
            if(check_mode < 2)
                check_mode++;
        }
        else if(key_number == 8)
        {
            if(check_mode > 0)
                check_mode--;
        }
        else if(key_number == 16)
        {
            mode = mode_dis_time;
        }
    }
}

/*设置任务*/
void TaskSetTemp(void)
{
    uchar key_number;
    //查询温度
    tpbuf = get_temp();
    if(tpbuf < 85)
        tempurter.now = tpbuf;
    
    if(key_flag == 1)
    {
        key_number = key_scanf();
        
        switch(key_number)
        {
            case 1:tempurter.val[tempurter.val_count] = 1;                  //1
                   if(tempurter.val_count<4)tempurter.val_count++;
                   break;
            case 2:tempurter.val[tempurter.val_count] = 2;                  //2
                   if(tempurter.val_count<4)tempurter.val_count++;
                   break;
            case 3:tempurter.val[tempurter.val_count] = 3;                  //3
                   if(tempurter.val_count<4)tempurter.val_count++;
                   break;
            case 5:tempurter.val[tempurter.val_count] = 4;                  //4
                   if(tempurter.val_count<4)tempurter.val_count++;
                   break;
            case 6:tempurter.val[tempurter.val_count] = 5;                  //5
                   if(tempurter.val_count<4)tempurter.val_count++;
                   break;
            case 7:tempurter.val[tempurter.val_count] = 6;                  //6
                    if(tempurter.val_count<4)tempurter.val_count++;
                    break;
            case 9:tempurter.val[tempurter.val_count] = 7;                  //7
                    if(tempurter.val_count<4)tempurter.val_count++;
                    break;
            case 10:tempurter.val[tempurter.val_count] = 8;                  //8
                    if(tempurter.val_count<4)tempurter.val_count++;
                    break;
            case 11:tempurter.val[tempurter.val_count] = 9;                  //9
                    if(tempurter.val_count<4)tempurter.val_count++;
                    break;
            case 12:                                                        //清除
                tempurter.val[1] = tempurter.val[2] = tempurter.val[3] = tempurter.val[4] =0;
                tempurter.val_count = 1;
            case 14:tempurter.val[tempurter.val_count++] = 0;               //0
                    if(tempurter.val_count<4)tempurter.val_count++;
                    break;
            case 16:tempurter.val_count =1;                                 //推出
                    mode = mode_dis_time;
                    //设置温度
                    tempurter.min = tempurter.val[1]*10+tempurter.val[2];
                    tempurter.max = tempurter.val[3]*10+tempurter.val[4];
                    break;
        }
    }
}
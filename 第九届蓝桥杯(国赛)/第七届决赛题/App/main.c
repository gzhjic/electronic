#include "tim.h"
#include "display.h"
#include "key.h"
#include "iic.h"
#include "ds1302.h"
#include "tool.h"


/* 宏定义 */
#define r_type  0
#define r_hour  1
#define r_min   2
#define r_sec   3
#define r_max   4
#define r_m     5
/* 变量声明 */
enum{
    mod_time,       //显示时间模式
    mod_time_set,   //设置时间模式
    mod_v,          //显示电压模式
    mod_f,          //显示频率模式
    mod_set,        //设置上下限模式
    mod_check       //显示报警模式
} mode;

struct{
    uchar hour;     //时
    uchar min;      //分
    uchar sec;      //秒
    uchar select;   //选择
}time;              //时间

struct{
    uint mea;       //测得电压
    uint max;       //最大电压
    uint min;       //最小电压
    uchar select;   //选择
    uchar type;     //报警类型
}v;                 //电压

SqQueue eeprom;     //写eeprom任务队列

bit check_f;        //报警显示标志
bit f_f;            //频率/周期选择
uchar dis_flash;    //闪烁标志
uchar r_buf[6];     //读eeprom数据缓冲
uint f;             //频率
uint f_dis;         //频率/周期显示

/* 函数声明 */
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


/* 数据处理函数 */
void main(void)
{
    Init();
    while(1)
    {
        switch(mode)//工作模式选择任务
        {
            case mod_time:Task_Time();break;
            case mod_time_set:Task_Time_Set();break;
            case mod_v:Task_V();break;
            case mod_f:Task_F();break;
            case mod_set:Task_Set();break;
            case mod_check:Task_Check();break;
        }
        Task_Mark();//检测电压任务
        
    }
}


/* 频率测量/时基函数 */
void timer1_isr(void) interrupt 3
{
    static uint ms,s;
    if(mode == mod_f)       //频率测量模式下
    {
        TR0 = 1;
        if(++ms>1000)       //每秒测一次频率
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
        if(++s>1000)        //数码管闪烁记时
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
    
    key_on();               //按键滤波
}


/* 显示/eeprom任务处理函数 */
void timer2_isr(void) interrupt 12
{
    switch(mode)
    {
        case mod_time:
        case mod_time_set:
            Display_Time(time.hour,time.min,time.sec,dis_flash);
        break;//显示时间
        
        case mod_v:
            v.mea = 5000*(float)dac_read(3)/255;        
            Display_mV(v.mea);
        break;//显示读出电压
        
        case mod_f:
            Display_F(f_dis);
        break;//显示频率
        
        case mod_set:
            Display_Set(v.max,v.min,dis_flash);
        break;//设置电压
        
        case mod_check:
            if(check_f)
                Display_Time(r_buf[r_hour],r_buf[r_min],r_buf[r_sec],0);
            else
                Display_Type(r_buf[r_type]);
        break;//显示报警
    }        
    Task_Write();//eeprom写任务
}


/* 初始化 */
void Init(void)
{
    EA = 0;
    init_mempool(0x0000,0x03ff);//分配动态内存1k
    Task_Read();                //读出eeprom的数据
    Board_Init();               //关掉板子上无关外设
    InitQueue(&eeprom);         //eeprom任务队列初始化
//    v.max = 2000;             //默认值
//    v.min = 1000;
    ds1302_init();              //时钟芯片初始化
    timer0_init();              //定时器初始化
    timer1_init();
    timer2_init();
    EA = 1;                     //开始
}


/* 关闭板子上无关外设 */
void Board_Init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0X00;
    XBYTE[0XC000] = 0XFF;
    XBYTE[0XE000] = 0XFF;
}


/* 显示时间任务 */
void Task_Time(void)
{
    uchar key_num;
    time.hour = ds1302_read(ds_r_hour);//读出时间
    time.min = ds1302_read(ds_r_min);
    time.sec = ds1302_read(ds_r_sec);
    key_num = key();                    //获取键值
    switch(key_num)
    {
        case 13:
            time.select = 1;
            mode = mod_time_set;
        break;                          //切换模式
        
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


/* 设置时间任务 */
void Task_Time_Set(void)
{
    uchar key_num;
    key_num = key();                //获取键值
    switch(key_num)
    {
        case 13:
        if(++time.select>3)         //选择时分秒
            time.select = 1;
        break;
            
        case 2:
            Time_Add();             //时间加
        break;
        
        case 6:
            Time_Sub();             //时间减
        break;
        
        case 1:                     //写时间
            ds1302_write(ds_w_sec,time.sec);
            ds1302_write(ds_w_min,time.min);
            ds1302_write(ds_w_hour,time.hour);
            mode = mod_time;
        break;
    }
}


/* 时间加 */
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


/* 时间减 */
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


/* 显示电压任务 */
void Task_V(void)
{
    uchar key_num;
    key_num = key();
    switch(key_num)//切换任务
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
        break;//选择要设置的电压
            
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
        break;//电压加
        
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
        break;//电压减
                
        case 5:
            r_buf[r_max] = v.max/100;
            EnQueue(&eeprom,4);
            r_buf[r_min] = v.min/100;
            EnQueue(&eeprom,5);
            mode = mod_v;
        break;//创建2个写eeprom任务
    }
}


/* 报警显示任务 */
void Task_Check(void)
{
    uchar key_num;
    key_num = key();
    switch(key_num)
    {
        case 13:
            check_f = ~check_f;
        break;//切换显示
        
        case 5:
            mode = mod_v;
        break;
        
        case 9:
            mode = mod_f;
        break;
    }
}


/* 频率显示任务 */
void Task_F(void)
{
    uchar key_num;
    key_num = key();
    switch(key_num)//切换任务
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
        f_dis = f;                  //显示频率
    else
        f_dis = 1000000*1/(float)f; //显示周期
}


/* 电压报警检测任务 */
void Task_Mark(void)
{
   if(v.mea == v.max)               //超出上限
   {
       r_buf[r_type] = 1;           //类型为1
       EnQueue(&eeprom, 0);
       r_buf[r_hour] = time.hour;
       EnQueue(&eeprom, 1);
       r_buf[r_min] = time.min;
       EnQueue(&eeprom, 2);
       r_buf[r_sec] = time.sec;
       EnQueue(&eeprom, 3);
   }                                //创建3个eeprom写任务
   else if(v.mea == v.min)          //超出下限
   {
       r_buf[r_type] = 2;           //类型为1
       EnQueue(&eeprom, 0);
       r_buf[r_hour] = time.hour;
       EnQueue(&eeprom, 1);
       r_buf[r_min] = time.min;
       EnQueue(&eeprom, 2);
       r_buf[r_sec] = time.sec;
       EnQueue(&eeprom, 3);
   }                                //创建3个eeprom写任务
}


/* 执行eeprom写任务的函数 */
void Task_Write(void)
{
    QElemType e;
    if(QueueLength(eeprom))         //队列长度大于一
    {
        DeQueue(&eeprom, &e);       //出队
        Write_At24c02(e,r_buf[e]);
    }
}


/* 开机读出eeprom数据 */
void Task_Read(void)
{
    at24c02_read_buffer(0,r_buf,6); //读eeprom数据
    v.max = r_buf[r_max]*100;       //类型转换
    v.min = r_buf[r_min]*100;
}

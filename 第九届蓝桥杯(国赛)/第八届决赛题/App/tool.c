#include "tool.h"

/* 函数声明 */
void Task_Init(void);
void Task_Work(void);
void Task_LED(void);
void Task_DAC(void);
void Task_Display(void);
void Task_Read(void);
void Task_Write(void);
void Task_Time(void);

static void Board_Init(void);
static void Task_C(void);
static void Task_B(void);
static void Task_F(void);


/* 变量声明 */
struct{
    uchar dat[4];       //4次测试的数据
    uchar last;         //上次的数据
    uchar now;          //现在的数据
    uchar cnt;          //数据的位置
    uchar set;          //设置的数值
} sonic;                //测试得到的距离

enum{
    mod_c = 0,          //测距模式
    mod_b = 1,          //数据回显模式
    mod_f = 3           //设置模式
} mode;                 //工作模式

uchar led_sta = 0xff;   //LED状态

uchar led_flash;        //LED闪烁计数


/* 初始化 */
void Task_Init(void)
{
    EA = 0;
    Board_Init();       //关掉板子上无关外设
    timer0_init();      //定时器初始化
    timer1_init();
    timer2_init();
    EA = 1;
}


/* 工作模式 */
void Task_Work(void)
{
    switch(mode)
    {
        case mod_c:Task_C();break;//测距模式
        case mod_b:Task_B();break;//数据回显模式
        case mod_f:Task_F();break;//设置模式
    }
}


/* 设置LED */
void Task_LED(void)
{
    XBYTE[0x8000] = led_sta;
}


/* 电压输出 */
void Task_DAC(void)
{
    if(sonic.now <= sonic.set)        //S<=S0
        dac_write(0);
    else                            //S>S0
        dac_write((sonic.now-sonic.set)*255/5*0.02);
}


/* 显示 */
void Task_Display(void)
{
    switch(mode)
    {
        case mod_c://测距模式
            display_c(sonic.last,sonic.now);
        break;
        
        case mod_b://数据回显模式
            display_b(sonic.cnt,sonic.dat[sonic.cnt]);
        break;
        
        case mod_f://设置模式
            display_f(sonic.set);
        break;
    }
}


/* 读出EEPROM上的数据 */
void Task_Read(void)
{
    sonic.dat[0] = at24c02_read(0);
    sonic.dat[1] = at24c02_read(1);
    sonic.dat[2] = at24c02_read(2);
    sonic.dat[3] = at24c02_read(3);
    sonic.set = at24c02_read(4);
}


/* 数据写进EEPROM */
void Task_Write(void)
{
    at24c02_write(sonic.cnt,sonic.dat[sonic.cnt]);
}


/* 关闭板子上无关外设 */
static void Board_Init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0X00;
    XBYTE[0XC000] = 0XFF;
    XBYTE[0XE000] = 0XFF;
}


/* 测距模式 */
static void Task_C(void)
{
    uchar key_num;
    key_num = key_scanf();                  //按键按下事件
    if(key_num == S4_ON)                    //按下S4
    {
        sonic.dat[sonic.cnt] = sonic_get(); //读出距离
        led_flash = 3;                      //LED闪烁3次
        sonic.last = sonic.now;             //上次的数据
        sonic.now = sonic.dat[sonic.cnt];   //现在的数据
        if(++sonic.cnt >= 4)                //数据的位置
            sonic.cnt = 0;
    }
    else if(key_num == S5_ON)               //按下S5
    {
        mode = mod_b;                       //切换到回显模式
        sonic.cnt = 0;                      //数据指向第一个
    }
    else if(key_num == S6_ON)               //按下S6
        mode = mod_f;                       //切换到设置模式
}


/* 回显模式 */
static void Task_B(void)
{
    uchar key_num;
    led_sta &= ~(1<<7);                     //此模式下量的灯
    key_num = key_scanf();                  //按键按下事件
    if(key_num == S5_ON)                    //按下S5
    {
        mode = mod_c;                       //切换到显示模式
        led_sta |= (1<<7);                  //关灯
    }
    else if(key_num == S6_ON)               //按下S6
    {
        mode = mod_f;                       //切换到设置模式
        led_sta |= (1<<7);                  //关灯
    }
    else if(key_num == S7_ON)               //按下S7
        if(++sonic.cnt >= 4)                //翻页
            sonic.cnt = 0;
}


/* 设置模式 */
static void Task_F(void)
{
    uchar key_num;
    led_sta &= ~(1<<6);                     //开灯
    key_num = key_scanf();                  //按键按下事件
    if(key_num == S5_ON)                    //按下S5
    {
        mode = mod_b;                       //切换到回显模式
        led_sta |= (1<<6);                  //关灯
    }
    else if(key_num == S6_ON)               //按下S6
    {
        mode = mod_c;                       //切换到显示模式
        led_sta |= (1<<6);                  //关灯
    }
    else if(key_num == S7_ON)               //按下S7
    {
        if((sonic.set += 10) > 30)          //设置盲区
            sonic.set = 0;
    }
    
}


void Task_Time(void)
{
    static uint count;
    if(led_flash)                           //LED闪烁
    {
        if(count++>25000)                   //计数
        {
            count = 0;
            led_flash--;
        }
        else if(count >12500)
            led_sta |= 1;
        else
            led_sta &= ~1;
    }
    else
        led_sta |= 1;
}

#include "tool.h"

/* �������� */
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


/* �������� */
struct{
    uchar dat[4];       //4�β��Ե�����
    uchar last;         //�ϴε�����
    uchar now;          //���ڵ�����
    uchar cnt;          //���ݵ�λ��
    uchar set;          //���õ���ֵ
} sonic;                //���Եõ��ľ���

enum{
    mod_c = 0,          //���ģʽ
    mod_b = 1,          //���ݻ���ģʽ
    mod_f = 3           //����ģʽ
} mode;                 //����ģʽ

uchar led_sta = 0xff;   //LED״̬

uchar led_flash;        //LED��˸����


/* ��ʼ�� */
void Task_Init(void)
{
    EA = 0;
    Board_Init();       //�ص��������޹�����
    timer0_init();      //��ʱ����ʼ��
    timer1_init();
    timer2_init();
    EA = 1;
}


/* ����ģʽ */
void Task_Work(void)
{
    switch(mode)
    {
        case mod_c:Task_C();break;//���ģʽ
        case mod_b:Task_B();break;//���ݻ���ģʽ
        case mod_f:Task_F();break;//����ģʽ
    }
}


/* ����LED */
void Task_LED(void)
{
    XBYTE[0x8000] = led_sta;
}


/* ��ѹ��� */
void Task_DAC(void)
{
    if(sonic.now <= sonic.set)        //S<=S0
        dac_write(0);
    else                            //S>S0
        dac_write((sonic.now-sonic.set)*255/5*0.02);
}


/* ��ʾ */
void Task_Display(void)
{
    switch(mode)
    {
        case mod_c://���ģʽ
            display_c(sonic.last,sonic.now);
        break;
        
        case mod_b://���ݻ���ģʽ
            display_b(sonic.cnt,sonic.dat[sonic.cnt]);
        break;
        
        case mod_f://����ģʽ
            display_f(sonic.set);
        break;
    }
}


/* ����EEPROM�ϵ����� */
void Task_Read(void)
{
    sonic.dat[0] = at24c02_read(0);
    sonic.dat[1] = at24c02_read(1);
    sonic.dat[2] = at24c02_read(2);
    sonic.dat[3] = at24c02_read(3);
    sonic.set = at24c02_read(4);
}


/* ����д��EEPROM */
void Task_Write(void)
{
    at24c02_write(sonic.cnt,sonic.dat[sonic.cnt]);
}


/* �رհ������޹����� */
static void Board_Init(void)
{
    XBYTE[0X8000] = 0XFF;
    XBYTE[0XA000] = 0X00;
    XBYTE[0XC000] = 0XFF;
    XBYTE[0XE000] = 0XFF;
}


/* ���ģʽ */
static void Task_C(void)
{
    uchar key_num;
    key_num = key_scanf();                  //���������¼�
    if(key_num == S4_ON)                    //����S4
    {
        sonic.dat[sonic.cnt] = sonic_get(); //��������
        led_flash = 3;                      //LED��˸3��
        sonic.last = sonic.now;             //�ϴε�����
        sonic.now = sonic.dat[sonic.cnt];   //���ڵ�����
        if(++sonic.cnt >= 4)                //���ݵ�λ��
            sonic.cnt = 0;
    }
    else if(key_num == S5_ON)               //����S5
    {
        mode = mod_b;                       //�л�������ģʽ
        sonic.cnt = 0;                      //����ָ���һ��
    }
    else if(key_num == S6_ON)               //����S6
        mode = mod_f;                       //�л�������ģʽ
}


/* ����ģʽ */
static void Task_B(void)
{
    uchar key_num;
    led_sta &= ~(1<<7);                     //��ģʽ�����ĵ�
    key_num = key_scanf();                  //���������¼�
    if(key_num == S5_ON)                    //����S5
    {
        mode = mod_c;                       //�л�����ʾģʽ
        led_sta |= (1<<7);                  //�ص�
    }
    else if(key_num == S6_ON)               //����S6
    {
        mode = mod_f;                       //�л�������ģʽ
        led_sta |= (1<<7);                  //�ص�
    }
    else if(key_num == S7_ON)               //����S7
        if(++sonic.cnt >= 4)                //��ҳ
            sonic.cnt = 0;
}


/* ����ģʽ */
static void Task_F(void)
{
    uchar key_num;
    led_sta &= ~(1<<6);                     //����
    key_num = key_scanf();                  //���������¼�
    if(key_num == S5_ON)                    //����S5
    {
        mode = mod_b;                       //�л�������ģʽ
        led_sta |= (1<<6);                  //�ص�
    }
    else if(key_num == S6_ON)               //����S6
    {
        mode = mod_c;                       //�л�����ʾģʽ
        led_sta |= (1<<6);                  //�ص�
    }
    else if(key_num == S7_ON)               //����S7
    {
        if((sonic.set += 10) > 30)          //����ä��
            sonic.set = 0;
    }
    
}


void Task_Time(void)
{
    static uint count;
    if(led_flash)                           //LED��˸
    {
        if(count++>25000)                   //����
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

#include "display.h"
#include "key.h"
#include "uart.h"
#include "tim.h"
#include "intrins.h"

/*变量声明*/
uchar key_num;
uchar hour,min,sec;
uchar led_sta=0xff;
/*函数声明*/
void init(void);
void board_init(void);
void led_test(void);
void smg_test(void);


/*主函数*/
void main(void)
{
    init();
    while(1)
    {
        
        XBYTE[0X8000] = led_sta;
        
        key_num = key_scanf();
        if      (key_num==S5_ON)
            led_sta ^= 0x80;
        else if (key_num==S4_ON)
            led_sta ^= 0x40;
    }
}


void timer0(void) interrupt 1
{
    static uint sec_count=0; 
    TR0=0;
    display_time(hour,min,sec);
    
    if(++sec_count>500)
    {
        sec_count = 0;
        if(sec<60)
            sec++;
        else
        {
            sec = 0;
            if(min<60)
                min++;
            else
            {
                min = 0;
                if(hour<24)
                    hour++;
                else
                    hour = 0;
            }
        }
    }
    TR0=1;
}


void timer1(void) interrupt 3
{
    key_on();
}


void uart1(void) interrupt 4
{
    uchar uart_rx;
    uart_rx = Uart_Receive_Byte();
    if     ((uart_rx&0xf0) == 0xa0)
        led_sta = ((~(uart_rx))&0x0f) | (led_sta&0xf0);
    else if((uart_rx&0xf0) == 0xb0)
    {
        Uart_Send_Byte(hour/10*16+hour%10);
        Uart_Send_Byte(min/10*16+min%10);
        Uart_Send_Byte(sec/10*16+sec%10);
    }
}


/*系统初始化*/
void init(void)
{
    board_init();
    led_test();
    smg_test();
    timer1_init();
    timer0_init();
    UartInit();
    EA = 1;
}


/*板初始化*/
void board_init(void)
{
    XBYTE[0X8000]=0XFF;
    XBYTE[0XA000]=0;
    XBYTE[0XC000]=0;
    XBYTE[0XE000]=0;
}


void led_test(void)
{
    uchar i,dat=0xff;
    void Delay100ms(void);
    
    for(i=0;i<8;i++)
    {
        dat &= ~(1<<i);
        XBYTE[0x8000] = dat;
        Delay100ms();
    }
    
    for(i=0;i<8;i++)
    {
        dat |= 1<<i;
        XBYTE[0x8000] = dat;
        Delay100ms();
    }
}

void smg_test(void)
{
    uchar i,dat=0;
    void Delay100ms(void);
    
    for(i=0;i<8;i++)
    {
        dat |= 1<<i;
        display_test(dat);
        Delay100ms();
    }
    
    for(i=0;i<8;i++)
    {
        dat &= ~(1<<i);
        display_test(dat);
        Delay100ms();
    }
    
}


void Delay100ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

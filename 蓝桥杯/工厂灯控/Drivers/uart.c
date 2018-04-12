#include "uart.h"


void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR &= 0xFB;		//定时器2时钟为Fosc/12,即12T
	T2L = 0xE8;		//设定定时初值
	T2H = 0xFF;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
    ES=1;
}


void Uart_Send_Byte(unsigned char dat)
{
    SBUF = dat;
    while(TI == 0);
    TI = 0;
}



unsigned char Uart_Receive_Byte(void)
{
    while(RI == 0);
    RI=0;
    return SBUF;
}





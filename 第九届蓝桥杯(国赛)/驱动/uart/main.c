#include <stc15f2k60s2.h>
#include <absacc.h>
#include "uart.h"
#include "stdio.h"
#include "iic.h"

unsigned char dat;
unsigned char wbuf[]={1,2,3,4,5,6,7};
unsigned char rbuf[7];

void main(void)
{
    unsigned char i;
    unsigned int j=10000;
    UartInit();
    XBYTE[0XA000]=0;
    iic_write_buffer(0,wbuf, 7);
    while(j--);
    iic_read_buffer(0,rbuf,7);
    
    for(i=0;i<7;i++)
    {
        TI = 1;
        printf("%d:%d   \n",(int)i,(int)rbuf[i]);
    }
    while(1);
}


void uart(void) interrupt 4
{
    dat = Uart_Receive_Byte();
}
#include "uart.h"


void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR &= 0xFB;		//��ʱ��2ʱ��ΪFosc/12,��12T
	T2L = 0xE8;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
    ES=1;
}


void Uart_Send_Byte(char dat)
{
    SBUF = dat;
    while(TI == 0);
    TI = 0;
}

char Uart_Receive_Byte(void)
{
    while(RI == 0);
    RI=0;
    return SBUF;
}


void Uart_Send_Str(char *pstr)
{
    while(*pstr != '\0')
    {
        Uart_Send_Byte(*pstr);
        pstr++;
    }
}




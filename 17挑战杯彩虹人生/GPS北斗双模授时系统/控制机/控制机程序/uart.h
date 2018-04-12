#ifndef _uart_h_
#define _uart_h_

#include "iom164v.h"

#define uchar unsigned char
#define uint unsigned int

void UART1_Init(void);
void UART1_Send(uchar i);
uchar UART1_Receive(void);
void UART1_Send_Char(uchar *p);
void UART0_Init(void);
uchar UART0_Receive(void);
void UART0_Send(uchar i);
void UART0_Send_Char(uchar *p);
void UART1_Send_RX(uchar *p);

#endif
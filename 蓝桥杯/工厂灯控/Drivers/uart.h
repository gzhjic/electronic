#ifndef _uart_h_
#define _uart_h_

#include "stc15f2k60s2.h"

void UartInit(void);
unsigned char Uart_Receive_Byte(void);
void Uart_Send_Byte(unsigned char dat);

#endif
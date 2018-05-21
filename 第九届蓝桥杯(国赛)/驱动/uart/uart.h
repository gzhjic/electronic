#ifndef _uart_h_
#define _uart_h_


#include "stc15f2k60s2.h"
#include "stdio.h"

void UartInit(void);
void Uart_Send_Str(char *pstr);
char Uart_Receive_Byte(void);

#endif
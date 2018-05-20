#ifndef _tool_h_
#define _tool_h_

#define uchar unsigned char
#define uint unsigned int

#include "tim.h"
#include "sonic.h"
#include "display.h"
#include "key.h"
#include "iic.h"


void Task_Init(void);
void Task_Work(void);
void Task_LED(void);
void Task_DAC(void);
void Task_Display(void);
void Task_Read(void);
void Task_Write(void);
void Task_Time(void);

#endif
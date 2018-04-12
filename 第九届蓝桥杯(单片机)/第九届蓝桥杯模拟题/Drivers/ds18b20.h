#ifndef _ds18b20_h_
#define _ds18b20_h_

#include "stc15f2k60s2.h"
#include "absacc.h"
#include "intrins.h"

#define uchar unsigned char
#define uint unsigned int

sbit DQ = P1^4;

uint get_temp(void);

#endif
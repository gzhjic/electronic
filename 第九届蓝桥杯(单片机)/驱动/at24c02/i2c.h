#ifndef _i2c_h_
#define _i2c_h_

#define uchar unsigned char
#define uint unsigned int

#include "stc15f2k60s2.h"
#include "absacc.h"
#include "intrins.h"

sbit sda=P2^1;
sbit scl=P2^0;

void Write_At24c02(uchar add,uchar dat);
uchar  Read_At24c02(uchar add);

#endif
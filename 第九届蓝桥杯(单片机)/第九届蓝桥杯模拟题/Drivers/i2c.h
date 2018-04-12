#ifndef _i2c_h_
#define _i2c_h_

#define uchar unsigned char
#define uint unsigned int
#include "stc15f2k60s2.h"
#include "absacc.h"
#include "intrins.h"

void write_at24c02(uchar add,uchar dat);
uchar read_at24c02(uchar add);

#endif
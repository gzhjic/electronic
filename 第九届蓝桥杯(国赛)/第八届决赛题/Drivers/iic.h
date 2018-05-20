#ifndef _iic_h_
#define _iic_h_

#include "intrins.h"
#include "stc15f2k60s2.h"

#define uchar unsigned char

void at24c02_write(uchar add, uchar dat);
uchar at24c02_read(uchar add);
void dac_write(uchar dat);

#endif
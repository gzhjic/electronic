#ifndef _iic_h_
#define _iic_h_

#include "intrins.h"
#include "stc15f2k60s2.h"

#define uchar unsigned char

void Write_At24c02(uchar add,uchar dat);
void at24c02_read_buffer(uchar add,uchar *dat, uchar num);
uchar dac_read(uchar dat);

#endif
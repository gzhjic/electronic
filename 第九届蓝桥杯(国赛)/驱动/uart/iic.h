#ifndef _iic_h_
#define _iic_h_

#include "intrins.h"
#include "stc15f2k60s2.h"

#define uchar unsigned char


void iic_write_buffer(uchar add, uchar *dat, uchar num);
void iic_read_buffer(uchar add,uchar *dat, uchar num);

#endif
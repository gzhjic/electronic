#ifndef _ds1302_h_
#define _ds1302_h_

#include "stc15f2k60s2.h"
#include "absacc.h"
#include "intrins.h"

#define uchar unsigned char
    
#define ds_w_sec  0x80
#define ds_w_min  0x82
#define ds_w_hour 0x84

#define ds_r_sec  0x81
#define ds_r_min  0x83
#define ds_r_hour 0x85
    
void ds1302_init(void);
uchar ds1302_read(uchar add);
void ds1302_write(uchar add,uchar dat);

#endif
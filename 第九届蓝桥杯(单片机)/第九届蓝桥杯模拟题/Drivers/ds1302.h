#ifndef _ds1302_h_
#define _ds1302_h_

#include "stc15f2k60s2.h"
#include "absacc.h"

#define uchar unsigned char
#define uint unsigned int

#define ds_w_sec  0x80
#define ds_w_min  0x82
#define ds_w_hour 0x84

#define ds_r_sec  0x81
#define ds_r_min  0x83
#define ds_r_hour 0x85

sbit rst = P1^3;
sbit io = P2^3;
sbit sck = P1^7;

void set_time(void);
uchar read_ds1302(uchar addr);

void write_ds1302(uchar addr,uchar dat);

#endif
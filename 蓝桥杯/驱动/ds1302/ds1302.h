#ifndef _ds1302_h_
#define _ds1302_h_

#define uchar unsigned char
#define uint unsigned int

#include "stc15f2k60s2.h"
#include "absacc.h"

sbit rst = P1^3;
sbit io = P2^3;
sbit sck = P1^7;

void set_time(void);
uchar read_ds1302(uchar addr);

void write_ds1302(uchar addr,uchar dat);

#endif
#ifndef _ds1302_h_
#define _ds1302_h_

#include "stc15f2k60s2.h"
#include "absacc.h"

#define uchar unsigned char
#define uint unsigned int

#define DS_W_SEC  0x80
#define DS_W_MIN  0x82
#define DS_W_HOUR 0x84

#define DS_R_SEC  0x81
#define DS_R_MIN  0x83
#define DS_R_HOUR 0x85

sbit rst = P1^3;
sbit io = P2^3;
sbit sck = P1^7;

void set_time(void);
uchar read_ds1302(uchar addr);


#endif
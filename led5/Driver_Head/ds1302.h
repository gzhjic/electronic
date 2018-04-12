#ifndef _ds1302_h
#define _ds1302_h

#include <avr/io.h>
#include "util/delay.h"

#define uint  unsigned int
#define uchar unsigned char

#define  SEC_W_ADDR 0x80
#define  MIN_W_ADDR 0x82
#define  HOU_W_ADDR 0x84
#define  DAT_W_ADDR 0x86
#define  MON_W_ADDR 0x88
#define  YEA_W_ADDR 0x8c

#define  SEC_R_ADDR 0x81
#define  MIN_R_ADDR 0x83
#define  HOU_R_ADDR 0x85
#define  DAT_R_ADDR 0x87
#define  MON_R_ADDR 0x89
#define  YEA_R_ADDR 0x8D

#define DS1302_WP_ON()	Write_ds1302(0x8E,0x80)	
#define DS1302_WP_OFF() Write_ds1302(0x8E,0x00)

uchar Read_ds1302(uchar addr);
void Write_ds1302(uchar addr,uchar data);
void Init_ds1302(void);
#endif
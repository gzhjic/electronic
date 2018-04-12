#ifndef _smg_h_
#define _smg_h_

#include "stc15f2k60s2.h"
#include "absacc.h"

#define uchar unsigned char
#define uint unsigned int

#define smg_off 10
#define smg_g	11
#define smg_c	12
#define smg_flash_hour 1
#define smg_flash_min  2
#define smg_flash_sec  3

void smg_dis_temp(uchar temp);
void smg_dis_time(uchar hour, uchar min, uchar sec, uchar flash);

#endif
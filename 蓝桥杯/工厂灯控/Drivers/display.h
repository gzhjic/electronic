#ifndef _display_h_
#define _display_h_

#define uchar unsigned char
#define uint unsigned int

#include "stc15f2k60s2.h"
#include "absacc.h"

#define SMG_OFF 10
#define SMG_G	11
#define SMG_C	12

void display_time(uchar h,uchar m,uchar s);
void display_test(uchar w);

#endif
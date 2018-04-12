#ifndef _key_h_
#define _key_h_

#include "stc15f2k60s2.h"
#include "absacc.h"

#define uchar unsigned char

#define S7_ON 1
#define S6_ON 2
#define S5_ON 3
#define S4_ON 4

void key_on(void);
uchar key_scanf(void);

#endif
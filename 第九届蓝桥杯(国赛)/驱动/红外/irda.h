#ifndef _irda_h_
#define _irda_h_


#include "stc15f2k60s2.h"
#include "intrins.h"

#define uchar unsigned char

#define IRDA_ID 0

sbit ir = P1^1;

uchar get_pluse_time(void);
uchar irda_process(void);

#endif
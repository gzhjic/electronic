#ifndef _sonic_h_
#define _sonic_h_

#define uchar unsigned char
#define uint unsigned int

#include "stc15f2k60s2.h"
#include "absacc.h"

void sonic_sent(void);
uchar sonic_get(void);

#endif
#ifndef _tim_h_
#define _tim_h_


#include "stc15f2k60s2.h"

sbit ext0_port = P3^2;

void timer0_init(void);
void ext0_init(void);

#endif
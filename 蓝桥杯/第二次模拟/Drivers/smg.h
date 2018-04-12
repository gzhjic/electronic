#ifndef _smg_h_
#define _smg_h_

#include "stc15f2k60s2.h"
#include "absacc.h"

#define uchar unsigned char
#define uint unsigned int

#define SMG_OFF 10
#define SMG_G	11
#define SMG_C	12

void dis_time(uchar hour, uchar min, uchar sec);
void dis_worring(uchar mod, uchar min, uchar sec);
void dis_temp(uchar min, uchar max,uchar temp);
void dis_set(uchar min_h, uchar min_l,
              uchar max_h, uchar max_l,
              uchar temp, uchar flash);


#endif
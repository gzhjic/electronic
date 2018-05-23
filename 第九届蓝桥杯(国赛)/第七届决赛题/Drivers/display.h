#ifndef _display_h_
#define _display_h_

#define uchar unsigned char
#define uint unsigned int

#include "stc15f2k60s2.h"
#include "absacc.h"

#define SMG_OFF 10
#define SMG_G	11
#define SMG_C	12
#define SMG_F   13


void Display_Time(uchar hour,uchar min,uchar sec,uchar flash);
void Display_mV(uint mv);
void Display_Set(uint top,uint button,uchar falsh);
void Display_F(uint f);
void Display_Type(uchar type);


#endif
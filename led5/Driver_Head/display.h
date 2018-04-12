
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <avr/io.h>
#include "util/delay.h"

#define uint unsigned int 
#define uchar unsigned char 


#define H595_ST_1		PORTC|=1<<PC7		//PC7
#define H595_ST_0		PORTC&=~(1<<PC7)		

#define H595_SCLK_1		PORTA|=1<<PA7			//PB1
#define H595_SCLK_0		PORTA&=~(1<<PA7)		

#define H595_DAT_1		PORTC|=1<<PC6		//PB2
#define H595_DAT_0		PORTC&=~(1<<PC6)

#define LED_ON		PORTD|=(1<<PD7)		
#define LED_OFF		PORTD&=~(1<<PD7)		

void display(uchar hour, uchar min);

#endif
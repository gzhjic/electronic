#include "delay.h"


void delay_us(unsigned int time) //8Mhz�ڲ�RC����ʱXus  
{
	 do 
	{  time--; } 
 	 while(time>1); 
}

 
void delay_ms(unsigned int time) //8Mhz�ڲ�RC����ʱXms 
{ 
 	while(time!=0) 
	{  
	delay_us(1000);
 	time--; 
	}  
}
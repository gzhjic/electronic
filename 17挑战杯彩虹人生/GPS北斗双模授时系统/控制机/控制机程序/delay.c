#include "delay.h"


void delay_us(unsigned int time) //8Mhz内部RC震荡延时Xus  
{
	 do 
	{  time--; } 
 	 while(time>1); 
}

 
void delay_ms(unsigned int time) //8Mhz内部RC震荡延时Xms 
{ 
 	while(time!=0) 
	{  
	delay_us(1000);
 	time--; 
	}  
}
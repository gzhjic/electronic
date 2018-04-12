 
 
 
 #include "delay.h"
 
 uchar history_messages_number = 0;			//历史信息循环显示变量
 
 /**************1ms延时函数**************/
 void delay_ms(uint xms)
 {
 	uint i,j;
	for(i=0;i<xms;i++)
	   delay_us(1000);
 }
 
 /*************1us延时函数****************/
 void delay_us(uint us)
 {
 	uint i;
   	us=us*5/4;
  	for(i=0;i<us;i++);
 }
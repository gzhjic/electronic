
   


#ifndef _JQ8400_h_
#define _JQ8400_h_
    
#include <avr/io.h>
   
#define uint  unsigned int
#define uchar unsigned char	
	
#define fosc 8000000 
#define baud 9600
   

/**************JQ8400的功能函数声明**************/	
void UART_Init(void);	//初始化

void  Play_Function(void);	//播放函数声明
	
void  Pause_Function(void);//暂停函数声明
	
void  Add_Volume_Function(void);//增加音量函数声明
	
void  Decrease_Volume_Function(void);//减小音量函数声明
	
#endif
		
		
		


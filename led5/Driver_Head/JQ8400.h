
   


#ifndef _JQ8400_h_
#define _JQ8400_h_
    
#include <avr/io.h>
   
#define uint  unsigned int
#define uchar unsigned char	
	
#define fosc 8000000 
#define baud 9600
   

/**************JQ8400�Ĺ��ܺ�������**************/	
void UART_Init(void);	//��ʼ��

void  Play_Function(void);	//���ź�������
	
void  Pause_Function(void);//��ͣ��������
	
void  Add_Volume_Function(void);//����������������
	
void  Decrease_Volume_Function(void);//��С������������
	
#endif
		
		
		


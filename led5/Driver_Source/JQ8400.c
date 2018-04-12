    
		
		
#include "JQ8400.h"
		
		
/********************���͹����ֽ�***********************************/
	
const uchar Play_Location[4] = {0xAA,0x02,0x00,0xAC};//����
		
const uchar Pause_Location[4] = {0xAA,0x03,0x00,0xAD};//��ͣ
		
const uchar Add_Volume_Location[4] = {0xAA,0x15,0x00,0xBF};//��������
		
const uchar Decrease_Volume_Location[4] = {0xAA,0x14,0x00,0xBE};//��С����
	
/***************���ڳ�ʼ�����������ݡ���������********************/
void UART_Init(void)
{
		DDRB |= (1 << PD0) | (1 << PD1);
		PORTD |= (1 << PD0) | (1 << PD1);
		UCSRB = 0X00;
		UCSRA = 0X00;
		UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
		UBRRL = (fosc / 16 / (baud + 1))%256;
		UBRRH = (fosc / 16 / (baud + 1))/256;
		UCSRB |= (1 << TXEN) | (1 << RXEN);
}
		
		
static void UART_Send(uchar i)
{
		while(!(UCSRA & (1 << UDRE)));
		UDR = i;
}
		
//static uchar ucUART_Receive(void)
//{
	//while(!(UCSRA & (1 << RXC)));
	//return UDR;
//}
		
		
/*************************************************************/	



/**************JQ8400�Ĺ���**********************************/
       	
/**********����**********/
void  Play_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
		UART_Send(Play_Location[i]);
	} 
}
		
/**********��ͣ**************/
void  Pause_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
		UART_Send(Pause_Location[i]); 
	} 
}
		
/**********��������***********/
void  Add_Volume_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
	UART_Send(Add_Volume_Location[i]); 
	} 
}
		
/**********��С����****************/
void  Decrease_Volume_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
	UART_Send(Decrease_Volume_Location[i]); 
	} 
}
		
		
/********************************************************/		
		
		
		
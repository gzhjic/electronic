    
		
		
#include "JQ8400.h"
		
		
/********************发送功能字节***********************************/
	
const uchar Play_Location[4] = {0xAA,0x02,0x00,0xAC};//播放
		
const uchar Pause_Location[4] = {0xAA,0x03,0x00,0xAD};//暂停
		
const uchar Add_Volume_Location[4] = {0xAA,0x15,0x00,0xBF};//增加音量
		
const uchar Decrease_Volume_Location[4] = {0xAA,0x14,0x00,0xBE};//减小音量
	
/***************串口初始化、发送数据、接收数据********************/
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



/**************JQ8400的功能**********************************/
       	
/**********播放**********/
void  Play_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
		UART_Send(Play_Location[i]);
	} 
}
		
/**********暂停**************/
void  Pause_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
		UART_Send(Pause_Location[i]); 
	} 
}
		
/**********增加音量***********/
void  Add_Volume_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
	UART_Send(Add_Volume_Location[i]); 
	} 
}
		
/**********减小音量****************/
void  Decrease_Volume_Function(void)
{
	uchar i;
		  
	for(i = 0;i < 4;i++)
	{
	UART_Send(Decrease_Volume_Location[i]); 
	} 
}
		
		
/********************************************************/		
		
		
		
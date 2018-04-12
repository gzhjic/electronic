#include <avr/io.h>
#include <avr/interrupt.h>
#include "display.h"
#include "ds1302.h"
#include "nrf24l01.h"
#include "ADC.h"
#include "TIM.h"
#include "JQ8400.h"


/*变量声明*/
uint adc_value;						//adc
uchar  aa=0,cd=0;
uchar hour,min,sec,date,month,year; //时间
char TXbuf[32];						//无线发送数组
char RXbuf[32];						//无线接收数组
/*函数声明*/
void Get_Time(void);
void init(void);



/*主函数*/
int main(void)
{
	init();
	PWM_Set(10,2000);
    while (1) 
    {
		//hour = Read_ds1302(HOU_R_ADDR);
		//min = Read_ds1302(MIN_R_ADDR);
		//sec = Read_ds1302(SEC_R_ADDR);
		if(sec%2)
			LED_OFF;
		else
			LED_ON;
    }
}


/*TIM0溢出中断*/
SIGNAL(TIMER0_OVF_vect)
{
	if(aa++>=30)
	{
		aa=0;
		if(cd++>9)
			cd=0;
	}
}


/*TIM2溢出中断*/
SIGNAL(TIMER2_OVF_vect)
{
	display(12,34);
}


/*ADC转换完成中断*/
SIGNAL(ADC_vect)
{
	adc_value = ADC_Read();
}


void init(void)
{
	DDRD = 0xff;
	DDRC = 0xff;
	DDRB = 0xf0;
	DDRA = 0xff;
	init_NRF24L01(); 
	SetRX_Mode();
	TIM0_Init();
	TIM1_PWM_Init();
	TIM2_Init();
	ADC_Init();
	UART_Init();
	Init_ds1302();
	sei();
}


void Get_Time(void)
{
	sec = (RXbuf[6]-0x30)*10+(RXbuf[7]-0x30);
	min = (RXbuf[4]-0x30)*10+(RXbuf[5]-0x30);
	hour = (RXbuf[2]-0x30)*10+(RXbuf[3]-0x30);
}
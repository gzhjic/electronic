#include "ADC.h"

void ADC_Init(void)
{
	ADMUX = 0X43;	//基准电压AVCC，右对齐，ADC3
	ADCSRA = 0XFF;  //使能ADC，中断，自动触发， 128分频
	SFIOR &=0X1F;   //连续转换模式
}

unsigned int ADC_Read(void)
{
	unsigned char h,l;
	
	l = ADCL;
	h = ADCH&0x03;
	
	return (h<<8) + l; 
}
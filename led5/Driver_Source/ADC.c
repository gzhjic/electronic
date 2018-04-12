#include "ADC.h"

void ADC_Init(void)
{
	ADMUX = 0X43;	//��׼��ѹAVCC���Ҷ��룬ADC3
	ADCSRA = 0XFF;  //ʹ��ADC���жϣ��Զ������� 128��Ƶ
	SFIOR &=0X1F;   //����ת��ģʽ
}

unsigned int ADC_Read(void)
{
	unsigned char h,l;
	
	l = ADCL;
	h = ADCH&0x03;
	
	return (h<<8) + l; 
}
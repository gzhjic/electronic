#include "TIM.h"


/* ��ʱ��0��ʼ��*/
void TIM0_Init(void)
{
	TCCR0 = 0X05;	//1024��Ƶ
	TCNT0 = 68;		//Լ24sm����һ���ж�
	TIMSK |= 1;		//����ж�ʹ��
}


/*��ʱ��2��ʼ��*/
void TIM2_Init(void)
{
	TCCR2 = 4;		//64��Ƶ
	TCNT2 = 131;	//1ms����һ���ж�
	TIMSK |= 1<<6;	//����ж�ʹ��
}


/*��ʱ��1PWM�����ʼ��*/
void TIM1_PWM_Init(void)
{
	DDRD |= 1<<5;
	TCCR1A = 0X82;	//�Ƚ�ƥ��ʱΪ0������PWMģʽ
	TCCR1B = 0X1A;  //����PWMģʽ��8��Ƶ
	ICR1 =	1000;	//����1ms
	OCR1A = 900;
}


/************************************
	PWM���ú���  
	pro_100:ռ�ձ�(0-100)
	f_nHZ:  Ƶ��nHZ
***********************************/
void PWM_Set(unsigned char pro_100, unsigned int f_nHZ)
{
	ICR1 = (unsigned int)(1000000/f_nHZ);
	OCR1A = ((float)pro_100/100)*ICR1;
} 


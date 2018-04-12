
#include"display.h"
uchar i;

uchar smg_buf[]={0x7e,0x30,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x7b,0x80};
				//  0    1    2    3   4     5   6     7    8    9    -
static void hc595(uchar sum)
{
	unsigned char i = 0;
	H595_ST_0;
	for(i=0;i<8;i++)
	{
		H595_SCLK_0;
		if(sum&0x80)
			H595_DAT_1;
		else
			H595_DAT_0;
		H595_SCLK_1;
		sum<<=1;
	}
	H595_ST_1;	
}


void display(uchar hour, uchar min)
{
	uchar temp[4];

	temp[0] = smg_buf[hour/10];
	temp[1] = smg_buf[hour%10];
	temp[2] = smg_buf[min/10];
	temp[3] = smg_buf[min%10];
	//temp[4] = smg_buf[sec/10];
	//temp[5] = smg_buf[sec%10];
	
	
	PORTC = 0;
	//hc595(0);
	hc595(temp[i]);
	PORTC = 1<<i;
	//PORTC = 0;
	
	if(++i >=4)
		i = 0;
}


//void display(uchar hour, uchar min)
//{
	//PORTC = 0;
	//hc595(smg_buf[hour/10]);
	//PORTC = 0xff;
	//_delay_ms(3);
	//
	//PORTC = 0;
	//hc595(smg_buf[hour%10]);
	//PORTC = 0xff;
	//_delay_ms(3);
	//
	//PORTC = 0;
	//hc595(smg_buf[min/10]);
	//PORTC = 0xff;
	//_delay_ms(3);
	//
	//PORTC = 0;
	//hc595(smg_buf[min%10]);
	//PORTC = 0xff;
	//_delay_ms(3);
//}
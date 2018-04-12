#include "display.h"


uchar smg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void display_smg(uchar sum1,uchar sum2,uchar sum3,uchar sum4)
{
	static uchar temp[8];
	static uchar i;

	temp[0]=smg[sum1/10];
	temp[1]=smg[sum1%10];
	temp[2]=smg[sum2/10];
	temp[3]=smg[sum2%10];
	temp[4]=smg[sum3/10];
	temp[5]=smg[sum3%10];
	temp[6]=smg[sum4/10];
	temp[7]=smg[sum4%10];

	XBYTE[0xe000]=0xff;
	XBYTE[0xC000]=0x01<<i;
	XBYTE[0xE000]=temp[i];

	if(++i>=8)
	i=0;
}

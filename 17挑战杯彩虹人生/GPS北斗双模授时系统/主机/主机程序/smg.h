#ifndef _smg_h_
#define _smg_h_



unsigned char smg_duan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0x7f,0xff};
//uchar smg_wela[]={0xef,0xdf,0xcf,0x7f};

void smg(unsigned int smg_num)
{
	static unsigned char i;
	unsigned char wela[4];
	
	wela[0]=smg_duan[smg_num%10];
	wela[1]=smg_duan[smg_num/10%10];
	wela[2]=smg_duan[smg_num/100%10];
	wela[3]=smg_duan[smg_num/1000%10];
	
	PORTC=0xff;
	PORTD=~(0x80>>i);
	PORTC=wela[i];
	if(++i>=4)
	{i=0;}
}

#endif
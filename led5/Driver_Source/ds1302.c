#include "ds1302.h"

/*��λ����*/
#define RST_CLR PORTD &= ~(1 << PD4) //�õ͵�ƽ
#define RST_SET PORTD |=  (1 << PD4) //�øߵ�ƽ
#define RST_IN  DDRD  &= ~(1 << PD4) //������
#define RST_OUT DDRD  |=  (1 << PD4) //�����

/*˫������*/
#define IO_CLR  PORTD &= ~(1 << PD3) //�õ͵�ƽ
#define IO_SET  PORTD |=  (1 << PD3) //�øߵ�ƽ 
#define IO_R    PIND & (1 << PD3)    //��ƽ��ȡ
#define IO_IN   DDRD &= ~(1 << PD3)  //������
#define IO_OUT  DDRD |=  (1 << PD3)  //�����

/*ʱ���ź�*/
#define SCK_CLR  PORTD &= ~(1 << PD2) //ʱ���ź�
#define SCK_SET  PORTD |=  (1 << PD2) //�øߵ�ƽ
#define SCK_IN   DDRD  &= ~(1 << PD2) //������
#define SCK_OUT  DDRD  |=  (1 << PD2) //�����



/*��ds1302��һ�ֽ�����*/
uchar Read_Byte(void)
{
	 uchar i;
	 uchar dat = 0;//�����������ݴ����dat��
 
	 IO_IN; //����Ϊ����
	 IO_CLR;//������������
 
	 for(i = 0;i < 7;i++) //��7λ
	 {
		  SCK_SET; //�øߵ�ƽ
		  _delay_us(10);
		  SCK_CLR;//ʱ���ź�
		  _delay_us(10);
  
		  if(IO_R)//�����ݶ˿�״̬
		  {
			dat = dat | 0x80;
		  }
		  else
		  {
			dat = dat & 0x7f;
		  }
  
		  SCK_SET;//����������
		  dat = dat >> 1;
	 }
 
	 IO_OUT;//�ָ�Ϊ���
	 return dat;
}

/*��ds1302дһ���ֽ�����*/
void Write_Byte(uchar dat)
{
   uchar i;
	
	for(i = 0;i < 8;i++)
	{
	  SCK_CLR;
			
			if(dat & 0x01)//д����λ
			{
			  IO_SET;
			}
			else
			{
			 IO_CLR;
			}
			
			_delay_us(10);
			SCK_SET;
			dat >>= 1;//��������1λ
	}
	
}

/*��ds1302��ָ����ַ��1�ֽ�����*/
uchar Read_ds1302(uchar addr)
{
  char data;
  
  RST_CLR;
  SCK_CLR;
  _delay_us(10);
  
  RST_SET;
  _delay_us(10);
  
  Write_Byte(addr);//д���������
  _delay_us(10);
  
  data = Read_Byte();//��������
  _delay_us(10);
  
  SCK_CLR;
  RST_CLR;
  
  data = data/16*10 + data%16;
  return data;
}

/*��ds1302��ָ����ַд1�ֽ�����*/
void Write_ds1302(uchar addr,uchar data)
{
   RST_CLR;
	SCK_CLR;
	_delay_us(10);
	
	RST_SET;
	_delay_us(10);
	
	Write_Byte(addr);//д���������
	_delay_us(10);
	
	SCK_CLR;
	_delay_us(10);
	
	SCK_CLR;
	_delay_us(10);
	
	data = data/10*16 + data%10;
	Write_Byte(data);//д������
	
	SCK_CLR;
	_delay_us(10);
	
	RST_CLR;
}


/*��ʼ��ds1302����*/
void Init_ds1302(void)
{
  RST_CLR;//RST�����õ͵�ƽ
  SCK_CLR;//SCK�����õ͵�ƽ
  RST_OUT;//RST�����������
  SCK_OUT;//SCK������������
  
  DS1302_WP_OFF();//д����������,����д
  Write_ds1302(SEC_W_ADDR,0);//д��Ĵ���
  Write_ds1302(MIN_W_ADDR,17);//д�ּĴ���
  Write_ds1302(HOU_W_ADDR,20);//дʱ�Ĵ���
  Write_ds1302(DAT_W_ADDR,27);//д�ռĴ���
  Write_ds1302(MON_W_ADDR,3);//д�¼Ĵ���
  Write_ds1302(YEA_W_ADDR,18);//д��Ĵ���
  
  Write_ds1302(0x90,0xAB);//д�����
  DS1302_WP_ON();//д����������,��ֹд
}






#include "ds1302.h"
#include "delay.h"

/*复位引脚*/
#define RST_CLR PORTC &= ~(1 << PC0) //置低电平
#define RST_SET PORTC |=  (1 << PC0) //置高电平
#define RST_IN  DDRC  &= ~(1 << PC0) //设输入
#define RST_OUT DDRC  |=  (1 << PC0) //设输出

/*双向数据*/
#define IO_CLR  PORTC &= ~(1 << PC1) //置低电平
#define IO_SET  PORTC |=  (1 << PC1) //置高电平 
#define IO_R    PINC & (1 << PC1)    //电平读取
#define IO_IN   DDRC &= ~(1 << PC1)  //设输入
#define IO_OUT  DDRC |=  (1 << PC1)  //设输出

/*时钟信号*/
#define SCK_CLR  PORTC &= ~(1 << PC2) //时钟信号
#define SCK_SET  PORTC |=  (1 << PC2) //置高电平
#define SCK_IN   DDRC  &= ~(1 << PC2) //设输入
#define SCK_OUT  DDRC  |=  (1 << PC2) //设输出



/*从ds1302读一字节数据*/
uchar Read_Byte(void)
{
 uchar i;
 uchar dat = 0;//将读出的数据存放在dat中
 
 IO_IN; //设置为输入
 IO_CLR;//不带上拉电阻
 
 for(i = 0;i < 7;i++) //读7位
 {
  SCK_SET; //置高电平
  delay_us(10);
  SCK_CLR;//时钟信号
  delay_us(10);
  
  if(IO_R)//读数据端口状态
  {
    dat = dat | 0x80;
  }
  else
  {
   dat = dat & 0x7f;
  }
  
  SCK_SET;//产生下跳沿
  dat = dat >> 1;
 }
 
 IO_OUT;//恢复为输出
 return dat;
}

/*向ds1302写一个字节数据*/
void Write_Byte(uchar dat)
{
   uchar i;
	
	for(i = 0;i < 8;i++)
	{
	  SCK_CLR;
			
			if(dat & 0x01)//写数据位
			{
			  IO_SET;
			}
			else
			{
			 IO_CLR;
			}
			
			delay_us(10);
			SCK_SET;
			dat >>= 1;//数据右移1位
	}
	
}

/*从ds1302的指定地址读1字节数据*/
uchar Read_ds1302(uchar addr)
{
  char data;
  
  RST_CLR;
  SCK_CLR;
  delay_us(10);
  
  RST_SET;
  delay_us(10);
  
  Write_Byte(addr);//写入操作命令
  delay_us(10);
  
  data = Read_Byte();//读出数据
  delay_us(10);
  
  SCK_CLR;
  RST_CLR;
  
  data = data/16*10 + data%16;
  return data;
}

/*从ds1302的指定地址写1字节数据*/
void Write_ds1302(uchar addr,uchar data)
{
   RST_CLR;
	SCK_CLR;
	delay_us(10);
	
	RST_SET;
	delay_us(10);
	
	Write_Byte(addr);//写入操作命令
	delay_us(10);
	
	SCK_CLR;
	delay_us(10);
	
	SCK_CLR;
	delay_us(10);
	
	data = data/10*16 + data%10;
	Write_Byte(data);//写入数据
	
	SCK_CLR;
	delay_us(10);
	
	RST_CLR;
}

/*设置初始时间函数*/
void Set_ds1302(uchar addr,uchar *p,uchar n)
{
 Write_ds1302(0x8e,0x00);//写控制字，允许写操作
 
 for(;n>0;n--)
 {
    Write_ds1302(addr,*p);
		p++;
		addr = addr + 2;
 }
 
 Write_ds1302(0x8e,0x80);//写保护，不允许写
 
}

/*初始化ds1302函数*/
void Init_ds1302(void)
{
  RST_CLR;//RST引脚置低电平
  SCK_CLR;//SCK引脚置低电平
  RST_OUT;//RST引脚设置输出
  SCK_OUT;//SCK引脚设置输入
  
  Write_ds1302(0x80,0x00);//写秒寄存器
  
  Write_ds1302(0x90,0xAB);//写充电器
  
  Write_ds1302(0x8E,0x80);//写保护控制字,禁止写
}






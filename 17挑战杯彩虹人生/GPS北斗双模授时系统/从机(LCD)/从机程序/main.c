#include"iom16v.h"
#include "shounrf24l01.h"
#include "12864.h"
#include "ds1302.h"

#define uchar unsigned char 
#define uint unsigned int

uchar RXbuf[32];
//此机地址为0x01   TXbuf[2]=0x01
uchar TXbuf[32]={0x43,0x03,0x01,0x01,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x34};

uchar Hour,Hour_High,Hour_Low;
uchar Min_High,Min_Low,Min;
uchar Sec_High,Sec_Low,Sec;
uchar Day,Day_High,Day_Low;
uchar Month,Month_High,Month_Low;
uchar Year_High,Year_Low;
uchar MaxDay;
uint  Year;
uchar TimeCorrect;
uint Timetable;
uchar Timetable_Flag;
/*函数声明*/
void P_init(void);
uchar IsLeapYear(unsigned int uiYear);
unsigned char GetMaxDay(unsigned char Month_Value,unsigned int Year_Value);
void UTCDate2LocalDate(void);
void GetTime(void);
void LCD_Display(void);
void DataToASCII(void);
void AllWriteIntoDS1302(void);
void AllReadDS1302(void);
void EEPROM_Write(uint addr,uint adata);
uchar EEPROM_Read(uint addr);


/********************************************/
void main(void) 
{  
uchar z;
/*无线初始化*/
P_init();
init_NRF24L01();
SetRX_Mode();
/*液晶初始化*/
lcd_port_init();
lcd_init();
lcd_clr();   
/*液晶显示界面*/
lcd_write_char(0,0,"时间：");    
lcd_write_char(0,2,"20  年  月  日");
lcd_write_char(0,3,"    时  分  秒");
/*DS1302端口初始化*/
//Init_ds1302();
while(1)  
{
	nRF24L01_RxPacket(RXbuf);			//从无线中获取所有信息
	if((RXbuf[0]==0x43)&&(RXbuf[31]==0x34)) //判断起始位和结束位
	{			
		switch(RXbuf[1])					//选择工作模式
		{	
		/**************工作模式1 广播************/
			case 1:							
			if(RXbuf[30]==1)				//检测GPS信号
			{		
				GetTime();											//从无线中提取时间信息
				TimeCorrect=Sec-0x30;								
				//if(TimeCorrect!=Read_ds1302(0x81))			    //如果DS1302时间有误差
					//AllWriteIntoDS1302();							//修正时间
				lcd_write_char(0,1,"      ");
			}
			else
			{
				lcd_write_char(0,1,"无信号");
			}
			break;
		/************工作模式2 时间表***********/
			case 2:		
			for(z=0;z<28;z++)					
			{
				EEPROM_Write(z+28*RXbuf[2],RXbuf[z+3]);
			}
			break;
		/************工作模式4 请求应答*********/
			case 4:
			if(RXbuf[15])
				nRF24L01_TxPacket(TXbuf);
			break;
		/************错误*********************/
			default:
			lcd_write_char(0,1,"故障");
			break;
		}
	} 
	else
	{
		lcd_write_char(0,1,"故障");
	}
	//AllReadDS1302();									//时间从DS1302中读出
	DataToASCII();										//时间转成ASCII码
	LCD_Display();										//显示到LCD上
	
	/*************到点报时*********************/
	Timetable=Hour*10000+Min*100+Sec;
	switch(Timetable)
	{
		case 82000 : case 90500: case 91000: case 95500: case 101000:case 105500:case 110000:case 114500:
		case 134000:case 142500:case 143000:case 151500:case 152500:case 161000:case 161500:case 170000:
		case 175000:case 183500:case 184000:case 192500:case 193500:case 202000:case 202500:case 211000:
		PORTA^=(1<<0);break;
		default:
		break;
	}
}
}

void P_init(void)
{
	DDRA=0XFF;
	PORTA=0XFF;
	DDRB=(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB7);
	DDRA|=1<<0;
}
/************************************************
从无线中取出时间并转换成北京时间
*************************************************/
void GetTime(void)
{
	Year_High = RXbuf[12];
	Year_Low = RXbuf[13];

	Month_High = RXbuf[10];
	Month_Low = RXbuf[11];

	Day_High = RXbuf[8];
	Day_Low = RXbuf[9];
	
	Hour_High = RXbuf[2];
	Hour_Low = RXbuf[3];
	
	Min_High = RXbuf[4];
	Min_Low = RXbuf[5];
	
	Sec_High = RXbuf[6];
	Sec_Low = RXbuf[7];
	
	Month = (Month_High-0x30)*10+(Month_Low-0x30);
	Year = 2000+(Year_High-0x30)*10+(Year_Low-0x30);
	Day = (Day_High-0x30)*10+(Day_Low-0x30);
	Min = (Min_High-0x30)*10+(Min_Low-0x30);
	Sec = (Sec_High-0x30)*10+(Sec_Low-0x30);
	Hour = (Hour_High-0x30)*10+(Hour_Low-0x30)+8;			//UTC时间转换到北京时间		UTC+8
	if( Hour >= 24)				//溢出
	{
		Hour %= 24;				//获取当前Hour
		UTCDate2LocalDate();			//日期进位
	}
	
}

//****************************************************
//UTC日期与当地日期转换
//****************************************************
void UTCDate2LocalDate(void)
{
	Day = Day + 1;		//日  加一
	MaxDay = GetMaxDay(Month,Year);				//获取当月 天数 最大值
	if(Day > MaxDay)		//溢出
	{
		Day = 1;
		Month += 1;
		if(Month > 12)
		{
			Year+=1;
		}
	}
}

//****************************************************
//获取当月日期最大值
//****************************************************
unsigned char GetMaxDay(unsigned char Month_Value,unsigned int Year_Value)
{
	unsigned char iDays;
	switch(Month_Value)
	{
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			iDays = 31;break;
		case 2:
		//2月份比较特殊，需要根据是不是闰年来判断当月是28天还29天
			iDays = IsLeapYear(Year_Value)?29:28;break;
		case 4:case 6:case 9:case 11:
			iDays = 30;break;
		default : break;
	}
	return(iDays);						
}

//****************************************************
//闰年检测
//****************************************************
uchar IsLeapYear(unsigned int uiYear)
{
	return (((uiYear%4)==0)&&((uiYear%100)!=0))||((uiYear%400)==0);
}

/*****************************************************
写入DS1302
******************************************************/
void AllWriteIntoDS1302(void)
{
	Write_ds1302(0x8e,0x00);   //关闭写保护
	Write_ds1302(0x90,0xab);
	Write_ds1302(0x8c,Year-2000);
    Write_ds1302(0x88,Month);
  	Write_ds1302(0x86,Day);
  	Write_ds1302(0x8a,1);
  	Write_ds1302(0x84,Hour);
  	Write_ds1302(0x82,Min);
  	Write_ds1302(0x80,Sec);
	Write_ds1302(0x8e,0x80);   //打开写保护
}

void AllReadDS1302(void)
{
	Year=Read_ds1302(0x8d);
	Month=Read_ds1302(0x89);
	Day=Read_ds1302(0x87);
	Hour=Read_ds1302(0x85);
	Min=Read_ds1302(0x83);
	Sec=Read_ds1302(0x81);
}

/****************************************************
转ASCII
*****************************************************/
void DataToASCII(void)
{
	
	Hour_High = Hour/10+0x30;			//时间转成ASCII码
	Hour_Low = Hour%10+0x30;
	
	Sec_High = Sec/10+0x30;
	Sec_Low = Sec%10+0x30;
	
	Min_High = Min/10+0x30;
	Min_Low = Min%10+0x30;
	
	Day_High = Day/10 + 0x30;				//转换日期值为ASCII
	Day_Low = Day%10 + 0x30;

	Month_High = Month/10 + 0x30;			//转换月份值为ASCII
	Month_Low = Month%10 + 0x30;

	Year_High = Year%100/10 + 0x30;			//转换年份值为ASCII
	Year_Low = Year%10 + 0x30;			
	
	
}

/******************************************************
LCD显示时间
*******************************************************/
void LCD_Display(void)
{
	lcd_xy(3,1);
	lcd_write_data(Hour_High);   
	lcd_write_data(Hour_Low);
	lcd_xy(3,3);
	lcd_write_data(Min_High);
	lcd_write_data(Min_Low);
	lcd_xy(3,5);
	lcd_write_data(Sec_High);
	lcd_write_data(Sec_Low);
	lcd_xy(2,1);
	lcd_write_data(Year_High);
	lcd_write_data(Year_Low);
	lcd_xy(2,3);
	lcd_write_data(Month_High);
	lcd_write_data(Month_Low);
	lcd_xy(2,5);
	lcd_write_data(Day_High);
	lcd_write_data(Day_Low);
}


/*EEPROM的写操作*/
void EEPROM_Write(uint addr,uint adata)
{
   SREG &= ~BIT(7);//关闭总中断
	while(EECR & BIT(EEWE));//等待EEWE为0
	
	EEAR = addr;//写地址
	EEDR = adata;//写数据
	
	EECR |= BIT(EEMWE);//将EEMWE置"1"
	EECR |= BIT(EEWE);//将EEWE置"1"
	
	SREG |= BIT(7);//打开总中断
}

/*EEPROM读操作*/
uchar EEPROM_Read(uint addr)
{
  uchar edata;
  SREG &= ~BIT(7);
  while( EECR & BIT(EEWE) );
  EEAR = addr;
  EECR |= BIT(EERE);//判断读操作是否完成
  edata = EEDR;
  return edata; 
}



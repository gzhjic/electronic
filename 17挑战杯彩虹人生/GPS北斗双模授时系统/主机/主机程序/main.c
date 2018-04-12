#include "nrf2401.h"

#define uchar unsigned char
#define uint unsigned int

uchar Data_legitimate=0;			//接收数据有效判断
uchar GPS_lock;						//定位有效判断
uchar GPSUSE_satellite[2];			//检测使用卫星个数<4就无法定位
uchar GPSVISIBLE_satellite[2];		//可见卫星个数
uchar GPSDATA_number;				//数据类型$GPGGA$GPGSV$GPGMC
uchar GPSDATA_mode;					//数据模式
uchar GPSDOT_count;					//逗号个数
uchar GPSDATA_count;				//数据存放计数
uchar GPSDATA_cmd[5];				//用来装数据类型
uchar GPS_latitude[9];				//用来装纬度
uchar GPS_latitude_dir;				//纬度的方向NS
uchar GPS_longitude[10];			//用来装经度
uchar GPS_longitude_dir;			//经度的方向WE
uchar GPS_speed[5]={'0','0','0','.','0'};//速度
uchar GPS_altitude[6];				//海拔高度
uchar GPS_date[6];					//日期
uchar GPS_time[6];					//时间
uchar GPS_Angle[5]={'0','0','0','0','0'};//方位角，初始为0
uchar OUT_speed[5];					//方位角

uchar Flag_GPSEnd=0;
uchar TXbuf[32];
uchar Flag_S[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void Mode1_TXbufSet(void);
parity_check(unsigned x);

/*************************串口初始化*******************************/
void uart_init(void)
{
	UCSRA=0X00;
	UCSRC=0x86;								//异步不倍速
	UBRRH=0x00;
	UBRRL=0x33;								//波特率9600
	UCSRB=0X98;								//使能
	SREG|=BIT(7);
}
/***************串口中断GPS解码***************************/
#pragma interrupt_handler usart:12
void usart(void)
{
	uchar UART_data;
		UART_data=UDR;
		switch(UART_data)
		{
			case '$':
				GPSDATA_number=0;		//GPS数据类型清空
				GPSDATA_mode=1;			//接收命令模式
				GPSDATA_count=0;		//接收位数清空
				break;
			
			case ',':
				GPSDOT_count++;		//逗号计数加1
				GPSDATA_count=0;
				break;
			
			case '*':
				Flag_GPSEnd=1;
				switch(GPSDATA_number)
				{
					case 1:
						Data_legitimate|=0x01;//GPGGA
						break;
					case 2:
						Data_legitimate|=0x02;//GPGSV
						break;
					case 3:
						Data_legitimate|=0x04;//GPRMC
						break;
				}
				GPSDATA_mode=0;
				break;
				
			default:
				if(GPSDATA_mode==1)									//类型种类判断
				{
					GPSDATA_cmd[GPSDATA_count]=UART_data;			//接收字符放入类型缓存
					if(GPSDATA_count==4)							//如果类型数据接收完毕，判断类型
					{											
						if		//判断GPGGA
						(
							(GPSDATA_cmd[0]=='G' ||GPSDATA_cmd[0]=='B' )
									&&
							(GPSDATA_cmd[1]=='P' ||GPSDATA_cmd[1]=='D' ||GPSDATA_cmd[1]=='N')
									&&
							GPSDATA_cmd[2]=='G'
									&&
							GPSDATA_cmd[3]=='G'
									&&
							GPSDATA_cmd[4]=='A'
									
						)
						{
							GPSDATA_number=1;
							GPSDATA_mode=2;
							GPSDOT_count=0;
							GPSDATA_count=0;
						}
						
						if		//判断GPGSV
						(
							(GPSDATA_cmd[0]=='G' ||GPSDATA_cmd[0]=='B' )
									&&
							(GPSDATA_cmd[1]=='P' ||GPSDATA_cmd[1]=='D' ||GPSDATA_cmd[1]=='N')
									&&
							GPSDATA_cmd[2]=='G'
									&&
							GPSDATA_cmd[3]=='S'
									&&
							GPSDATA_cmd[4]=='V'
						)
						{
							GPSDATA_number=2;
							GPSDATA_mode=2;
							GPSDOT_count=0;					
							GPSDATA_count=0;
						}
						
						if		//判断GPRMC
						(
							(GPSDATA_cmd[0]=='G' ||GPSDATA_cmd[0]=='B' )
									&&
							(GPSDATA_cmd[1]=='P' ||GPSDATA_cmd[1]=='D' ||GPSDATA_cmd[1]=='N')
									&&
							GPSDATA_cmd[2]=='R'
									&&
							GPSDATA_cmd[3]=='M'
									&&
							GPSDATA_cmd[4]=='C'
						)
						{
							GPSDATA_number=3;
							GPSDATA_mode=2;					
							GPSDOT_count=0;
							GPSDATA_count=0;
						}
						
					}
				}
				else if(GPSDATA_mode==2)					//接收数据处理
				{
					switch (GPSDATA_number)
					{
						case 1:												//类型1数据接收。GPGGA
							switch(GPSDOT_count)
							{
								case 2:										//纬度处理
									if(GPSDATA_count<9)
										GPS_latitude[GPSDATA_count]=UART_data;
									break;
								case 3:										//纬度方向处理
									if(GPSDATA_count<1)
										GPS_latitude_dir=UART_data;
									break;
								case 4:										//经度处理
									if(GPSDATA_count<10)
										GPS_longitude[GPSDATA_count]=UART_data;
									break;
								case 5:										//经度方向处理
									if(GPSDATA_count<1)
										GPS_longitude_dir=UART_data;
									break;
								case 6:										//定位判断
									if(GPSDATA_count<1)
										GPS_lock=UART_data;
									break;
								case 7:										//GPS使用卫星个数
									if(GPSDATA_count<2)
										GPSUSE_satellite[GPSDATA_count]=UART_data;
									break;
								case 9:										//海拔高度处理
									if(GPSDATA_count<6)
										GPS_altitude[GPSDATA_count]=UART_data;
									break;
							}
							break;
							
						case 2:												//类型2数据接收。GPGSV
							switch(GPSDOT_count)
							{
								case 3:										//GPS可见卫星个数
									if(GPSDATA_count<2)
										GPSVISIBLE_satellite[GPSDATA_count]=UART_data;
									break;
							}
						break;
							
						case 3:												//类型3数据接收。GPRMC
							switch(GPSDOT_count)
							{
								case 1:										//时间处理
									if(GPSDATA_count<6)		
										GPS_time[GPSDATA_count]=UART_data;	
									break;
								case 2:										//定位判断						
									if(GPSDATA_count<1)
									{
									  if(UART_data=='A')
											GPS_lock=1;
									  if(UART_data=='V')
									    GPS_lock=0;
									}
									break;
								case 3:										//纬度处理						
									if(GPSDATA_count<9)
									{
										GPS_latitude[GPSDATA_count]=UART_data;
									}
									break;
								case 4:										//纬度方向处理						
									if(GPSDATA_count<1)
									{
										GPS_latitude_dir=UART_data;
									}
									break;
								case 5:										//经度处理						
									if(GPSDATA_count<10)
									{
										GPS_longitude[GPSDATA_count]=UART_data;
									}
									break;
								case 6:										//经度方向处理						
									if(GPSDATA_count<1)
									{
										GPS_longitude_dir=UART_data;
									}
									break;
								case 7:										//速度处理						
									if(GPSDATA_count<5)
									{
										GPS_speed[GPSDATA_count]=UART_data;
									}
									break;
								case 8:										//方位角处理						
									if(GPSDATA_count<5)
									{
										GPS_Angle[GPSDATA_count]=UART_data;
									}
									break;
								case 9:										//日期				
									if(GPSDATA_count<6)
									{
										GPS_date[GPSDATA_count]=UART_data;
									}
									break;
							}
							break;
					}
				}
				GPSDATA_count++;		//接收数位加1
				break;
		}
}

void delay(uint ms) 
{    
	uint i,j;  
    for (i=0;i<ms;i++) 
	{   
		for(j=0;j<1140;j++); 
	}
}

void main(void) 
{     
	DDRC=0XFF;
	DDRD|=0XF0 ;
	DDRB=(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB7);  //24L01端口初始化 //把MISO设置为输入和IRQ设置为输入既可 
	PORTB = 0xff;
	DDRA&=0x3f;								//电池检测脚初始化
	PORTA|=0XC0;
	init_NRF24L01();        
	uart_init();      
	while(1)  
	{                   
		if(Flag_GPSEnd)
		{
			Mode1_TXbufSet();
			nRF24L01_TxPacket(TXbuf);
			SPI_RW_Reg(WRITE_REG+STATUS,0XFF);   //将24L01的状态标志位置“1
			Flag_GPSEnd=0;
		}
		//delay(5);
	} 
}

/****************************************************************
 //广播模式下发送的数据处理函数 
       详情见项目目录下通信协议
 ***************************************************************/
void Mode1_TXbufSet(void)					
{
	uchar i,sum; 
	TXbuf[0]=0x43;							//起始位
	TXbuf[1]=0x01;							//工作模式
	for(i=2;i<8;i++)						//时间日期
	{
		TXbuf[i]=GPS_time[i-2];
		TXbuf[i+6]=GPS_date[i-2];
	} 
	switch(PINA&0xc0)						//电池充电状态
	{
		case 0x40:TXbuf[14]=0x10;break;
		case 0x80:TXbuf[14]=0x01;break;
		default :TXbuf[14]=0x11;
	}
	for(i=0;i<14;i++)						//从机工作状态
	{
		if(Flag_S[i])
		TXbuf[i+14]=1;
		else
		TXbuf[i+14]=0;
	}
	if((GPS_time[5]>=0x30)&&(GPS_time[5]<=0x30+60))		//判断GPS是否收到时间
	{
		TXbuf[29]=1;									
	}
	else
		TXbuf[29]=0;
	for(i=1;i<29;i++)						//求校验和
		 sum=sum+TXbuf[i];
	if(parity_check(sum))					//奇偶校验位
		TXbuf[30]=1;
	else
		TXbuf[30]=0;
	sum=0;
	TXbuf[31]=0x34;							//停止位
}


/*函数功能：如果1的个数为奇数个，则返回1，如果1的个数为偶数个，则返回0。*/
parity_check(unsigned int x)
{
    unsigned int val=0;
    while(x)
    {
        val^=x;//val 和x进行异或运算
        x>>=1;//x右移一位
    }
    return val&0x1;//取末位运算. val的二进制形式最后一位位1则返回1，为0则返回0.
}


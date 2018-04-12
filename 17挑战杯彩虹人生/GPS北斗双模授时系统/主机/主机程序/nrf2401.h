 #ifndef _nrf2401_h_
 #define _nrf2401_h_


 #include "iom16v.h"
 #include "macros.h"  
/*
// #define NRF24L01_MISO          PB4  //输入0 		//数据输出
#define   Hign_24L01_MISO    PORTB |= (1 << PB4)  
#define   Low_24L01_MISO     PORTB &= ~(1 << PB4) 
#define   Read_24L01_MISO    PINB & (1 << PB4)    
//#define NRF24L01_MOSI         PB3       //输出1 //数据输入
#define   Hign_24L01_MOSI    PORTB |= (1 << PB6)  
#define   Low_24L01_MOSI     PORTB &= ~(1 << PB6)
//#define   Read_24L01_MOSI    PINB & (1 << PB6)
//#define NRF24L01_SCK    PB5      //输出1 		//时钟线
#define   Hign_24L01_SCK    PORTB |= (1 << PB3)  
#define   Low_24L01_SCK     PORTB &= ~(1 << PB3)
//#define   Read_24L01_SCK    PINB & (1 << PC3);
//#define NRF24L01_CSN       PB2       //输出1	//片选端
#define   Low_24L01_CSN     PORTB &= ~(1 << PB5) 
#define   Hign_24L01_CSN    PORTB |= (1 << PB5) 
//#define NRF24L01_CE         PB1       //输出1	//收发模式选择端
#define   Hign_24L01_CE    PORTB |= (1 << PB2) 
#define   Low_24L01_CE     PORTB &= ~(1 << PB2)  
//#define   Read_24L01_CE    PINB & (1 << PB2)  
//#define  NRF24L01_IRQ     PB0        //输入	//可屏蔽中断
#define   Hign_NRF24L01_IRQ    PORTB |= (1 << PB7) 
#define   Low_NRF24L01_IRQ     PORTB &= ~(1 << PB7)
#define   Read_NRF24L01_IRQ    PINB & (1 << PB7) 
*/

// #define NRF24L01_MISO          PB4  //输入0 		//数据输出
#define   Hign_24L01_MISO    PORTB |= (1 << PB6)  
#define   Low_24L01_MISO     PORTB &= ~(1 << PB6) 
#define   Read_24L01_MISO    PINB & (1 << PB6)    
//#define NRF24L01_MOSI         PB3       //输出1 //数据输入
#define   Hign_24L01_MOSI    PORTB |= (1 << PB5)  
#define   Low_24L01_MOSI     PORTB &= ~(1 << PB5)
#define   Read_24L01_MOSI	 PINB  & (1<<PB5)
//#define   Read_24L01_MOSI    PINB & (1 << PB6)
//#define NRF24L01_SCK    PB7      //输出1 		//时钟线
#define   Hign_24L01_SCK    PORTB |= (1 << PB7)  
#define   Low_24L01_SCK     PORTB &= ~(1 << PB7)
//#define   Read_24L01_SCK    PINB & (1 << PC3);
//#define NRF24L01_CSN       PB2       //输出1	//片选端
#define   Low_24L01_CSN     PORTB &= ~(1 << PB4) 
#define   Hign_24L01_CSN    PORTB |= (1 << PB4) 
//#define NRF24L01_CE         PB1       //输出1	//收发模式选择端
#define   Hign_24L01_CE    PORTB |= (1 << PB3) 
#define   Low_24L01_CE     PORTB &= ~(1 << PB3)  
//#define   Read_24L01_CE    PINB & (1 << PB2)  
//#define  NRF24L01_IRQ     PB0        //输入	//可屏蔽中断
#define   Hign_NRF24L01_IRQ    PORTB |= (1 << PB2) 
#define   Low_NRF24L01_IRQ     PORTB &= ~(1 << PB2)
#define   Read_NRF24L01_IRQ    PINB & (1 << PB2) 


//*********************************************NRF24L01*************************************  
#define TX_ADR_WIDTH    5  
// 5 uints TX address width
#define RX_ADR_WIDTH    5    
// 5 uints RX address width 
#define TX_PLOAD_WIDTH  32  
// 20 uints TX payload 
#define RX_PLOAD_WIDTH  32 
// 20 uints TX payload  

//接收地址 //***************************************NRF24L01寄存器指令******************************************************* 
#define READ_REG        0x00  
// 读寄存器指令
#define WRITE_REG       0x20  
// 写寄存器指令
#define RD_RX_PLOAD     0x61   
// 读取接收数据指令 
#define WR_TX_PLOAD     0xA0  
// 写待发数据指令
#define FLUSH_TX        0xE1 
// 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2 
// 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3   
// 定义重复装载数据指令 
#define NOP1            0xFF  
// 保留 
//*************************************SPI(nRF24L01)寄存器地址**************************************************** 
#define CONFIG          0x00  
// 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01 
// 自动应答功能设置 
#define EN_RXADDR       0x02  
// 可用信道设置 
#define SETUP_AW        0x03 
// 收发地址宽度设置 
#define SETUP_RETR      0x04  
// 自动重发功能设置
#define RF_CH           0x05  
// 工作频率设置  
#define RF_SETUP        0x06 
// 发射速率、功耗功能设置 
#define STATUS          0x07  
// 状态寄存器 
#define OBSERVE_TX      0x08 
// 发送监测功能 
#define CD              0x09  
// 地址检测
#define RX_ADDR_P0      0x0A 
// 频道0接收数据地址
#define RX_ADDR_P1      0x0B 
// 频道1接收数据地址 
#define RX_ADDR_P2      0x0C
// 频道2接收数据地址 
#define RX_ADDR_P3      0x0D 
// 频道3接收数据地址 
#define RX_ADDR_P4      0x0E  
// 频道4接收数据地址 
#define RX_ADDR_P5      0x0F
// 频道5接收数据地址
#define TX_ADDR         0x10 
// 发送地址寄存器
#define RX_PW_P0        0x11 
// 接收频道0接收数据长度 
#define RX_PW_P1        0x12  
// 接收频道0接收数据长度
#define RX_PW_P2        0x13 
// 接收频道0接收数据长度
#define RX_PW_P3        0x14 
// 接收频道0接收数据长度 
#define RX_PW_P4        0x15  
// 接收频道0接收数据长度
#define RX_PW_P5        0x16
// 接收频道0接收数据长度 
#define FIFO_STATUS     0x17  
// FIFO栈入栈出状态寄存器设置 
#define MAX_RT    0x10  
// Max #of TX retrans interrupt 
#define TX_DS     0x20
// TX data sent interrupt 
#define RX_DR     0x40 
// RX data received 

extern char sta,count,tf;  


extern char TxBuf[32];
 
extern void Delay(int s);
extern char SPI_RW(char data); //功能：NRF24L01的SPI写时序 
extern char SPI_Read(char reg); //功能：NRF24L01的SPI时序  
extern char SPI_RW_Reg(char reg, char value);//功能：NRF24L01读写寄存器函数
extern char SPI_Read_Buf(char reg, char *pBuf, char uchars);//功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数 
extern char SPI_Write_Buf(char reg, char *pBuf, char uchars);//功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
extern void SetRX_Mode(void); //功能：数据接收配置
extern char nRF24L01_RxPacket(char* rx_buf);//功能：数据读取后放如rx_buf接收缓冲区中
extern void nRF24L01_TxPacket(char * tx_buf); //功能：发送 tx_buf中数据
extern void init_NRF24L01(void);	//NRF24L01初始化


#endif
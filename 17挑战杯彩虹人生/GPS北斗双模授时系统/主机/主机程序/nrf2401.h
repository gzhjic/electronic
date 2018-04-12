 #ifndef _nrf2401_h_
 #define _nrf2401_h_


 #include "iom16v.h"
 #include "macros.h"  
/*
// #define NRF24L01_MISO          PB4  //����0 		//�������
#define   Hign_24L01_MISO    PORTB |= (1 << PB4)  
#define   Low_24L01_MISO     PORTB &= ~(1 << PB4) 
#define   Read_24L01_MISO    PINB & (1 << PB4)    
//#define NRF24L01_MOSI         PB3       //���1 //��������
#define   Hign_24L01_MOSI    PORTB |= (1 << PB6)  
#define   Low_24L01_MOSI     PORTB &= ~(1 << PB6)
//#define   Read_24L01_MOSI    PINB & (1 << PB6)
//#define NRF24L01_SCK    PB5      //���1 		//ʱ����
#define   Hign_24L01_SCK    PORTB |= (1 << PB3)  
#define   Low_24L01_SCK     PORTB &= ~(1 << PB3)
//#define   Read_24L01_SCK    PINB & (1 << PC3);
//#define NRF24L01_CSN       PB2       //���1	//Ƭѡ��
#define   Low_24L01_CSN     PORTB &= ~(1 << PB5) 
#define   Hign_24L01_CSN    PORTB |= (1 << PB5) 
//#define NRF24L01_CE         PB1       //���1	//�շ�ģʽѡ���
#define   Hign_24L01_CE    PORTB |= (1 << PB2) 
#define   Low_24L01_CE     PORTB &= ~(1 << PB2)  
//#define   Read_24L01_CE    PINB & (1 << PB2)  
//#define  NRF24L01_IRQ     PB0        //����	//�������ж�
#define   Hign_NRF24L01_IRQ    PORTB |= (1 << PB7) 
#define   Low_NRF24L01_IRQ     PORTB &= ~(1 << PB7)
#define   Read_NRF24L01_IRQ    PINB & (1 << PB7) 
*/

// #define NRF24L01_MISO          PB4  //����0 		//�������
#define   Hign_24L01_MISO    PORTB |= (1 << PB6)  
#define   Low_24L01_MISO     PORTB &= ~(1 << PB6) 
#define   Read_24L01_MISO    PINB & (1 << PB6)    
//#define NRF24L01_MOSI         PB3       //���1 //��������
#define   Hign_24L01_MOSI    PORTB |= (1 << PB5)  
#define   Low_24L01_MOSI     PORTB &= ~(1 << PB5)
#define   Read_24L01_MOSI	 PINB  & (1<<PB5)
//#define   Read_24L01_MOSI    PINB & (1 << PB6)
//#define NRF24L01_SCK    PB7      //���1 		//ʱ����
#define   Hign_24L01_SCK    PORTB |= (1 << PB7)  
#define   Low_24L01_SCK     PORTB &= ~(1 << PB7)
//#define   Read_24L01_SCK    PINB & (1 << PC3);
//#define NRF24L01_CSN       PB2       //���1	//Ƭѡ��
#define   Low_24L01_CSN     PORTB &= ~(1 << PB4) 
#define   Hign_24L01_CSN    PORTB |= (1 << PB4) 
//#define NRF24L01_CE         PB1       //���1	//�շ�ģʽѡ���
#define   Hign_24L01_CE    PORTB |= (1 << PB3) 
#define   Low_24L01_CE     PORTB &= ~(1 << PB3)  
//#define   Read_24L01_CE    PINB & (1 << PB2)  
//#define  NRF24L01_IRQ     PB0        //����	//�������ж�
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

//���յ�ַ //***************************************NRF24L01�Ĵ���ָ��******************************************************* 
#define READ_REG        0x00  
// ���Ĵ���ָ��
#define WRITE_REG       0x20  
// д�Ĵ���ָ��
#define RD_RX_PLOAD     0x61   
// ��ȡ��������ָ�� 
#define WR_TX_PLOAD     0xA0  
// д��������ָ��
#define FLUSH_TX        0xE1 
// ��ϴ���� FIFOָ��
#define FLUSH_RX        0xE2 
// ��ϴ���� FIFOָ��
#define REUSE_TX_PL     0xE3   
// �����ظ�װ������ָ�� 
#define NOP1            0xFF  
// ���� 
//*************************************SPI(nRF24L01)�Ĵ�����ַ**************************************************** 
#define CONFIG          0x00  
// �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01 
// �Զ�Ӧ�������� 
#define EN_RXADDR       0x02  
// �����ŵ����� 
#define SETUP_AW        0x03 
// �շ���ַ������� 
#define SETUP_RETR      0x04  
// �Զ��ط���������
#define RF_CH           0x05  
// ����Ƶ������  
#define RF_SETUP        0x06 
// �������ʡ����Ĺ������� 
#define STATUS          0x07  
// ״̬�Ĵ��� 
#define OBSERVE_TX      0x08 
// ���ͼ�⹦�� 
#define CD              0x09  
// ��ַ���
#define RX_ADDR_P0      0x0A 
// Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B 
// Ƶ��1�������ݵ�ַ 
#define RX_ADDR_P2      0x0C
// Ƶ��2�������ݵ�ַ 
#define RX_ADDR_P3      0x0D 
// Ƶ��3�������ݵ�ַ 
#define RX_ADDR_P4      0x0E  
// Ƶ��4�������ݵ�ַ 
#define RX_ADDR_P5      0x0F
// Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10 
// ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11 
// ����Ƶ��0�������ݳ��� 
#define RX_PW_P1        0x12  
// ����Ƶ��0�������ݳ���
#define RX_PW_P2        0x13 
// ����Ƶ��0�������ݳ���
#define RX_PW_P3        0x14 
// ����Ƶ��0�������ݳ��� 
#define RX_PW_P4        0x15  
// ����Ƶ��0�������ݳ���
#define RX_PW_P5        0x16
// ����Ƶ��0�������ݳ��� 
#define FIFO_STATUS     0x17  
// FIFOջ��ջ��״̬�Ĵ������� 
#define MAX_RT    0x10  
// Max #of TX retrans interrupt 
#define TX_DS     0x20
// TX data sent interrupt 
#define RX_DR     0x40 
// RX data received 

extern char sta,count,tf;  


extern char TxBuf[32];
 
extern void Delay(int s);
extern char SPI_RW(char data); //���ܣ�NRF24L01��SPIдʱ�� 
extern char SPI_Read(char reg); //���ܣ�NRF24L01��SPIʱ��  
extern char SPI_RW_Reg(char reg, char value);//���ܣ�NRF24L01��д�Ĵ�������
extern char SPI_Read_Buf(char reg, char *pBuf, char uchars);//����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ��� 
extern char SPI_Write_Buf(char reg, char *pBuf, char uchars);//����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���
extern void SetRX_Mode(void); //���ܣ����ݽ�������
extern char nRF24L01_RxPacket(char* rx_buf);//���ܣ����ݶ�ȡ�����rx_buf���ջ�������
extern void nRF24L01_TxPacket(char * tx_buf); //���ܣ����� tx_buf������
extern void init_NRF24L01(void);	//NRF24L01��ʼ��


#endif
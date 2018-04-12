#include "nrf24l01.h"
char sta,count,tf;
char  TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01}; 
//���ص�ַ 
char  RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01}; 
//���յ�ַ
void Delay(int s) 
{ 
	unsigned int i; 
	for(i=0; i<s; i++); 
	for(i=0; i<s; i++);
} 

//������uint SPI_RW(uint uchar) 
//���ܣ�NRF24L01��SPIдʱ��  *************************/ 
char SPI_RW(char data) 
{  
char i,temp=0;      
for(i=0;i<8;i++) // output 8-bit     
{   
if(data & 0x80)   
{    
Hign_24L01_MOSI;          		// output 'uchar', MSB to MOSI   
}   
else   
{    
Low_24L01_MOSI;    
}    
data = (data << 1);            // shift next bit into MSB..   
temp<<=1;   
Hign_24L01_SCK;                 // Set SCK high..   
if(Read_24L01_MISO){temp++;}           // capture current MISO bfit   
Low_24L01_SCK;                 // ..then set SCK low again     
}     
return(temp);        		   // return read uchar 
}  
/***
//������uchar SPI_Read(uchar reg)
 //���ܣ�NRF24L01��SPIʱ��  ******************/ 
 
char SPI_Read(char reg) 
{  
char reg_val;
Low_24L01_CSN;                // CSN low, initialize SPI communication...  
SPI_RW(reg);            // Select register to read from..  
reg_val = SPI_RW(0);    	// ..then read registervalue  
Hign_24L01_CSN;                // CSN high, terminate SPI communication    
return(reg_val);        // return register value 
} 
 /***************  //���ܣ�NRF24L01��д�Ĵ�������  ********************/  
char SPI_RW_Reg(char reg, char value) 
{  
char status;
Low_24L01_CSN;                   // CSN low, init SPI transaction  
status = SPI_RW(reg);      // select register  
SPI_RW(value);             // ..and write value to it..  
Hign_24L01_CSN;            // CSN high again    
return(status);            // return nRF24L01 status uchar 
}  /****************************************  
//������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)  
//����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���  ******************/  
char SPI_Read_Buf(char reg, char *pBuf, char uchars) 
{  
int status1,uchar_ctr;
Low_24L01_CSN;                      // Set CSN low, init SPI tranaction  
status1 = SPI_RW(reg);         // Select register to write to and read status uchar
for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++) 
pBuf[uchar_ctr] = SPI_RW(0);    //     
Hign_24L01_CSN;                               
return(status1);                    // return nRF24L01 status uchar 
}  /**************************************************************  
//������uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)  
//����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ��� ***********************/  
char SPI_Write_Buf(char reg, char *pBuf, char uchars) 
{  
char status1,uchar_ctr;    
Low_24L01_CSN;             //SPIʹ��  
status1 = SPI_RW(reg);     
for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) 
//  
SPI_RW(*pBuf++);  
Hign_24L01_CSN;           //�ر�SPI  
return(status1); 
}  /************************  
���ܣ����ݽ�������   ********************************************/ 
void SetRX_Mode(void) 
{  
Low_24L01_CE;
//SPI_Write_Buf(WRITE_REG + RX_PW_P0, TX_ADDRESS,TX_ADR_WIDTH);
SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);     // IRQ�շ�����ж���Ӧ��16λCRC ��������  
Hign_24L01_CE; 
Delay(1200);			  //ע�ⲻ��̫С 
}  
/*****************************************************  
//������unsigned char nRF24L01_RxPacket(unsigned char* rx_buf) 
//���ܣ����ݶ�ȡ�����rx_buf���ջ�������  ************/

char nRF24L01_RxPacket(char* rx_buf) 
{      
char revale=0;  
SetRX_Mode();
sta=SPI_Read(STATUS);      // ��ȡ״̬�Ĵ������ж����ݽ���״��    
if(sta&0x40)                 // �ж��Ƿ���յ�����  
{     
Low_24L01_CE;    //SPIʹ��   
SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// �����ܵ������ݴ�RX_FIFO buffer   
revale =1;   				//��ȡ������ɱ�־  
}  
SPI_RW_Reg(WRITE_REG+STATUS,sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־  
  		/*  Low_24L01_CSN;
          SPI_RW(FLUSH_RX);
          Hign_24L01_CSN;*/
return revale; 
}  
/**********************************************  
//������void nRF24L01_TxPacket(char * tx_buf) 
//���ܣ����� tx_buf������  ****************************************/  
void nRF24L01_TxPacket(char * tx_buf) 
{  
Low_24L01_CE;   //StandBy Iģʽ   
SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 
// װ�ؽ��ն˵�ַ     
SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);     
// װ������   
SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);      
// IRQ�շ�����ж���Ӧ��16λCRC��������  
Hign_24L01_CE;   
//�ø�CE���������ݷ���  
Delay(600); 
}  
/********\**************************************/

//NRF24L01��ʼ��  *****************************************************/  
/*
void init_NRF24L01(void) 
{    
Low_24L01_CE;    // chip enable   
Hign_24L01_CSN;   // Spi disable     
Low_24L01_SCK;   // Spi clock line init high
//SPI_Write_Buf(WRITE_REG + TX_ADDR,  RX_ADDRESS, RX_ADR_WIDTH);    // д���ص�ַ   
SPI_Write_Buf(WRITE_REG + RX_PW_P0, TX_ADDRESS,TX_ADR_WIDTH); // д���Ͷ˵�ַ  
SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  Ƶ��0�Զ� ACKӦ������   
SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  �������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21    
SPI_RW_Reg(WRITE_REG + RF_CH,3);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ��  
SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);    //���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�   
SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);     // IRQ�շ�����ж���Ӧ��16λCRC ��������     
Delay(6000);

}
*/
void init_NRF24L01(void)
{   
	Low_24L01_CE;   
	// chip enable 
    Hign_24L01_CSN; 
	// Spi disable    
	Low_24L01_SCK; 
	 
	// Spi clock line init high 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH); 
	// д���ص�ַ  
	SPI_Write_Buf(WRITE_REG +  RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
	// д���ն˵�ַ  
	
	//SPI_Write_Buf(WR_TX_PLOAD, TxBuf, TX_PLOAD_WIDTH);/*******/
	
	SPI_RW_Reg(WRITE_REG + EN_AA,0x01); // 0
	//  Ƶ��0�Զ� ACKӦ������ ��ʹ�ܣ�  
	SPI_RW_Reg(WRITE_REG + EN_RXADDR,0x01); // 0
	//  �������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21 ��ʹ�ܣ�
	// SPI_RW_Reg(WRITE_REG + EN_AA, 0x00);          // �ر�ͨ��0�Զ�Ӧ��
   // SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x00);     // �رս���ͨ��0
	//SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x00); 
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a);//�Զ��ط�
	
	SPI_RW_Reg(WRITE_REG + RF_CH, 3);   //   �����ŵ�����Ϊ2.4GHZ���շ�����һ�� 
	     
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);  // 0//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB 
	
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ� 
	
	
	 
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0E);  // IRQ�շ�����ж���Ӧ��16λCRC ��������   
	Hign_24L01_CE;
	Delay(6000); 

}
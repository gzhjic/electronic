NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   007C   000A =     10. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       007C  __idata_start
       0086  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0086   0484 =   1156. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0043  __text_start
       0043  __start
       0065  _exit
       0066  _nrf24l01_Port_init
       0069  _main
       007F  _UART0
       00B7  _UART1
       00EF  _UART1_Init
       0103  _UART1_Send
       010A  _UART1_Receive
       0111  _UART1_Send_Char
       0121  _UART0_Init
       0135  _UART0_Send
       013C  _UART0_Receive
       0143  _UART0_Send_Char
       0153  _UART1_Send_RX
       0162  _delay_us
       016A  _delay_ms
       0179  _Delay
       018E  _SPI_RW
       01A6  _SPI_Read
       01B1  _SPI_RW_Reg
       01C0  _SPI_Read_Buf
       01DE  _SPI_Write_Buf
       01F4  _SetRX_Mode
       01FC  _nRF24L01_RxPacket
       0217  _nRF24L01_TxPacket
       0232  _init_NRF24L01
       025D  pop_xgset30FC
       0266  push_xgsetF0FC
       0268  push_xgset30FC
       026A  push_xgset00FC
       026C  push_xgset003C
       0271  push_xgset300C
       0276  pop_xgset300C
       027B  push_xgsetF000
       0280  pop_xgsetF000
       0285  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100   000A =     10. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  __data_start
       0100  _TX_ADDRESS
       0105  _RX_ADDRESS
       010A  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   010A   0024 =     36. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       010A  _RXbuf
       010A  __bss_start
       012A  _ddd
       012B  _tf
       012C  _count
       012D  _sta
       012E  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0074 =    116. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

E:\ICCV7\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
uart.o	[ uart.c ]
delay.o	[ delay.c ]
shounrf24l01.o	[ shounrf24l01.c ]
<library>	[ gpop4.s, gpush.s, gpushx.s, gpushy.s ]

User Global Definitions

ram_end = 0x4ff
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x7c
data = 0x100
eeprom:0.512


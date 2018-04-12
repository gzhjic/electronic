NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0045 =     69. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0099  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   009A   085C =   2140. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       004D  __start
       004D  __text_start
       006F  _exit
       0070  _uart_init
       007B  _usart
       02AF  _delay
       02C4  _main
       02E9  _Mode1_TXbufSet
       037D  _parity_check
       038F  _Delay
       03A4  _SPI_RW
       03BC  _SPI_Read
       03C7  _SPI_RW_Reg
       03D6  _SPI_Read_Buf
       03F4  _SPI_Write_Buf
       040A  _nRF24L01_TxPacket
       0425  _init_NRF24L01
       044F  pop_xgset30FC
       0458  push_xgsetF0FC
       045A  push_xgset30FC
       045C  push_xgset00FC
       045E  push_xgset003C
       0463  push_xgsetF000
       0468  pop_xgsetF000
       046D  push_xgsetF00C
       0474  pop_xgsetF00C
       047B  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0045 =     69. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _Data_legitimate
       0060  __data_start
       0061  _GPS_speed
       0066  _GPS_Angle
       006B  _Flag_GPSEnd
       006C  _Flag_S
       007B  _TxBuf
       009B  _TX_ADDRESS
       00A0  _RX_ADDRESS
       00A5  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   00A5   005D =     93. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       00A5  _TXbuf
       00A5  __bss_start
       00C5  _OUT_speed
       00CA  _GPS_time
       00D0  _GPS_date
       00D6  _GPS_altitude
       00DC  _GPS_longitude_dir
       00DD  _GPS_longitude
       00E7  _GPS_latitude_dir
       00E8  _GPS_latitude
       00F1  _GPSDATA_cmd
       00F6  _GPSDATA_count
       00F7  _GPSDOT_count
       00F8  _GPSDATA_mode
       00F9  _GPSDATA_number
       00FA  _GPSVISIBLE_satellite
       00FC  _GPSUSE_satellite
       00FE  _GPS_lock
       00FF  _tf
       0100  _count
       0101  _sta
       0102  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

E:\ICCV7\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
nrf2401.o	[ nrf2401.c ]
<library>	[ gpop4.s, gpush.s, gpushy.s, gpushz.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512


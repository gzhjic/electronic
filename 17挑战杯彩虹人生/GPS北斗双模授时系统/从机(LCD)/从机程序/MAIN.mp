NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0064 =    100. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       00B8  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00B8   0E88 =   3720. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       005C  __start
       005C  __text_start
       007E  _exit
       007F  _main
       0257  _P_init
       025E  _GetTime
       02E4  _UTCDate2LocalDate
       0311  _GetMaxDay
       0359  _IsLeapYear
       037B  _AllWriteIntoDS1302
       03AD  _AllReadDS1302
       03D6  _DataToASCII
       044D  _LCD_Display
       0495  _EEPROM_Write
       049F  _EEPROM_Read
       04AA  _lcd_port_init
       04B1  _lcd_xy
       04CF  _lcd_send_byte
       04DF  _lcd_write_com
       04F3  _lcd_write_data
       0507  _lcd_init
       052A  _lcd_clr
       0530  _lcd_write_char
       0545  _delay_ms
       0555  _delay_us
       056C  _Read_Byte
       058C  _Write_Byte
       05A3  _Read_ds1302
       05CD  _Write_ds1302
       0606  _Set_ds1302
       061F  _Init_ds1302
       062C  _Delay
       0641  _SPI_RW
       0659  _SPI_Read
       0664  _SPI_RW_Reg
       0673  _SPI_Read_Buf
       0691  _SPI_Write_Buf
       06A7  _SetRX_Mode
       06AF  _nRF24L01_RxPacket
       06CA  _nRF24L01_TxPacket
       06E5  _init_NRF24L01
       0710  mod16u
       0712  div16u
       0713  xdiv16u
       072C  mod8u
       072E  div8u
       072F  xdiv8u
       0744  empy16s
       0754  pop_xgset30FC
       075D  push_xgsetF0FC
       075F  push_xgset30FC
       0761  push_xgset00FC
       0763  push_xgset003C
       0768  push_xgset300C
       076D  pop_xgset300C
       0772  push_xgsetF00C
       0779  pop_xgsetF00C
       0780  push_xgset303C
       0787  pop_xgset303C
       078E  push_xgsetF03C
       0797  pop_xgsetF03C
       07A0  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0064 =    100. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _TXbuf
       00B8  _flag_lcd_start
       00B9  _history_messages_number
       00BA  _TX_ADDRESS
       00BF  _RX_ADDRESS
       00C4  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   00C4   003B =     59. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       00C4  __bss_start
       00C4  _Timetable_Flag
       00C5  _Timetable
       00C7  _TimeCorrect
       00C8  _Year
       00CA  _MaxDay
       00CB  _Year_Low
       00CC  _Year_High
       00CD  _Month_Low
       00CE  _Month_High
       00CF  _Month
       00D0  _Day_Low
       00D1  _Day_High
       00D2  _Day
       00D3  _Sec
       00D4  _Sec_Low
       00D5  _Sec_High
       00D6  _Min
       00D7  _Min_Low
       00D8  _Min_High
       00D9  _Hour_Low
       00DA  _Hour_High
       00DB  _Hour
       00DC  _RXbuf
       00FC  _tf
       00FD  _count
       00FE  _sta
       00FF  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

E:\ICCV7\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
12864.o	[ _12864.c ]
delay.o	[ delay.c ]
ds1302.o	[ ds1302.c ]
shounrf24l01.o	[ shounrf24l01.c ]
<library>	[ div16u.s, div8u.s, emul16s.s, gpop4.s, gpush.s, gpushx.s, gpushz.s, gpusha.s, gpushb.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512


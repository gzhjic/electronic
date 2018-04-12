NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0040 =     64. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0094  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0094   00D6 =    214. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       004A  __text_start
       004A  __start
       006C  _exit
       006D  _delay
       007F  _main
       0090  _UART_Init
       009D  _UART_Send
       00A1  _UART_Receive
       00A5  _UART_Send_Char
       00B5  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0040 =     64. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _data
       0060  __data_start
       0080  _data1
       00A0  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

E:\ICCV7\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
BlueTooth.o	[ BlueTooth.c ]
<library>	

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512


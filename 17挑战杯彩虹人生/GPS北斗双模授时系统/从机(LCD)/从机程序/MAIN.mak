CC = iccavr
LIB = ilibw
CFLAGS =  -IF:\AVR\test\成功接收\接收 -e -D__ICC_VERSION=722 -DATMega16  -l -g -MLongJump -MHasMul -MEnhanced -Wf-const_is_flash -DCONST="" 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = main.o 12864.o delay.o ds1302.o shounrf24l01.o 

MAIN:	$(FILES)
	$(CC) -o MAIN $(LFLAGS) @MAIN.lk   -lstudio -lcatmega
main.o: E:\ICCV7\include\iom16v.h .\shounrf24l01.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h .\12864.h .\delay.h .\ds1302.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
12864.o: .\12864.h .\delay.h E:\ICCV7\include\iom16v.h
12864.o:	12864.c
	$(CC) -c $(CFLAGS) 12864.c
delay.o: .\delay.h E:\ICCV7\include\iom16v.h
delay.o:	delay.c
	$(CC) -c $(CFLAGS) delay.c
ds1302.o: .\ds1302.h E:\ICCV7\include\iom16v.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h .\delay.h
ds1302.o:	ds1302.c
	$(CC) -c $(CFLAGS) ds1302.c
shounrf24l01.o: .\shounrf24l01.h E:\ICCV7\include\iom16v.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h
shounrf24l01.o:	shounrf24l01.c
	$(CC) -c $(CFLAGS) shounrf24l01.c

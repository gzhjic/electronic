CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -D_EE_EXTIO -DATMega164P  -l -g -MLongJump -MHasMul -MEnhanced -Wf-const_is_flash -DCONST="" 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x7c.0x4000 -dram_end:0x4ff -bdata:0x100.0x4ff -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = main.o uart.o delay.o shounrf24l01.o 

CONTROL:	$(FILES)
	$(CC) -o CONTROL $(LFLAGS) @CONTROL.lk   -lstudio -lcatmega
main.o: .\uart.h E:\ICCV7\include\iom164v.h .\delay.h .\shounrf24l01.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
uart.o: .\UART.h E:\ICCV7\include\iom164v.h
uart.o:	uart.c
	$(CC) -c $(CFLAGS) uart.c
delay.o: .\delay.h
delay.o:	delay.c
	$(CC) -c $(CFLAGS) delay.c
shounrf24l01.o: .\shounrf24l01.h E:\ICCV7\include\iom164v.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h
shounrf24l01.o:	shounrf24l01.c
	$(CC) -c $(CFLAGS) shounrf24l01.c

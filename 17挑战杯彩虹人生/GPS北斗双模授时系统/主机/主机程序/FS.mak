CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega16  -l -g -MLongJump -MHasMul -MEnhanced -Wf-const_is_flash -DCONST="" 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = main.o nrf2401.o 

FS:	$(FILES)
	$(CC) -o FS $(LFLAGS) @FS.lk   -lcatmega
main.o: .\nrf2401.h E:\ICCV7\include\iom16v.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
nrf2401.o: .\nrf2401.h E:\ICCV7\include\iom16v.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h
nrf2401.o:	nrf2401.c
	$(CC) -c $(CFLAGS) nrf2401.c

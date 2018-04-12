CC = iccavr
LIB = ilibw
CFLAGS =  -IF:\AVR\test\成功接收\接收 -IF:\AVRtest\双模\接收\12864 -IF:\AVRtest\双模\接收\24l01 -IF:\AVRtest\双模\接收\delay -IF:\AVRtest\双模\接收\12864 -e -D__ICC_VERSION=722 -DATMega16  -l -g -Wa-IF:\AVRtest\双模\接收\12864 -Wa-IF:\AVRtest\双模\接收\24l01 -Wa-IF:\AVRtest\双模\接收\delay -MLongJump -MHasMul -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -LF:\AVRtest\双模\接收\listing -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = main.o BlueTooth.o 

TEXT:	$(FILES)
	$(CC) -o TEXT $(LFLAGS) @TEXT.lk   -lstudio -lcatmega
main.o: C:\Users\Kong\Desktop\测试程序\BlueTooth.h E:\ICCV7\include\iom16v.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h
main.o:	C:\Users\Kong\Desktop\测试程序\main.c
	$(CC) -c $(CFLAGS) C:\Users\Kong\Desktop\测试程序\main.c
BlueTooth.o: C:\Users\Kong\Desktop\测试程序\BlueTooth.h E:\ICCV7\include\iom16v.h E:\ICCV7\include\macros.h E:\ICCV7\include\AVRdef.h
BlueTooth.o:	C:\Users\Kong\Desktop\测试程序\BlueTooth.c
	$(CC) -c $(CFLAGS) C:\Users\Kong\Desktop\测试程序\BlueTooth.c

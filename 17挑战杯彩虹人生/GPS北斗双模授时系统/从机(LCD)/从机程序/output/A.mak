CC = iccavr
LIB = ilibw
CFLAGS =  -IF:\AVR\test\�ɹ�����\���� -IF:\AVRtest\˫ģ\����\12864 -IF:\AVRtest\˫ģ\����\24l01 -IF:\AVRtest\˫ģ\����\delay -IF:\AVRtest\˫ģ\����\12864 -e -D__ICC_VERSION=722 -DATMega16  -l -g -Wa-IF:\AVRtest\˫ģ\����\12864 -Wa-IF:\AVRtest\˫ģ\����\24l01 -Wa-IF:\AVRtest\˫ģ\����\delay -MLongJump -MHasMul -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -LF:\AVRtest\˫ģ\����\listing -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = main.o 

A:	$(FILES)
	$(CC) -o A $(LFLAGS) @A.lk   -lstudio -lcatmega
main.o: E:\ICCV7\include\iom164v.h
main.o:	C:\Users\Kong\Desktop\ns\main.c
	$(CC) -c $(CFLAGS) C:\Users\Kong\Desktop\ns\main.c

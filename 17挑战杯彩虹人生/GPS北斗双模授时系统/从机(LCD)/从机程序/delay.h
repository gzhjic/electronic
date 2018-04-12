 
 
 
 #ifndef _delay_h_
 #define _delay_h_
 
 #include "iom16v.h"
 
 #define uchar unsigned char 
 #define uint  unsigned int 
 
 extern uchar history_messages_number;
 
 extern uchar const start_lcd_datatwo[];
 extern uchar const start_lcd_datathree[];
 extern uchar const start_lcd_datafour[];
 
 extern uchar const week_data[];
 extern uchar const lcd_data[];
 
 extern void delay_ms(uint xms);
 extern void delay_us(uint us);
 
 
 #endif  
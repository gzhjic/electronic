#include "tool.h"


void main(void)
{
    
    Task_Init();            //初始化
    Task_Read();            //读出EEPROM的数据
    while(1)
    {
        Task_Work();        //工作模式
        Task_LED();         //LED显示
        Task_DAC();         //电压输出
    }
}


void timer0_isr(void) interrupt 1
{
    Task_Display();         //数码管显示
    Task_Write();           //数据写进EEPROM
}


void timer2_isr(void) interrupt 12
{
    sonic_sent();           //发送超声波
    key_on();               //按键消痘
    Task_Time();            //获取时间
}




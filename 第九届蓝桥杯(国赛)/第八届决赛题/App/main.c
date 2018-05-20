#include "tool.h"


void main(void)
{
    
    Task_Init();            //��ʼ��
    Task_Read();            //����EEPROM������
    while(1)
    {
        Task_Work();        //����ģʽ
        Task_LED();         //LED��ʾ
        Task_DAC();         //��ѹ���
    }
}


void timer0_isr(void) interrupt 1
{
    Task_Display();         //�������ʾ
    Task_Write();           //����д��EEPROM
}


void timer2_isr(void) interrupt 12
{
    sonic_sent();           //���ͳ�����
    key_on();               //��������
    Task_Time();            //��ȡʱ��
}




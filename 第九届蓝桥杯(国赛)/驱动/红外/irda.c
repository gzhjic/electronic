#include "irda.h"

long frame_data;
bit frame_flag;

void Delay20us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 52;
	while (--i);
}


/* ��ȡ�ߵ�ƽʱ�� */
uchar get_pluse_time(void)
{
    uchar time = 0;
    while(ir)
    {
        time++;
        Delay20us();
        if(time == 250)     //5ms
            return time;    //��ʱ���
    }
    return time;
}


/* һ֡������4���ֽ�
 * ��һ���ֽ���ң��id
 * �ڶ����ֽ��ǵ�һ���ֽڵķ���
 * ������������ң�ص������ļ�ֵ
 * ���ĸ��ֽ��ǵ������ֽڵķ���
*/
uchar irda_process(void)
{
    uchar first_byte,sec_byte,tir_byte,fou_byte;
    first_byte = frame_data >> 24;
    sec_byte = (frame_data>>16) & 0xff;
    tir_byte = frame_data >> 8;
    fou_byte = frame_data;
    
    frame_flag = 0;
    //У�� �ɹ����ؼ�ֵ ʧ�ܷ���0
    if( (first_byte==(uchar)~sec_byte) && (first_byte==IRDA_ID) && tir_byte == (uchar)~fou_byte)
        return tir_byte;
    else
        return 0;
}
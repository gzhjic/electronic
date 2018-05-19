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


/* 获取高电平时间 */
uchar get_pluse_time(void)
{
    uchar time = 0;
    while(ir)
    {
        time++;
        Delay20us();
        if(time == 250)     //5ms
            return time;    //超时溢出
    }
    return time;
}


/* 一帧数据有4个字节
 * 第一个字节是遥控id
 * 第二个字节是第一个字节的反码
 * 第三个数据是遥控的真正的键值
 * 第四个字节是第三个字节的反码
*/
uchar irda_process(void)
{
    uchar first_byte,sec_byte,tir_byte,fou_byte;
    first_byte = frame_data >> 24;
    sec_byte = (frame_data>>16) & 0xff;
    tir_byte = frame_data >> 8;
    fou_byte = frame_data;
    
    frame_flag = 0;
    //校验 成功返回键值 失败返回0
    if( (first_byte==(uchar)~sec_byte) && (first_byte==IRDA_ID) && tir_byte == (uchar)~fou_byte)
        return tir_byte;
    else
        return 0;
}
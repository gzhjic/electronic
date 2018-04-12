#ifndef _setp_h_
#define _setp_h_

#include "stm32f10x.h"
#include "bsp_GeneralTim.h"

struct SetpStatus{
    long location;              //电机位置
    uint8_t direction;          //正反转
    uint8_t status;             //开关
};

extern struct SetpStatus setp1,setp2,setp3;

#define Z   1
#define N   0
#define ON  1
#define OFF 0


#define SETP1_OFF    GPIO_SetBits   (GPIOD, GPIO_Pin_0)
#define SETP1_ON   GPIO_ResetBits (GPIOD, GPIO_Pin_0)
#define SETP1_Z     GPIO_SetBits   (GPIOD, GPIO_Pin_1)
#define SETP1_N     GPIO_ResetBits (GPIOD, GPIO_Pin_1)

#define SETP2_OFF    GPIO_SetBits   (GPIOD, GPIO_Pin_2)
#define SETP2_ON   GPIO_ResetBits (GPIOD, GPIO_Pin_2)
#define SETP2_Z     GPIO_SetBits   (GPIOD, GPIO_Pin_3)
#define SETP2_N     GPIO_ResetBits (GPIOD, GPIO_Pin_3)


#define SETP3_OFF    GPIO_SetBits   (GPIOD, GPIO_Pin_4)
#define SETP3_ON   GPIO_ResetBits (GPIOD, GPIO_Pin_4)
#define SETP3_Z     GPIO_SetBits   (GPIOD, GPIO_Pin_5)
#define SETP3_N     GPIO_ResetBits (GPIOD, GPIO_Pin_5)

void Setp_Init(void);
void Setp_Reset(void);

#endif /*_setp_h_*/


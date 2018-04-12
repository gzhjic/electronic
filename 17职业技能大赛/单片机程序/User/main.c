#include "setp.h"
#include "bsp_usart.h"
#include "bsp_GeneralTim.h"
#include "bsp_SysTick.h"

#define M1_up   {SETP1_Z;SETP1_ON;setp1.status=ON;setp1.direction=Z;}
#define M2_up   {SETP2_Z;SETP2_ON;setp2.status=ON;setp2.direction=Z;}
#define M3_up   {SETP3_Z;SETP3_ON;setp3.status=ON;setp3.direction=Z;}

#define M1_down {SETP1_N;SETP1_ON;setp1.status=ON;setp1.direction=N;}
#define M2_down {SETP2_N;SETP2_ON;setp2.status=ON;setp2.direction=N;}
#define M3_down {SETP3_N;SETP3_ON;setp3.status=ON;setp3.direction=N;}

#define M3_OFF   {SETP3_OFF;setp3.status=OFF;}
#define M2_OFF   {SETP2_OFF;setp2.status=OFF;}
#define M1_OFF   {SETP1_OFF;setp1.status=OFF;}
#define delay   SysTick_Delay_Us

uint8_t RES_Flag;

void control(void)
{delay(0);M3_up;
delay(2847780);M3_OFF;
delay(2988068);Setp_Reset();
delay(5505269);M2_up;
delay(2549232);M2_OFF;
delay(1752475);Setp_Reset();
delay(447989);Setp_Reset();
delay(3983503);M1_up;
delay(3412270);M1_OFF;
delay(7527474);M1_down;
delay(1163238);M3_up;
delay(553678);M1_OFF;
delay(1530756);M3_OFF;
delay(2470789);M1_up;
delay(1340191);M1_OFF;
delay(1303608);Setp_Reset();
delay(7458290);M2_up;
delay(3198981);M2_OFF;
delay(4541183);M1_up;
delay(3175485);M1_OFF;
delay(649089);M2_down;
delay(1635591);M2_OFF;
delay(1436169);Setp_Reset();

}

int main(void)
{
    USART_Config();
    Setp_Init();
    SysTick_Init();
    printf("-------------------------------\n");
    printf("帮助:0xff\n");
    printf("所有电机停止:0x00\n");
    printf("电机A正转0x11\n");
    printf("电机A反转0x10\n");
    printf("电机B正转0x21\n");
    printf("电机B反转0x20\n");
    printf("电机C正转0x31\n");
    printf("电机C反转0x30\n");
    printf("-------------------------------\n");
   //control();
    while(1)
    {
        printf("电机A的位置:%d\t电机B的位置:%d\t电机C的位置:%d\n",setp1.location,setp2.location,setp3.location);
        SysTick_Delay_Ms(500);
        if(RES_Flag)
        {
            RES_Flag= 0 ;
            Setp_Reset();
        }
    }
}


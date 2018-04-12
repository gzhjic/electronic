#include "setp.h"



static void Setp_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOD, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|
                                     GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}    


void Setp_Init(void)
{
    GENERAL_TIM_Init();
    Setp_GPIO_Config();
    
    setp1.location = 0;
    setp3.location = 0;
    setp3.location = 0;
    
    SETP1_OFF;
    setp1.status = OFF;
    
    SETP1_N;
    setp1.direction = N; 
    
    SETP2_OFF;
    setp2.status = OFF;
    
    SETP2_N;
    setp2.direction = N; 
    
    SETP3_OFF;
    setp3.status = OFF;
    
    SETP3_N;
    setp3.direction = N; 
}


void Setp_Reset(void)
{
    while(setp1.location!=0 || setp2.location!=0 || setp3.location!=0)
    {
        if      (setp1.location >0)
        {
            SETP1_N;
            setp1.direction = N;
            SETP1_ON;
            setp1.status = ON;
        }
        else if (setp1.location <0)
        {
            SETP1_Z;
            setp1.direction = Z;
            SETP1_ON;
            setp1.status = ON;
        }
        else 
        {
            SETP1_OFF;
            setp1.status = OFF;
        }
        
        if      (setp2.location >0)
        {
            SETP2_N;
            setp2.direction = N;
            SETP2_ON;
            setp2.status = ON;
        }
        else if (setp2.location <0)
        {
            SETP2_Z;
            setp2.direction = Z;
            SETP2_ON;
            setp2.status = ON;
        }
        else
        {
            SETP2_OFF;
            setp2.status = OFF;
        }
        
        if      (setp3.location >0)
        {
            SETP3_N;
            setp3.direction = N;
            SETP3_ON;
            setp3.status = ON;
        }
        else if (setp3.location <0)
        {
            SETP3_Z;
            setp3.direction = Z;
            SETP3_ON;
            setp3.status = ON;
        }
        else
        {
            SETP3_OFF;
            setp3.status = OFF;
        }
    }
    SETP1_OFF;
    SETP2_OFF;
    SETP3_OFF;
    setp1.status = OFF;
    setp2.status = OFF;
    setp3.status = OFF;
}


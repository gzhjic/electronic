/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "setp.h"

extern void TimingDelay_Decrement(void);
extern uint8_t RES_Flag;
uint32_t count;

struct SetpStatus setp1,setp2,setp3;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
//    if(count++>=1000000)
//    {
//        count = 0;
//        printf("电机A的位置:%d\t电机B的位置:%d\t电机C的位置:%d\n",setp1.location,setp2.location,setp3.location);
//    }
}


void  GENERAL_TIM_IRQHandler (void)
{
    /*定时器更新中断*/
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
        /*电机位置改变 记录位置*/
		if(setp1.status == ON)                      
        {
            if      (setp1.direction == Z)
                setp1.location++;
            else if (setp1.direction == N)
                setp1.location--;
        }
        if(setp2.status == ON)
        {
            if      (setp2.direction == Z)
                setp2.location++;
            else if (setp2.direction == N)
                setp2.location--;
        }
        if(setp3.status == ON)
        {
            if      (setp3.direction == Z)
                setp3.location++;
            else if (setp3.direction == N)
                setp3.location--;
        }
        
        
		TIM_ClearITPendingBit(GENERAL_TIM , TIM_FLAG_Update);  	//清除中断标志位	 
	}	
    
}


void DEBUG_USART_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
        
        printf("0x%x\n",ucTemp);
        
        switch(ucTemp)
        {
            case 0x00:
                SETP1_OFF;
                setp1.status = OFF;
            
                SETP2_OFF;
                setp2.status = OFF;
            
                SETP3_OFF;
                setp3.status = OFF;
                printf("所有电机停止\n");
            break;
            
            case 0xff:
                printf("-------------------------------\n");
                printf("帮助:0xff\n");
                printf("电机复位:0x77\n");
                printf("所有电机停止:0x00\n");
                printf("电机A正转0x11\n");
                printf("电机A反转0x10\n");
                printf("电机B正转0x21\n");
                printf("电机B反转0x20\n");
                printf("电机C正转0x31\n");
                printf("电机C反转0x30\n");
                printf("-------------------------------\n");
            break;
            
            case 0x11:
                SETP1_Z;
                setp1.direction = Z;
                SETP1_ON;
                setp1.status = ON;
                printf("电机A正转\n");
            break;
            
            case 0x10:
                SETP1_N;
                setp1.direction = N;
                SETP1_ON;
                setp1.status = ON;
                printf("电机A反转\n");
            break;
            
            case 0x13:
                SETP1_OFF;
                setp1.status = OFF;
                printf("电机A停止\n");
            break;
            
            case 0x21:
                SETP2_Z;
                setp2.direction = Z;
                SETP2_ON;
                setp2.status = ON;
                printf("电机B正转\n");
            break;
            
            case 0x20:
                SETP2_N;
                setp2.direction = N;
                SETP2_ON;
                setp2.status = ON;
                printf("电机B反转\n");
            break;
            
            case 0x23:
                SETP2_OFF;
                setp2.status = OFF;
                printf("电机B停止\n");
            break;
            
            case 0x31:
                SETP3_Z;
                setp3.direction = Z;
                SETP3_ON;
                setp3.status = ON;
                printf("电机C正转\n");
            break;
            
            case 0x30:
                SETP3_N;
                setp3.direction = N;
                SETP3_ON;
                setp3.status = ON;
                printf("电机C反转\n");
            break;
            
            case 0x33:
                SETP3_OFF;
                setp3.status = OFF;
                printf("电机C停止\n");
            break;
            
            case 0x77:
                RES_Flag = 1;
            break;
        }
        
	}	 
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval None
  */

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

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
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_exti.h"
#include "led.h"
#include "key.h"

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
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

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
/*
@brief	通过忙等延时一段时间
@params	None
@retval	None

*/
static void delay_moment(void){
	int moment=0xfffff;
	while(moment--);
}

/*
@brief	外部中断线0的中断处理函数；检测按钮S1是否按下，如果按下点亮LED1；否则熄灭LED1
@params	None
@retval	None
*/
void EXTI0_IRQHandler(void){
	if(Key1_press()){
		// 如果按键按下就闪烁三次
		LED1_Set(1);
		delay_moment();
		LED1_Set(0);
		delay_moment();
		LED1_Set(1);
		delay_moment();
		LED1_Set(0);
		delay_moment();
		LED1_Set(1);
		delay_moment();
		LED1_Set(0);
		delay_moment();
	}else{
		LED1_Set(0);
	}
	EXTI_ClearITPendingBit(EXTI_Line0);	//清除中断标志（如果不清除会一直停留在中断状态）
}

void EXTI4_IRQHandler(void){
	if(Key1_press()){
		LED1_Set(1);
		delay_moment();
		LED1_Set(0);
		delay_moment();
	}else{
		LED1_Set(0);
	}
	EXTI_ClearITPendingBit(EXTI_Line4);	//清除中断标志（如果不清除会一直停留在中断状态）
}

void EXTI9_5_IRQHandler(void)
{
	  if(EXTI_GetITStatus(EXTI_Line7) != RESET) {
			if(Key1_press()){
				// 如果按键按下就闪烁三次
				LED1_Set(1);
				delay_moment();
				LED1_Set(0);
				delay_moment();
				LED1_Set(1);
				delay_moment();
				LED1_Set(0);
				delay_moment();
				LED1_Set(1);
				delay_moment();
				LED1_Set(0);
				delay_moment();
			}else{
			LED1_Set(0);
		}
    EXTI_ClearITPendingBit(EXTI_Line7); //清除中断标志（如果不清除会一直停留在中断状态）
  }
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

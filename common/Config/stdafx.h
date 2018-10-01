#ifndef __STDAFX_H__
#define __STDAFX_H__

#include"stm32f10x.h"

typedef unsigned char uchar;

// 8位LED的IO口定义
#define RCC_LED 	RCC_APB2Periph_GPIOF	
#define GPIO_LED 	GPIOF
#define GPIO_PIN_LED 	(GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7\
|GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10)

// 单独LED的IO口定义
#define RCC_LED1 	RCC_APB2Periph_GPIOF	
#define GPIO_LED1 	GPIOF
#define GPIO_PIN_LED1 	GPIO_Pin_3

// 单个独立按键的IO口定义
#define RCC_KEY1 	RCC_APB2Periph_GPIOD	
#define GPIO_KEY1 	GPIOD
#define GPIO_PIN_KEY1 	GPIO_Pin_7

// 1位中断
#define RCC_EXIT1   RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD
#define GPIO_EXIT1  GPIO_PortSourceGPIOD
#define GPIO_PIN_EXIT1 	GPIO_PinSource7
#define LINE_EXIT1  EXTI_Line7
#define CHANNEL_EXIT1   EXTI9_5_IRQn

// 串口
#define RCC_USART1   RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA
#define GPIO_USART1  GPIOA
#define GPIO_PIN_USART1_TX 	GPIO_Pin_9
#define GPIO_PIN_USART1_RX 	GPIO_Pin_10

// 定时器
#define TIM1_PRESCALER  7200 - 1
#define TIM1_PERIOD     10000 - 1
#define TIM1_ClOCKDIVISION      TIM_CKD_DIV1
#define TIM1_COUNTERMODE        TIM_CounterMode_Up


#define TIM2_PRESCALER  7200 - 1
#define TIM2_PERIOD     10000 - 1
#define TIM2_ClOCKDIVISION      TIM_CKD_DIV1
#define TIM2_COUNTERMODE        TIM_CounterMode_Up
#define TIM2_IRQ_CHANNEL        TIM2_IRQn

// ADC
#define RCC_ADC1        RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC
#define GPIO_ADC1       GPIOC
#define GPIO_PIN_ADC1   GPIO_Pin_1
#define ADC1_CHANNEL    ADC_Channel_1
#endif
// STM32F10X_MD,USE_STDPERIPH_DRIVER

/*
 * filename	exti.h
 * author	Lonelinessqwf
 * brief	中断声明
 */
#ifndef __EXTI_H_
#define __EXTI_H_

#include "stdafx.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

// 初始化1位外部中断
void EXTI1_Init(void);
// 配置1位中断
void NVIC_init(void);
#endif

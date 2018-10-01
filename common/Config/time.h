/*
 * filename	time.h
 * author	Lonelinessqwf
 * brief	定时器声明
 */
#ifndef __TIME_H_
#define __TIME_H_

#include "stdafx.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void TIM1_Delay(void);
void TIM1_Counter(void);
void TIM1_PWM(void);

void TIM2_Delay(void);
void TIM2_Counter(void);
void TIM2_PWM(void);

#endif

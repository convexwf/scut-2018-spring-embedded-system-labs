/*
 * filename	led.h
 * author	Lonelinessqwf
 * brief	LED头文件，单个LED和8位LED相关函数声明
 */
#ifndef __LED_H_
#define __LED_H_

#include "stdafx.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

// 打开IO时钟和初始化GPIO(八位LED)
void LED_Init(void);
// 设置八位LED的状态
void LED_Sets(uint16_t data);

// 打开IO时钟和初始化GPIO(单个LED)
void LED1_Init(void);
// 单个LED设置
void LED1_Set(uint8_t a);
// 单个LED闪烁
void LED1_Twinkle(uint8_t count);

#endif

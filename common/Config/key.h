/*
 * filename	key.h
 * author	Lonelinessqwf
 * brief	Key头文件，独立按键相关函数声明
 */
#ifndef __KEY_H_
#define __KEY_H_

#include "stdafx.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

// 打开IO时钟和初始化GPIO
void Key1_Init(void);
// 检测独立按键是否按下
char Key1_press(void);
#endif

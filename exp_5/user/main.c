/*
@file	main.c
@brief	通用定时器定时实例,让LED1间隔1s闪烁
@author	Zev
*/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "led.h"
#include "time.h"

/*
@brief	初始化定时器定时1s
@params	None
@retval	0 程序正常结束
*/
int main(void){
	
	LED1_Init();	//初始化LED1
	TIM1_Init();
	
	
	while(1);	//等待定时时间到来，跳转执行中断处理程序TIM1_UP_IRQHandler
	
	return 0;
}

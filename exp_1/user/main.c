/*
@file	main.c
@brief	测试程序（HelloWorld），检验灯亮
@author	picy
*/

#include "stdafx.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


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
@brief	初始化LED灯，实现让LED亮
@params	None
@retval	0 程序正常结束
*/
int main(void){
	GPIO_InitTypeDef gpio_init;
	
	//使能APB2时钟
	RCC_APB2PeriphClockCmd(RCC_LED1,ENABLE);
	
	//设置为推挽输出
	gpio_init.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin=GPIO_PIN_LED1;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO_LED1,&gpio_init);
	
	while(1){
		
		//设置为高电平,根据电路图LED灯亮
		GPIO_ResetBits(GPIO_LED1,GPIO_PIN_LED1);
    delay_moment();
		//设置为低电平,根据电路图LED灯灭 
		GPIO_SetBits(GPIO_LED1,GPIO_PIN_LED1);
		delay_moment();
	}
}


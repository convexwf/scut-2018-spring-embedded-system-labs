#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"


/*
@brief	初始化LED1和按钮S1，进入死循环等待外部中断发生，执行中断处理函数
@params	None
@retval	0 程序正常结束
*/
int main(void){
	LED1_Init();	//初始化LED1
	Key1_Init();	//初始化按钮S1
	EXTI1_Init();
	while(1);	//等待外部中断发生
	//return 0;
}

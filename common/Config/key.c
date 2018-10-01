#include "Key.h"


void Key1_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	
	// 打开Key使用的GPIO的时钟使能
	RCC_APB2PeriphClockCmd(RCC_KEY1, ENABLE);

	// 初始化相应的GPIO
	GPIO_Init(GPIO_KEY1, &GPIO_InitStructure);
}

char Key1_press(void) {
	return !GPIO_ReadInputDataBit(GPIO_KEY1,GPIO_PIN_KEY1);
}


#include "led.h"

static void delay_moment(void);

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	// 打开LED使用的GPIO的时钟使能
	RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);

	// 初始化相应的GPIO
	GPIO_Init(GPIO_LED, &GPIO_InitStructure);

}

void LED_Sets(uint8_t data)
{
}

void LED1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	// 打开LED使用的GPIO的时钟使能
	RCC_APB2PeriphClockCmd(RCC_LED1, ENABLE);

	// 初始化相应的GPIO
	GPIO_Init(GPIO_LED1, &GPIO_InitStructure);

}

/*
@brief	通过忙等延时一段时间
@params	传入1设置高电平，传入0设置低电平
@retval	None
*/
void LED1_Set(uint8_t a)
{
	// a = 1时，高电平，灯亮
	// a = 0时，低电平，灯灭
	if(a) GPIO_SetBits(GPIO_LED1,GPIO_PIN_LED1);
	else  GPIO_ResetBits(GPIO_LED1,GPIO_PIN_LED1);
}

/*
@brief	LED1闪烁
@params	闪烁的次数
@retval	None
*/
void LED1_Twinkle(uint8_t count)
{
	for(uint8_t i = 0; i < count; i++)
	{
		LED1_Set(1);
		delay_moment();
		LED1_Set(0);
		delay_moment();
	}
}

/*
@brief	通过忙等延时一段时间
@params	None
@retval	None
*/
static void delay_moment(void){
	int moment=0xfffff;
	while(moment--);
}

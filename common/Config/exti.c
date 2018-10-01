#include "exti.h"

void EXTI1_Init(void)
{
	EXTI_InitTypeDef exti_init;
	RCC_APB2PeriphClockCmd(RCC_EXIT1,ENABLE);	  
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_EXIT1,GPIO_PIN_EXIT1);    //配置连接引脚
	
	
	exti_init.EXTI_Line=LINE_EXIT1;              //外部中断线   连接引脚
	exti_init.EXTI_LineCmd=ENABLE;               //外部中断使能 
	exti_init.EXTI_Mode=EXTI_Mode_Interrupt;     //外部中断模式 
	exti_init.EXTI_Trigger=EXTI_Trigger_Rising_Falling;   //采用上升沿下降沿触发中断 
	
	EXTI_Init(&exti_init);
	NVIC_init();
}

void NVIC_init(void)
{
	NVIC_InitTypeDef nvic_init;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);      //配置中断组别0，抢占式优先级0位，响应优先级4位 
	nvic_init.NVIC_IRQChannel=CHANNEL_EXIT1;                //外部0中断 
	nvic_init.NVIC_IRQChannelCmd=ENABLE;                 //中断使能 
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;       //抢占优先级0
	nvic_init.NVIC_IRQChannelSubPriority=0;              //响应优先级0 
	NVIC_Init(&nvic_init);
}

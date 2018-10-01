#include "time.h"

static void NVIC_Config(void);

void TIM1_Delay(void)
{
	TIM_TimeBaseInitTypeDef tim_base_init;
	NVIC_InitTypeDef nvic_init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	//设定定时器定时1s
	TIM_TimeBaseStructInit(&tim_base_init);
	tim_base_init.TIM_Prescaler=72000-1;      //72000000/7200=10000
	tim_base_init.TIM_Period=1000-1;
	TIM_TimeBaseInit(TIM1,&tim_base_init);
	//设置TIM1的更新中断
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	nvic_init.NVIC_IRQChannel=TIM1_UP_IRQn;
	nvic_init.NVIC_IRQChannelCmd=ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;
	nvic_init.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic_init);

	TIM_Cmd(TIM1,ENABLE);
}

void TIM1_PWM(void)
{
	TIM_TimeBaseInitTypeDef tim_base_init;
	NVIC_InitTypeDef nvic_init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	TIM_TimeBaseStructInit(&tim_base_init);
	tim_base_init.TIM_CounterMode = TIM_CounterMode_Up; 
	tim_base_init.TIM_Prescaler=1024-1;      //72000000/7200=10000
	tim_base_init.TIM_Period=200-1;
	TIM_TimeBaseInit(TIM1,&tim_base_init);
	
	//设置输出通道2为PWM1模式
	TIM_OCStructInit(&tim_oc_init);
	tim_oc_init.TIM_OCMode=TIM_OCMode_PWM1;           //输出PWM1模式
	tim_oc_init.TIM_OCPolarity=TIM_OCPolarity_Low;		
	tim_oc_init.TIM_OutputState=TIM_OutputState_Enable;  //输出状态使能
	tim_oc_init.TIM_Pulse=0;							
	TIM_OC1Init(TIM1,&tim_oc_init);
	
	//响应TIM2的更新中断
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);      //清除TIM1更新中断标志
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);  //使能TIM1更新中断
	nvic_init.NVIC_IRQChannel=TIM1_IRQn;       //TIM1中断
	nvic_init.NVIC_IRQChannelCmd=ENABLE;       //使能此通道中断
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;  //抢占中断优先级0
	nvic_init.NVIC_IRQChannelSubPriority=0;         //响应中断优先级0
	NVIC_Init(&nvic_init);
	
	TIM_Cmd(TIM1,ENABLE);
}

void TIM2_Counter(void) {
	TIM_TimeBaseInitTypeDef tim_base_init;
	NVIC_InitTypeDef nvic_init;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_DeInit(TIM2);
	tim_base_init.TIM_Period = 0xFFFF;                     //装载周期设定尽量大数字，程序影响不大
	tim_base_init.TIM_Prescaler = 0x00;                    //不预分频
	tim_base_init.TIM_ClockDivision =TIM_CKD_DIV1;        //时间分割值1
	tim_base_init.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数模式
	TIM_TimeBaseInit(TIM2, &tim_base_init);
	TIM_ETRClockMode1Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);	//将定时器设置为下降沿触发计数

	//设置定时器被外部触发时产生中断
	TIM_ITConfig(TIM2,TIM_IT_Trigger,ENABLE);           //使能TIM2输入通道中断源
	nvic_init.NVIC_IRQChannel=TIM2_IRQn;                //TIM2触发中断
	nvic_init.NVIC_IRQChannelCmd=ENABLE;                //使能中断通道
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;      //抢占优先级0
	nvic_init.NVIC_IRQChannelSubPriority=0;             //响应优先级0
	NVIC_Init(&nvic_init);
	
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef tim_base_init;
    //设定定时器参数
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructInit(&tim_base_init);
	tim_base_init.TIM_Prescaler = TIM2_PRESCALER;      //72000000/7200=10000
	tim_base_init.TIM_Period = TIM2_PERIOD;
	TIM_TimeBaseInit(TIM1,&tim_base_init);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    NVIC_Config();
    TIM_Cmd(TIM2,ENABLE);
}

static void NVIC_Config(void)
{
    NVIC_InitTypeDef nvic_init;
    //设置TIM1的更新中断
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	nvic_init.NVIC_IRQChannel = TIM1_UP_IRQn;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init);
}

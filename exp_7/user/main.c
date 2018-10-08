/**
@file	main.c
@brief	消息邮箱实例
@author	Zev
@note	此程序用于实验箱
*/
#include "stdafx.h"
#include "includes.h"
#include "misc.h"
#include "stm32f10x_tim.h"
#include "led.h"
#include "usart.h"
#include "adc.h"

#define TASK_STK_SIZE	80			//任务栈的大小


unsigned char  RUN[8]={0x30,0x0e,0x39,0x07};  


OS_STK switch_stk[TASK_STK_SIZE];	//检测开关任务栈
OS_STK led_stk[TASK_STK_SIZE];		//控制LED任务栈
OS_STK usart_stk[TASK_STK_SIZE];	//串口任务栈
OS_STK run_stk[TASK_STK_SIZE];	//串口任务栈

INT8U motor_status = STATUS_STOP;
INT8U motor_direction = DIRECTION_PLUS;
OS_EVENT *pmailbox;					//消息邮箱指针


static void TIM4_config(void);
static void output_config(void);
static void TIM_config(void);
static void systick_config(void);
static void switch_task(void *pdata);
static void led_task(void *pdata);
static void usart_task(void *pdata);
static void run_task(void *pdata);

/**
@brief	创建任务
@param	None
@retval	如果程序正常结束返回0
*/
int main(void){
	output_config();
	TIM_config();
	TIM4_config();
	usart_config();
	ADC1_Init();
	systick_config();
	
	OSInit();
	OSTaskCreate(led_task,(void*)0,led_stk+(TASK_STK_SIZE-1),5);
	OSTaskCreate(switch_task,(void*)0,switch_stk+(TASK_STK_SIZE-1),6);
	OSTaskCreate(usart_task,(void*)0,usart_stk+(TASK_STK_SIZE-1),7);
	//OSTaskCreate(run_task,(void*)0,run_stk+(TASK_STK_SIZE-1),8);
	OSStart();
	
	return 0;
}

static void output_config(void) {
	GPIO_InitTypeDef gpio_init;

	RCC_APB2PeriphClockCmd(RCC_OUTPUT,ENABLE);

	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio_init.GPIO_Pin=GPIO_PIN_OUTPUT1 | GPIO_PIN_OUTPUT2;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO_OUTPUT1,&gpio_init);	
}

static void TIM4_config(void)
{
	TIM_TimeBaseInitTypeDef tim_base_init;
	NVIC_InitTypeDef nvic_init;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_DeInit(TIM4);
	tim_base_init.TIM_Period = 0xffff;                     //装载周期设定尽量大数字，程序影响不大
	tim_base_init.TIM_Prescaler = 0x00;                    //不预分频
	tim_base_init.TIM_ClockDivision =TIM_CKD_DIV1;        //时间分割值1
	tim_base_init.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数模式
	TIM_TimeBaseInit(TIM4, &tim_base_init);
	TIM_ETRClockMode1Config(TIM4, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_Inverted, 0);	//将定时器设置为下降沿触发计数
	
	//设置定时器被外部触发时产生中断
	TIM_ITConfig(TIM4,TIM_IT_Trigger,ENABLE);           //使能TIM2输入通道中断源
	//TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 
	nvic_init.NVIC_IRQChannel=TIM4_IRQn;                //TIM2触发中断
	nvic_init.NVIC_IRQChannelCmd=ENABLE;                //使能中断通道
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;      //抢占优先级0
	nvic_init.NVIC_IRQChannelSubPriority=0;             //响应优先级0
	NVIC_Init(&nvic_init);
	
	TIM_Cmd(TIM4,ENABLE);
}

static void TIM_config(void){
	TIM_TimeBaseInitTypeDef tim_base_init;
	TIM_OCInitTypeDef tim_oc_init;
	NVIC_InitTypeDef nvic_init;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//计时周期按照个人喜好可以加减，这会影响到实际的呼吸灯效果
	TIM_TimeBaseStructInit(&tim_base_init);
	tim_base_init.TIM_CounterMode=TIM_CounterMode_Up;       //向上计数模式
	tim_base_init.TIM_Period=1024-1;                        //设置装载计数周期值
	tim_base_init.TIM_Prescaler=200-1;                      //设置分频 
	TIM_TimeBaseInit(TIM2,&tim_base_init);
	
	//设置输出通道2为PWM1模式
	TIM_OCStructInit(&tim_oc_init);
	tim_oc_init.TIM_OCMode=TIM_OCMode_PWM1;           //输出PWM1模式
	tim_oc_init.TIM_OCPolarity=TIM_OCPolarity_High;		//注意LED1是给低电平才点亮，所以输出极性为低
	tim_oc_init.TIM_OutputState=TIM_OutputState_Enable;  //输出状态使能
	tim_oc_init.TIM_Pulse=0;							//初始值而已，在更新中断中会根据“呼吸数组”改变
	TIM_OC1Init(TIM2,&tim_oc_init);
	TIM_OC2Init(TIM2,&tim_oc_init);
	
	//响应TIM2的更新中断
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);      //清除TIM2更新中断标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //使能TIM2更新中断
	nvic_init.NVIC_IRQChannel=TIM2_IRQn;       //TIM2中断
	nvic_init.NVIC_IRQChannelCmd=ENABLE;       //使能此通道中断
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;  //抢占中断优先级0
	nvic_init.NVIC_IRQChannelSubPriority=0;         //响应中断优先级0
	NVIC_Init(&nvic_init);
	
	TIM_Cmd(TIM2,ENABLE);
}

/**
@brief	检测开关USER1是否按下,并群邮消息
@param	pdata 创建任务时传入的数据
@retval	None
*/
static void switch_task(void *pdata){
	INT8U data = 0;
	GPIO_InitTypeDef gpio_init_1, gpio_init_2;

	RCC_APB2PeriphClockCmd(RCC_KEY,ENABLE);

	gpio_init_1.GPIO_Mode=GPIO_Mode_IPU;
	gpio_init_1.GPIO_Pin=GPIO_PIN_KEY1;
	gpio_init_1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO_KEY1,&gpio_init_1);
	
	gpio_init_2.GPIO_Mode=GPIO_Mode_IPU;
	gpio_init_2.GPIO_Pin=GPIO_PIN_KEY2;
	gpio_init_2.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO_KEY2,&gpio_init_2);


	while(1){
		
		while(1)
		{
			if(GPIO_ReadInputDataBit(GPIO_KEY1, GPIO_PIN_KEY1)){	//按钮没按
			motor_direction = motor_direction;
			data = 0;
			}else{	//按钮按下
				motor_direction = DIRECTION_MINUS + DIRECTION_PLUS - motor_direction;
				data = motor_direction;
				break;
			}

			if(GPIO_ReadInputDataBit(GPIO_KEY2, GPIO_PIN_KEY2)){	//按钮没按
				motor_status = motor_status;
				data = 0;
			}else{	//按钮按下
				motor_status = motor_status % 6 + 1;
				data = motor_status;
				break;
			}
		}

		if(data > 0) OSMboxPostOpt(pmailbox,&data,OS_POST_OPT_BROADCAST);	//群邮消息
		
		OSTimeDly(100);
	}
}
/**
@brief	根据收到的邮箱消息，控制LED的亮灭
@param	pdata 创建任务时传入的数据
@retval	None
*/
static void led_task(void *pdata){
	INT8U err;
	INT8U *pd;
	INT16U setValue = 0x0000;
	
	LED_Init();
	
	// pmailbox=OSMboxCreate(NULL);
	
	while(1){
		setValue = 0xffff;
		if(motor_direction == DIRECTION_PLUS) setValue |= 0x0400;
		else setValue |= 0x0200;
		if(motor_status == STATUS_STOP) setValue |= 0x0100;
		else if(motor_status == STATUS_SPIN1) setValue |= 0x0080;
		else if(motor_status == STATUS_SPIN2) setValue |= 0x0040;
		else if(motor_status == STATUS_SPIN3) setValue |= 0x0020;
		else if(motor_status == STATUS_SPIN4) setValue |= 0x0010;
		else if(motor_status == STATUS_SPIN5) setValue |= 0x0008;
		LED_Sets(setValue);
		
		OSTimeDly(1);
	}
	
}
/**
@brief	通过串口向上位机发送接收到的邮箱消息
@param	pdata 创建任务时传入的数据
@retval	None
*/
static void run_task(void *pdata){
	INT8U err;
	INT8U *pd;
	uint8_t i;
	
		GPIO_InitTypeDef gpio_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	gpio_init.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_All;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init);
	
	 while (1)
 { 
        for (i=0; i<8; i++)       //Ò»¸öÖÜÆÚ×ª3.75*8=30¶È
        {
          GPIO_Write(GPIOA, RUN[i]); //È¡Êý¾Ý ´ÓGPIO¿ÚÊä³ö
          OSTimeDly(1);             //µ÷½Ú×ªËÙ
        }
  }
}

/**
@brief	通过串口向上位机发送接收到的邮箱消息
@param	pdata 创建任务时传入的数据
@retval	None
*/
static void usart_task(void *pdata){
	INT8U err;
	INT8U *pd;
	
// 		while(1){
// 		if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)){					//ADC??????
// 			float voltage=3.3f/4096*ADC_GetConversionValue(ADC1);	//??????
// 			printf("%f\n",voltage);		
// 			OSTimeDly(1);										//??????
// 		}
// 	}
	
	
	//pmailbox=OSMboxCreate(NULL);
	uint8_t pcnt = 0;
	
	while(1){
		//pd=(INT8U*)OSMboxPend(pmailbox,0,&err);
		//usart_send_char(*pd);
		uint8_t cnt = TIM_GetCounter(TIM4);
		usart_send_char(cnt-pcnt);
		pcnt = cnt;
		OSTimeDly(10);
	}
}

/**
@brief	配置每一次ucos系统滴答调用一次SysTick_Handler
@param	None
@retval	None
@note	这是一个私有函数
*/
static void systick_config(void){
	RCC_ClocksTypeDef rcc_clk;
	
	RCC_GetClocksFreq(&rcc_clk);
	SysTick_Config(rcc_clk.SYSCLK_Frequency/OS_TICKS_PER_SEC);
}

#ifdef  USE_FULL_ASSERT
/**
@brief	如果传递给库函数的参数错误将会调用此函数，指出出错的文件名以及行数
@param	None
@retval	None
@note	库函数会调用此函数，不需要自己调用
*/
void assert_failed(uint8_t* file, uint32_t line){
	//printf("Error:in file %s, at line %d",file,line);
	while(1);
}
#endif

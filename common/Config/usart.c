/*
@file	usart.c
@brief	实现与串口通信相关的接口
@author	Zev
*/
#include "usart.h"

/*
@brief	初始化与串口通信相关的GPIO
@params	None
@retval	None
@note	这是一个私有函数
*/
static void gpio_init(void){
	GPIO_InitTypeDef gpio_init;
	
	//USART1_TX
	gpio_init.GPIO_Pin = GPIO_PIN_USART1_TX;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIO_USART1, &gpio_init);
	//USART1_RX
	gpio_init.GPIO_Pin = GPIO_PIN_USART1_RX;
    gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_USART1, &gpio_init);
}

/*
@brief	配置串口接收中断
@params	None
@retval	None
@note	这是一个私有函数
*/
static void NVIC_Config(void){
	NVIC_InitTypeDef nvic_init;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	nvic_init.NVIC_IRQChannel=USART1_IRQn;
	nvic_init.NVIC_IRQChannelCmd=ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority=0;
	nvic_init.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic_init);
}	

/*
@brief	初始化与串口通信相关的时钟、GPIO以及串口通信的参数
@params	None
@retval	None
*/
void USART1_Init(void){
	
	USART_InitTypeDef usart_init={
		.USART_BaudRate=9600,
		.USART_WordLength=USART_WordLength_8b,
		.USART_StopBits=USART_StopBits_1,
		.USART_Parity=USART_Parity_No,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx
	};
	
	RCC_APB2PeriphClockCmd(RCC_USART1, ENABLE);
	gpio_init();
	USART_Init(USART1,&usart_init);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	NVIC_Config();
	
	USART_Cmd(USART1,ENABLE);
	
}
/*
@brief	将一个字节数据发送给上位机
@params	data 待发送的数据
@retval	None
*/
void usart_send_byte(unsigned char data){
	USART_SendData(USART1,(uint8_t)data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);	//等待数据发送完成
}
/*
@brief	利用查询的方式接收一个字节数据
@params	None
@retval	接收到的一个字节数据
*/
uchar usart_recv_byte(void){
	while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE));//查询是否接收到数据
	return USART_ReceiveData(USART1);
}



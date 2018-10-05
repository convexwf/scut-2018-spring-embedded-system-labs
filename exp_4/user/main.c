/*
@file	main.c
@brief	利用中断方式实现串行通信
@author	Zev
*/
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"

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
@brief	初始化串口,然后等待接收上位机的数据
@params	None
@retval	0 程序正常结束
*/
int main(void){
	LED1_Init();
	USART1_Init();	//初始化串口
	
	// 第一种方式：查询
	while(1){
		uint8_t data=usart_recv_byte();		//利用查询的方式接收上位机的一个字节数据
		usart_send_byte(data);		//将接收到的数据发送给上位机
		if (data == 0x01) {
			LED1_Set(1);
		} else if (data == 0x02) {
			LED1_Set(0);
		}
	}
	
	// 第二种方式中断
	while(1)		//如果接收到上位机的数据，跳转执行中断处理函数USART1_IRQHandler
	{
	}
}

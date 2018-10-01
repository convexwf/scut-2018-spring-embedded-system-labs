/*
 * filename	exti.h
 * author	Lonelinessqwf
 * brief	串口声明
 */
#ifndef __USART_H_
#define __USART_H_

#include "stdafx.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

extern uint8_t rx_buf[RX_BUF_SIZE];
extern uint32_t volatile rx_buf_size;

void USART1_Init(void);

void usart_send_byte(uchar data);
uchar usart_recv_byte(void);

#endif

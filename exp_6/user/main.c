/*
@file	main.c
@brief	??ADC????????????,??????????
@author	Zev
*/

#include "stm32f10x.h"
#include "adc.h"
#include "usart.h"

static void delay_moment(void);

/*
@brief	??ADC????????????,??????????
@params	None
@retval	0 ??????
*/
int main(void){
	
	
	//??ADC1???10???????????
	ADC1_Init();
	USART1_Init();
	
	while(1){
		if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)){					//ADC??????
			float voltage=3.3f/4096*ADC_GetConversionValue(ADC1);	//??????
			usart_send_byte((uint8_t)voltage);
			delay_moment();											//??????
		}
	}
	
	return 0;
}

/*
@brief	??????
@params	None
@retval	None
*/
void delay_moment(void){
	int moment=0xffffff;
	while(moment--);
}
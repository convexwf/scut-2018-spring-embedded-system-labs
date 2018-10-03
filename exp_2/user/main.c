#include "LED.h"
#include "Key.h"

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
@brief	检测按钮S1是否按下，如果按下则使LED闪烁
@params	None
@retval 0 程序正常结束
*/
int main(void){
	LED1_Init();	//初始化LED1
	Key1_Init();	//初始化按键S1
	
	while(1){
		if(Key1_press()){	//按钮按下
			LED1_Set(1);	//点亮LED1
			delay_moment();
			LED1_Set(0);	//点亮LED1
			delay_moment();
		}else{				//按钮松开
			LED1_Set(0);		//熄灭LED1
		}
	}
}

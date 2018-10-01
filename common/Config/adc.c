#include "adc.h"

static void gpio_config() {
    //配置IO口为模拟输入
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Mode=GPIO_Mode_AIN;
    gpio_init.GPIO_Pin=GPIO_PIN_ADC1;
    GPIO_Init(GPIO_ADC1,&gpio_init);
}

void ADC1_Init() {
    RCC_APB2PeriphClockCmd(RCC_ADC1,ENABLE);
    gpio_config();
    ADC_DeInit(ADC1);
    ADC_InitTypeDef adc_init;
    adc_init.ADC_ContinuousConvMode=ENABLE;
    adc_init.ADC_DataAlign=ADC_DataAlign_Right;
    adc_init.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
    adc_init.ADC_Mode=ADC_Mode_Independent;
    adc_init.ADC_NbrOfChannel=1;
    adc_init.ADC_ScanConvMode=DISABLE;
    ADC_Init(ADC1,&adc_init);
    RCC_ADCCLKConfig(RCC_PCLK2_Div2);
    ADC_RegularChannelConfig(ADC1,ADC1_CHANNEL,1,ADC_SampleTime_239Cycles5);

    ADC_Cmd(ADC1,ENABLE);

    // ADC校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);	//软件触发ADC转换
}

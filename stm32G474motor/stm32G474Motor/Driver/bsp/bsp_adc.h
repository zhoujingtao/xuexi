#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "main.h"
#include "adc.h"


#define adc1_samples  	5 		// 单通道采样点数
#define adc1_channel  	9 		// 采样通道数
#define adc1_length   	adc1_samples*adc1_channel 		// 数据数

#define adc2_samples  	5 		// 单通道采样点数
#define adc2_channel  	3 		// 采样通道数
#define adc2_length   	adc2_samples*adc2_channel 		// 数据数

extern uint16_t adc1_dma_value[adc1_samples][adc1_channel]; 
extern uint16_t adc2_dma_value[adc2_samples][adc2_channel];

void adc_bsp_init(void);
void adc1_injected_callback(void);
void adc2_injected_callback(void);

uint16_t adc1_median_filter(uint8_t channel);
uint16_t adc1_avg_filter(uint8_t channel);

uint16_t adc2_median_filter(uint8_t channel);
uint16_t adc2_avg_filter(uint8_t channel);



#endif /* __ADC_BSP_H__ */


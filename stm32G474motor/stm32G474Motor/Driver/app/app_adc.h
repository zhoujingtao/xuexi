#ifndef __APP_ADC_H__
#define __APP_ADC_H__

#include "main.h"
#include "bsp.h"
#include "adc.h"

/* adc通道名字定义，根据自己的使用来命名 */
typedef enum
{
	adc1_ch1 = 0,//IC
	adc1_ch2 = 1,//IB
	adc1_ch3 = 2,//IA
	adc1_ch4 = 3,//IBUS
	adc1_ch5 = 4,//VA
	adc1_ch6 = 5,//VB
	adc1_ch7 = 6,//VC
	adc1_ch8 = 7,//NT3
	adc1_ch9 = 8 //NT1
} adc1_num;

typedef enum
{
	adc2_ch1 = 0,//VBUS
	adc2_ch2 = 1,//电位器
	adc2_ch3 = 2//NT2
} adc2_num;

typedef struct app_adc
{
	int16_t IC;
	int16_t IB;
	int16_t IA;
	int16_t IBUS;
	int16_t VA;
	int16_t VB;
	int16_t VC;
	int16_t NT3;
	int16_t NT1;
	int16_t VBUS;
	int16_t NT2;
	int16_t potentiometers;
	/* data */
}ADCSample_Data;




void adc_driver_init(void);

void app_TransducersData_process(void);

#endif /* __ADC_DRIVER_H__ */



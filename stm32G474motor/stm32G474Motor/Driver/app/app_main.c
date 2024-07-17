#include "app_main.h"


void app_MainInit(void)
{
    led_driver_init();
		key_driver_init();		
		LCD_Init();//LCD≥ı ºªØ
		LCD_Fill(0,0,LCD_W,LCD_H,BLACK);	
	
	
    adc_driver_init();
		OS_TaskInit();
	
}


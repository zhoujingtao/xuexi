#include "app_main.h"


void app_MainInit(void)
{
    led_driver_init();
		key_driver_init();		
	
    adc_driver_init();
		OS_TaskInit();
	
}


#include "app_LCDDisplayed.h"


void app_LCDDisplayed(void)
{
    LCD_ShowChinese(40,0,"ÖÐ¾°Ô°µç×Ó",RED,WHITE,32,0);
		LCD_ShowString(10,33,"LCD_W:",RED,WHITE,32,0);
		LCD_ShowIntNum(106,33,LCD_W,3,RED,WHITE,32);
		LCD_ShowString(10,66,"LCD_H:",RED,WHITE,32,0);
		LCD_ShowIntNum(106,66,LCD_H,3,RED,WHITE,32);



}



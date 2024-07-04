#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void)
{

	
	Serial_Init();
	
	while (1)
	{
		uint8_t MyArray[]={0x42,0x43,0x44,0x45};
    Serial_SendArray(MyArray,4);

    Serial_SendString("Hello world!\n");

    Serial_SendNumber(1234 , 4);
		
		if (Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
		}
	}
}

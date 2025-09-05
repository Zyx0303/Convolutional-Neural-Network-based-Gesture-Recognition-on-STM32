#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "key.h"
#include "W25Q64.h"
#include "Serial.h"
#include "LED.h"
#include "EXIT.h"

uint8_t ID;

uint8_t i;

int main(void)
{

	OLED_Init();
	MPU6050_Init();
	W25Q64_Init();
	LED_Init();
	Exit_Init();
	OLED_ShowString(2,1,"Left Earse");
	OLED_ShowString(3,1,"Right Record");
	while(1)
	{
		//注意，该状态由中断控制，主程序在EXIT.c中.
		Process_EXTI0_Event();
		Process_EXTI2_Event();

}
}
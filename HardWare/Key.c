#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef Key_t;
	Key_t.GPIO_Mode = GPIO_Mode_IPU;
	Key_t.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_0;
	Key_t.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&Key_t);
	
}
uint8_t Key_GetNum(void)
{
	uint8_t Key_Num = 0;
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
	{	Delay_ms(200);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0);
		Delay_ms(200);
		Key_Num = 1;}
	else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
	{	Delay_ms(200);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
		Delay_ms(200);
		Key_Num = 2;}
	else{Key_Num = 0;}
	return Key_Num;
	
}
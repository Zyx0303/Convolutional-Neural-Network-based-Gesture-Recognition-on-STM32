#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef LED_t;
	LED_t.GPIO_Mode = GPIO_Mode_Out_OD;
	LED_t.GPIO_Pin = GPIO_Pin_8;
	LED_t.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&LED_t);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
}
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
//void LED1_TURN(void)
//{
//	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)==0)
//	{
//		LED1_OFF();
//	}
//	else
//	{
//		LED1_ON();
//	}
//	
//}
//void LED2_ON(void)
//{
//	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//}
//void LED2_OFF(void)
//{
//	GPIO_SetBits(GPIOA,GPIO_Pin_1);
//}

//void LED2_TURN(void)
//{
//	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
//	{
//		LED2_OFF();
//	}
//	else
//	{
//		LED2_ON();
//	}
//	
//}
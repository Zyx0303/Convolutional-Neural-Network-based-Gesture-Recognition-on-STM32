#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "OLED.h"
#include "delay.h"
#include "MPU6050.h"
#include "W25Q64.h"
#include "LED.h"
uint16_t ms = 0;
int16_t Data[6];
uint32_t Address = 0x000000;
uint8_t KeyStatue = 0;//判断开关状态。状态为0时，表示按按钮前W25Q64不工作。状态为1时，表示按按钮前W25Q64工作。
volatile uint8_t exti0_flag = 0;  // EXTI0中断标志
volatile uint8_t exti2_flag = 0;  // EXTI2中断标志
void Exit_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	Key_Init();
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_StructInit(& EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(& EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = EXTI_Line2;
	EXTI_Init(& EXTI_InitStruct);

	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&NVIC_InitStruct);
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
}
void KeyStatue_Trun(void)
{
	KeyStatue = ! KeyStatue;
}
void EXTI0_IRQHandler (void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		exti0_flag = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
	
}
void Process_EXTI0_Event(void)
{
	if(exti0_flag)
    {
        exti0_flag = 0; 
		KeyStatue_Trun();
		if(KeyStatue==0)
	{		
		OLED_ShowString(1,1,"     ");
		OLED_ShowString(1,1,"OFF");
		Delay_ms(50);}
	else{		
		OLED_ShowString(1,1,"     ");
		OLED_ShowString(1,1,"ON");
		while(exti0_flag == 0)
		{
		MPU6050_GetData(Data);
		W25Q64_PageProgram_int16(Address,Data,6);
		Address += sizeof(Data);//注意，该地址是每次按钮按下后的新写入地址，没有进行擦除操作。 
		Delay_ms(10);
		ms += 10;
		OLED_ShowNum(1,5,ms,4);
			
		}
	}
}
}
void EXTI2_IRQHandler (void)
{
	if(EXTI_GetITStatus(EXTI_Line2)==SET)
	{
		exti2_flag = 1;
		
		EXTI_ClearITPendingBit(EXTI_Line2);
	}

}

void Process_EXTI2_Event(void)
{
	if(exti2_flag)
    {
        exti2_flag = 0; 
		ms = 0;//擦除后计时归零
		W25Q64_EraseWhole();
		LED1_ON();
		Delay_s(1);
		LED1_OFF();
}
}
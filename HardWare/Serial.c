#include "stm32f10x.h"                  // Device header
#include <stdio.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;
char Serial_RxPack[100];
void Serial_Init(void)//这一切编程都是针对单片机自身的内外设来的，不需要管电脑端接收、发送啥样
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef LED_t;
	LED_t.GPIO_Mode = GPIO_Mode_AF_PP;
	LED_t.GPIO_Pin = GPIO_Pin_9;//fa
	LED_t.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&LED_t);
	
	
	
	LED_t.GPIO_Mode = GPIO_Mode_IPU;
	LED_t.GPIO_Pin = GPIO_Pin_10;//shou
	LED_t.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&LED_t);
	
	
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate =  9600;
	USART_InitStruct.USART_HardwareFlowControl =  USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode =  USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No ;
	USART_InitStruct.USART_StopBits =  USART_StopBits_2;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b ;  
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
	
	
	
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	
}




void Serial_SendByte(uint16_t Byte)
{
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}


void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}




void Serial_SendString(char *String)
{
	uint16_t i;
	for(i=0;String[i]!='\0';i++)
	{
		Serial_SendByte(String[i]);
	}

}	

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result = 1;
	while(Y--)
	{
		Result*=X;
	}
	return Result;
}

void Serial_SendNum(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for (i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+'0');
	}
	
}

int fputc(int ch ,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

//void Serial_SendPacket(void)
//{
//	Serial_SendByte(0xFF);
//	Serial_SendArray(Serial_TxPack,4);
//	Serial_SendByte(0xFE);
//}


//uint8_t Serial_GetRxFlag(void)
//{
//	if(Serial_RxFlag==1){
//	Serial_RxFlag = 0;
//		return 1;
//	}
//	return 0;
//}

void USART1_IRQHandler(void)
{
	static uint8_t Rxstate = 0;
	static uint8_t pRxPack = 0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		if(Rxstate==0)
		{
			if(RxData =='@'&& Serial_RxFlag ==0)
			{
				Rxstate=1;
				pRxPack=0;
			}
		}
		else if(Rxstate ==1)
		{
			if(RxData=='\r')
			{Rxstate=2;}
			else
				{
					Serial_RxPack[pRxPack] = RxData;
					pRxPack ++;
				}
		}
		else if(Rxstate==2)
		{
			if(RxData=='\n')
			{
			Rxstate=0;
			Serial_RxFlag=1;
			Serial_RxPack[pRxPack] = '\0';
			}
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}

}


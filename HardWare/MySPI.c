#include "stm32f10x.h"                  // Device header

void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}
void MySPI_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
}
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
}
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef LED_t;
	LED_t.GPIO_Mode = GPIO_Mode_Out_PP;
	LED_t.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_7;
	LED_t.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&LED_t);
	LED_t.GPIO_Mode = GPIO_Mode_IPU;
	LED_t.GPIO_Pin = GPIO_Pin_6;
	LED_t.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&LED_t);
	
	MySPI_W_SS(1);
	MySPI_W_SCL(0);
	
	

}
void MySPI_Start()
{
	MySPI_W_SS(0);
}
void MySPI_Stop()
{
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t ByteReceive=0x00;
	uint8_t i;
	for(i=0;i<8;i++)
	{
	MySPI_W_MOSI(!!(ByteSend & (0x80>>i)));
	MySPI_W_SCL(1);
	if(MySPI_R_MISO()==1){ByteReceive |=(0x80>>i); }
	MySPI_W_SCL(0);
	}	
	return ByteReceive;
}






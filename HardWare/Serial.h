#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

extern uint8_t Serial_RxFlag;
extern char Serial_RxPack[];
void Serial_Init(void);

void Serial_SendByte(uint16_t Byte);

void Serial_SendArray(uint8_t *Array,uint16_t Length);


void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t X,uint32_t Y);
void Serial_SendNum(uint32_t Number,uint8_t Length);

void Serial_SendPacket(void);

uint8_t Serial_GetRxFlag(void);

#endif
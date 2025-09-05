#ifndef __MYSPI_H
#define __MYSPI_H
void MySPI_W_SS(uint8_t BitValue);
void MySPI_W_SCL(uint8_t BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
uint8_t MySPI_R_MISO(void);
void MySPI_Init(void);
void MySPI_Start();
void MySPI_Stop();
uint8_t MySPI_SwapByte(uint8_t ByteSend);


#endif
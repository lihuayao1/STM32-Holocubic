#ifndef _USART_H
#define _USART_H
#include "stm32f4xx.h"
#include <stdio.h>

#define PRINTF_BAUD_RATE			115200
#define PROJECTION_BAUD_RATE	460800 * 6 + 230400

void USART1DMA_Init(u8 data[],u16 len);
void printf_Init(u32 baudRate);
#endif

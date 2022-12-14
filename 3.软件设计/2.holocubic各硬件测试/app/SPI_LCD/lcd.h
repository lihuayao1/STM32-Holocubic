#ifndef _SPI_LCD_H
#define _SPI_LCD_H
#include "stm32f4xx.h"
#include "spi.h"
void LCD_Init(void);
void LCD_AddressSet(u16 xStart,u16 xEnd,u16 yStart,u16 yEnd);	//也是开窗函数
void LCD_FullColor(u16 color);
void LCD_DrawPicture(u8 picture[]);
void LCD_DMAWriteFrame(u8* pic1,u8* pic2);	//一帧分为两部分，因为DMA一次最多65535个字节
void LCD_Test(void);
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define RED           	 0xF800
#define GREEN         	 0x07E0
#define BLUE           	 0x001F  
#endif

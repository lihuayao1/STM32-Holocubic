#ifndef _SPI_LCD_H
#define _SPI_LCD_H
#include "stm32f4xx.h"
#include "spi.h"
void LCD_Init(void);
void LCD_AddressSet(u16 xStart,u16 xEnd,u16 yStart,u16 yEnd);	//Ҳ�ǿ�������
void LCD_FullColor(u16 color);
void LCD_DrawPicture(u8 picture[]);
void LCD_DMAWriteFrame(u8* pic1,u8* pic2);	//һ֡��Ϊ�����֣���ΪDMAһ�����65535���ֽ�
void LCD_Test(void);
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define RED           	 0xF800
#define GREEN         	 0x07E0
#define BLUE           	 0x001F  
#endif

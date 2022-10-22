#ifndef _FLASH_H
#define _FLASH_H
#include "stm32f4xx.h"
#include "spi.h"
#define DUMMY 0xFF
#define FLASHID	0xEF16
void FLASH_Init(void);
uint16_t FLASH_ReadID(void);
void FLASH_SectorErase(u8 block,u8 sector);
void FLASH_WriteData(u8 block,u8 sector,const u8 data[],u32 len);	//无限制大小写入，地址为块号和扇区号
void FLASH_ReadData(u8 block,u8 sector,u8 data[],u16 len);
void FLASH_FastRead(u8 block,u8 sector,u8 data[],u16 len);
void FLASH_DMAReadData(u8 block,u8 sector,u8 data[],u16 len);
u8 FLASH_Test(void);
#endif


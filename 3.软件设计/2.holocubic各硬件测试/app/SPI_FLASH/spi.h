#ifndef _SPI_H
#define _SPI_H
#include "stm32f4xx.h"
/*********SPI2（FLASH）*********/
#define SPI2_RCCAHB1	RCC_AHB1Periph_GPIOB
#define SPI2_RCCAPB1	RCC_APB1Periph_SPI2

#define SPI2_Port				GPIOB
#define SPI2_CS_Pin			GPIO_Pin_12
#define SPI2_SCL_Pin		GPIO_Pin_13
#define SPI2_MISO_Pin		GPIO_Pin_14
#define SPI2_MOSI_Pin		GPIO_Pin_15

#define SPI2_SCL_PinSource	GPIO_PinSource13
#define SPI2_MISO_PinSource	GPIO_PinSource14
#define SPI2_MOSI_PinSource	GPIO_PinSource15

#define SPI2_CS_UP		GPIO_SetBits(SPI2_Port,SPI2_CS_Pin)
#define SPI2_CS_DOWN	GPIO_ResetBits(SPI2_Port,SPI2_CS_Pin)

void SPI2_Init(void);
u8 SPI_WriteReadData(u8 data);
void SPI2DMA_Init(u8 data[],u16 len);
/*******************************/






/**********SPI1(LCD)************/
void SPI1Init(void);
void SPI1_WriteCMD(u8 cmd);
void SPI1_Write8Data(u8 data);
void SPI1_Write16Data(u16 data);
#define SPI1_RCCAHB1	RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC
#define SPI1_RCCAPB2	RCC_APB2Periph_SPI1

#define SPI1_Port				GPIOA
#define SPI1_CS_Pin			GPIO_Pin_4
#define SPI1_SCL_Pin		GPIO_Pin_5
//#define SPI2_MISO_Pin		GPIO_Pin_14	无需
#define SPI1_MOSI_Pin		GPIO_Pin_7
#define SPI1_SCL_PinSource	GPIO_PinSource5
//#define SPI2_MISO_PinSource	GPIO_PinSource14无需
#define SPI1_MOSI_PinSource	GPIO_PinSource7


#define LCD_CS_DOWN	GPIO_ResetBits(GPIOA,SPI1_CS_Pin)
#define LCD_CS_UP	GPIO_SetBits(GPIOA,SPI1_CS_Pin)

#define LCD_DC_DOWN	GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define LCD_DC_UP	GPIO_SetBits(GPIOA,GPIO_Pin_6)
//////////////////////////记得打开背光
#define LCD_BLK_OPEN	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define LCD_BLK_CLOSE	GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define LCD_IM_UP			GPIO_SetBits(GPIOC,GPIO_Pin_4)

#define LCD_RST_DOWN	GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define LCD_RST_UP	GPIO_SetBits(GPIOC,GPIO_Pin_5)

void SPI1Init(void);
void SPI1_WriteCMD(u8 cmd);
void SPI1_Write8Data(u8 data);
void SPI1_Write16Data(u16 data);
void SPI1DMA_Init(u8 data[],u16 len);
void suspendPinFSMC(void);	//将FSMC管脚挂起，避免影响SPI1通讯
/*******************************/









#endif

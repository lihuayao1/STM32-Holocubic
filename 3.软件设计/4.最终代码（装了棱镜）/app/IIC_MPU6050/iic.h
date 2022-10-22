#ifndef _IIC_H
#define _IIC_H
#include "stm32f4xx.h"
#include "systick.h"

#define SCL_PORT			GPIOA
#define SCL_Pin				GPIO_Pin_11
#define SCL_UP				GPIO_SetBits(SCL_PORT,SCL_Pin)
#define SCL_DOWN			GPIO_ResetBits(SCL_PORT,SCL_Pin)

#define SDA_PORT			GPIOA
#define SDA_Pin				GPIO_Pin_12
#define SDA_UP				GPIO_SetBits(SDA_PORT,SDA_Pin)
#define SDA_DOWN			GPIO_ResetBits(SDA_PORT,SDA_Pin)

#define IIC_RCC_AHB_PORT	RCC_AHB1Periph_GPIOA

void IIC_PinInit(void);	//IIC管脚初始化
void IIC_WriteDataToIMU(u8 RegAddress,u8 data);								//写入1个字节
void IIC_WriteManyDataToIMU(u8 RegAddress,u16 len,u8 data[]);	//写入多个字节
u8 IIC_ReadDataFromIMU(u8 RegAddress);												//读出1个字节
void IIC_ReadManyDataFromIMU(u8 RegAddress,u16 len,u8 data[]);//读出多个字节
#endif


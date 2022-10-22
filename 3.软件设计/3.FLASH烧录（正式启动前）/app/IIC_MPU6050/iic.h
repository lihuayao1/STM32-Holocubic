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

void IIC_PinInit(void);	//IIC�ܽų�ʼ��
void IIC_WriteDataToIMU(u8 RegAddress,u8 data);								//д��1���ֽ�
void IIC_WriteManyDataToIMU(u8 RegAddress,u16 len,u8 data[]);	//д�����ֽ�
u8 IIC_ReadDataFromIMU(u8 RegAddress);												//����1���ֽ�
void IIC_ReadManyDataFromIMU(u8 RegAddress,u16 len,u8 data[]);//��������ֽ�
#endif


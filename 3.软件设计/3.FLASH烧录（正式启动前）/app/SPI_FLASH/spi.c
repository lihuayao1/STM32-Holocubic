#include "spi.h"
#include "usart.h"
/**************SPI2(FLASH)*************/
void SPI2_Init(void)
{	
	RCC_AHB1PeriphClockCmd(SPI2_RCCAHB1,ENABLE);
	RCC_APB1PeriphClockCmd(SPI2_RCCAPB1,ENABLE);	
	//CS用软件操作，无需配置功能
	GPIO_PinAFConfig(SPI2_Port,SPI2_SCL_PinSource,GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI2_Port,SPI2_MISO_PinSource,GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI2_Port,SPI2_MOSI_PinSource,GPIO_AF_SPI2);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//复用推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//无上下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = SPI2_SCL_Pin;
	GPIO_Init(SPI2_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_Pin;	//复用推挽输出
	GPIO_Init(SPI2_Port,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI2_MISO_Pin;	//不能配置为输入，否则会出bug
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//普通推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = SPI2_CS_Pin;
	GPIO_Init(SPI2_Port,&GPIO_InitStructure);
	
//	SPI2_CS_UP;	//取消片选
	
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	//42/2 = 21M
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
	
}

u8 SPI_WriteReadData(u8 data)
{
	u16 WaitTime = 0;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET)	//发送寄存器非空就循环
	{
		WaitTime++;
		if(WaitTime>10000)
		{
			printf("写一个字节出现异常0\r\n");
		}
	}WaitTime=0;
	SPI_I2S_SendData(SPI2, data);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET)	//接收数据寄存器空就循环
	{
		WaitTime++;
		if(WaitTime>10000)
		{
			printf("写一个字节出现异常1\r\n");
		}
	}WaitTime=0;
	return SPI_I2S_ReceiveData(SPI2);		
}

void SPI2DMA_Init(u8 data[],u16 len)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
	DMA_DeInit(DMA1_Stream3);
	while(DMA_GetCmdStatus(DMA1_Stream3) == ENABLE);	//等待复位完成
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (SPI2_BASE+0x0C);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)data;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = len;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	//只传输一次
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream3,&DMA_InitStructure);

	
	DMA_Cmd(DMA1_Stream3,ENABLE);
	while(DMA_GetCmdStatus(DMA1_Stream3) == DISABLE);	//等待使能完成
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Stream3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

/****************************************/



/***************SPI1(LCD)***************/

void suspendPinFSMC(void)	//将FSMC管脚挂起，避免影响SPI1通讯。也可能不需要
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;	//高阻态
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8
	|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12 |GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8
	|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
	GPIO_SetBits(GPIOE,GPIO_Pin_11| GPIO_Pin_12 |GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}
void SPI1Init()
{
	RCC_AHB1PeriphClockCmd(SPI1_RCCAHB1,ENABLE);	//除了SCL的GPIO时钟外，还有其它控制脚的GPIO时钟
	RCC_APB2PeriphClockCmd(SPI1_RCCAPB2,ENABLE);
	
	GPIO_PinAFConfig(SPI1_Port,SPI1_SCL_PinSource,GPIO_AF_SPI1);	//SCL
	GPIO_PinAFConfig(SPI1_Port,SPI1_MOSI_PinSource,GPIO_AF_SPI1);	//MOSI
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//复用推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = SPI1_SCL_Pin;	//SCL
	GPIO_Init(SPI1_Port,&GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_Pin;	//MOSI
	GPIO_Init(SPI1_Port,&GPIO_InitStructure);
	
	//PC4-IM,PC5-RST,PA4-CS,PA6-DC都用推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	//IM,RST
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_6;	//CS,DC
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//BLK
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	LCD_IM_UP;	LCD_RST_UP;	LCD_DC_UP;	LCD_CS_UP;	
	
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;	//只发送
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);	
}

void SPI1_WriteCMD(u8 cmd)
{
	LCD_CS_DOWN;
	LCD_DC_DOWN;
	
	SPI_I2S_SendData(SPI1,cmd);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==0);
	
	LCD_CS_UP;	
}

void SPI1_Write8Data(u8 data)
{
	LCD_CS_DOWN;
	LCD_DC_UP;
	
	SPI_I2S_SendData(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==0);
	
	LCD_CS_UP;
}

void SPI1_Write16Data(u16 data)
{
	LCD_CS_DOWN;
	LCD_DC_UP;
	
	SPI_I2S_SendData(SPI1, data>>8);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==0);
	SPI_I2S_SendData(SPI1, (data&0x00FF));
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==0);
	
	LCD_CS_UP;
}

void SPI1DMA_Init(u16 data[],u16 len)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	DMA_DeInit(DMA2_Stream3);
	while(DMA_GetCmdStatus(DMA2_Stream3) == ENABLE);
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_Channel = DMA_Channel_3;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (SPI1_BASE+0x0C);
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)data;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = len;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	//只传输一次
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream3,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream3,ENABLE);
	while(DMA_GetCmdStatus(DMA2_Stream3) == DISABLE);	//等待使能完成
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = DMA2_Stream3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

/****************************************/

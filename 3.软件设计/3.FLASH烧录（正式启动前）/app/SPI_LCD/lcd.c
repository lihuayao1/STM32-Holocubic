#include "lcd.h"
#include "systick.h"
#include "picture.h"
#include "gui_guider.h"
void LCD_Init(void)
{
	delay_ms(500);
	SPI1Init();
	suspendPinFSMC();
	LCD_CS_DOWN;
	delay_ms(200);
	LCD_CS_UP;
	delay_ms(200);
	
	SPI1_WriteCMD(0x36);		//��ʾ������Ĭ�Ϸ���
//	SPI1_Write8Data(0x00);
	SPI1_Write8Data(LCD_DIR);
	
	SPI1_WriteCMD(0x3A);		//��ɫ����16λ��RGB565
	SPI1_Write8Data(0x05);

	/*****ϵͳ���ã��������*****/
	SPI1_WriteCMD(0xB2);
	SPI1_Write8Data(0x0C);
	SPI1_Write8Data(0x0C);
	SPI1_Write8Data(0x00);
	SPI1_Write8Data(0x33);
	SPI1_Write8Data(0x33); 
	SPI1_WriteCMD(0xB7); 
	SPI1_Write8Data(0x35);  
	SPI1_WriteCMD(0xBB);
	SPI1_Write8Data(0x37);
	SPI1_WriteCMD(0xC0);
	SPI1_Write8Data(0x2C);
	SPI1_WriteCMD(0xC2);
	SPI1_Write8Data(0x01);
	SPI1_WriteCMD(0xC3);
	SPI1_Write8Data(0x12);   
	SPI1_WriteCMD(0xC4);
	SPI1_Write8Data(0x20);  
	SPI1_WriteCMD(0xC6); 	//119Hz��һ��ɨ119��
	SPI1_Write8Data(0x00);  	
	SPI1_WriteCMD(0xD0); 
	SPI1_Write8Data(0xA4);
	SPI1_Write8Data(0xA1);
	SPI1_WriteCMD(0xE0);
	SPI1_Write8Data(0xD0);
	SPI1_Write8Data(0x04);
	SPI1_Write8Data(0x0D);
	SPI1_Write8Data(0x11);
	SPI1_Write8Data(0x13);
	SPI1_Write8Data(0x2B);
	SPI1_Write8Data(0x3F);
	SPI1_Write8Data(0x54);
	SPI1_Write8Data(0x4C);
	SPI1_Write8Data(0x18);
	SPI1_Write8Data(0x0D);
	SPI1_Write8Data(0x0B);
	SPI1_Write8Data(0x1F);
	SPI1_Write8Data(0x23);
	SPI1_WriteCMD(0xE1);
	SPI1_Write8Data(0xD0);
	SPI1_Write8Data(0x04);
	SPI1_Write8Data(0x0C);
	SPI1_Write8Data(0x11);
	SPI1_Write8Data(0x13);
	SPI1_Write8Data(0x2C);
	SPI1_Write8Data(0x3F);
	SPI1_Write8Data(0x44);
	SPI1_Write8Data(0x51);
	SPI1_Write8Data(0x2F);
	SPI1_Write8Data(0x1F);
	SPI1_Write8Data(0x1F);
	SPI1_Write8Data(0x20);
	SPI1_Write8Data(0x23);
	/***************************/
	
	SPI1_WriteCMD(0x35);	//����tearing efferct
	SPI1_Write8Data(0x00);
	
	
	SPI1_WriteCMD(0x21); 	//������ɫ����
	SPI1_WriteCMD(0x11); 	//�˳�˯��
	SPI1_WriteCMD(0x29); 	//����display
	LCD_BLK_OPEN;					//��������
}

void LCD_Test(void)
{
	LCD_FullColor(BLUE);
	delay_ms(1000);
	LCD_FullColor(RED);
	delay_ms(1000);
}


void LCD_AddressSet(u16 xStart,u16 xEnd,u16 yStart,u16 yEnd)	//Ҳ�ǿ�������
{
	if(LCD_DIR == DIR_UP2DOWN)	//���϶���
	{
		SPI1_WriteCMD(0x2A);	//������
		SPI1_Write16Data(xStart);
		SPI1_Write16Data(xEnd);
		SPI1_WriteCMD(0x2B);	//������
		SPI1_Write16Data(yStart);
		SPI1_Write16Data(yEnd);
		SPI1_WriteCMD(0x2C);	//��ʼ�������
	}
	else	//�ֲ�8.10.2�ɲ����¶��ϵ����з�Χ
	{
		SPI1_WriteCMD(0x2A);	//������
		SPI1_Write16Data(xStart);
		SPI1_Write16Data(xEnd);
		SPI1_WriteCMD(0x2B);	//������
		SPI1_Write16Data(yStart+80);
		SPI1_Write16Data(yEnd+80);
		SPI1_WriteCMD(0x2C);	//��ʼ�������
	}
}

void LCD_FullColor(u16 color)
{
	LCD_AddressSet(0,239,0,239);
	for(u16 i = 0; i < 240; i++)
		for(u16 j = 0; j < 240; j++)
			SPI1_Write16Data(color);
}


void LCD_DrawPicture(u8 picture[])
{
	u32 p = 0;
	LCD_AddressSet(0,239,0,239);
	for(u16 i = 0; i < 240; i++)
		for(u16 j = 0; j < 240; j++)
		{
			SPI1_Write8Data(picture[p++]);
			SPI1_Write8Data(picture[p++]);
		}
}

extern u8 DMA2_COMPLETED;
/*SPI1DMA_Init�Ѹĳɴ���16λ���飬����Ҫ�ú������������޸�*/
//void LCD_DMAWriteFrame(u8* pic1,u8* pic2)	//һ֡��Ϊ�����֣���ΪDMAһ�����65535���ֽ�
//{
//	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,DISABLE);	//�ȹر�,���ⷢ������ʱ����DMA
//	DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,DISABLE);
//	
//	LCD_AddressSet(0,239,0,239);	
//	LCD_DC_UP;
//	LCD_CS_DOWN;	
//	
//	SPI1DMA_Init((u8*)pic1,57600);
//	DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,ENABLE);
//	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
//	while(DMA2_COMPLETED == 0);
//	DMA2_COMPLETED = 0;
//	SPI1DMA_Init((u8*)pic2,57600);
//	DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,ENABLE);
//	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
//	while(DMA2_COMPLETED == 0);
//	DMA2_COMPLETED = 0;
//	
//	LCD_CS_UP;
//}

void LCD_LVGL_ColorFill(u16 xStart,u16 yStart,u16 xEnd,u16 yEnd,u16* color)
{
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,DISABLE);
	DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,DISABLE);
	LCD_AddressSet(xStart,xEnd,yStart,yEnd);	
	LCD_DC_UP;
	LCD_CS_DOWN;	
	SPI1DMA_Init(color,(xEnd-xStart+1)*(yEnd-yStart+1)*2);//16λcolor����8λspi�Ĵ������ʴ�С*2
	DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,ENABLE);
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
	while(DMA2_COMPLETED == 0);
	DMA2_COMPLETED = 0;
	LCD_CS_UP;
	
//	u32 p = 0;
//	LCD_AddressSet(xStart,xEnd,yStart,yEnd);
//	for(u16 i = xStart; i <= xEnd; i++)
//		for(u16 j = yStart; j <= yEnd; j++)
//			SPI1_Write16Data(color[p++]);
}



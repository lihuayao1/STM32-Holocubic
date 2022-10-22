#include "flash.h"
#include "usart.h"
#include "led.h"
#include "init.h"
void FLASH_Init(void)
{
	SPI2_Init();
	while(FLASH_ReadID()!=FLASHID);
}


uint16_t FLASH_ReadID(void)
{
	uint16_t id = 0;
	
	SPI2_CS_DOWN;            //��Ƭѡ
	
	SPI_WriteReadData(0x90);//���Ͷ�ȡID����	    
	SPI_WriteReadData(DUMMY); 	    
	SPI_WriteReadData(DUMMY); 	    
	SPI_WriteReadData(0x00);

	id |= SPI_WriteReadData(DUMMY) << 8; //��ȡ16λID 
	id |= SPI_WriteReadData(DUMMY);
		 
	SPI2_CS_UP;			 //�ر�Ƭѡ   
	return id;		
}
void FLASH_WriteEnable(void)
{
	SPI2_CS_DOWN;
	SPI_WriteReadData(0x06);	//дʹ��
	SPI2_CS_UP;
}

void FLASH_CheckBusy(void)	//���Ĵ���busyλ��ҳд�롢�����������������Ƭ������д״̬�Ĵ�����Ҫ����busyһ��ʱ��
{
	u8 status = 0;	u16 waitTime = 0;

	SPI2_CS_DOWN;
	SPI_WriteReadData(0x05);	//��ȡ�Ĵ���1
	status = SPI_WriteReadData(DUMMY);
	SPI2_CS_UP;
	while((status&0x01)==0x01)
	{
		SPI2_CS_DOWN;
		SPI_WriteReadData(0x05);
		status = SPI_WriteReadData(DUMMY);
		SPI2_CS_UP;
		waitTime++;
		if(waitTime > 0xFFFF)
		{
			printf("wait error\r\n");
			return;
		}
	}
}

//ÿpage��256Byte��ÿsector��16page��4KByte����ÿBlock��16sector��64KByte������128Block(8192KByte)
void FLASH_SectorErase(u8 block,u8 sector)
{
	u32 realAddress = block*65536 + sector*4096;
	
	FLASH_WriteEnable();
	SPI2_CS_DOWN;
	SPI_WriteReadData(0x20);	//��������
	SPI_WriteReadData(realAddress>>16);
	SPI_WriteReadData(realAddress>>8);
	SPI_WriteReadData(realAddress);	
	SPI2_CS_UP;
	FLASH_CheckBusy();
}
static void FLASH_PageWrite(u32 address,u8 data[],u16 len)	//дһҳ�����ڱ��ļ�ʹ��
{
	if(len > 256)
	{
		printf("Write Page Size is too large\r\n");
		return;
	}
	FLASH_WriteEnable();
	SPI2_CS_DOWN;
	SPI_WriteReadData(0x02);	//дҳ����
	SPI_WriteReadData(address>>16);
	SPI_WriteReadData(address>>8);
	SPI_WriteReadData(address);	
	for(u16 i = 0; i <len; i++)
		SPI_WriteReadData(data[i]);
	SPI2_CS_UP;	
	FLASH_CheckBusy();
}

//�ϲ�ֻ���������������
void FLASH_WriteData(u8 block,u8 sector,u8 data[],u32 len)	//�����ƴ�Сд�룬��ַΪ��ź�������
{
	u32 realAddress = block*65536 + sector*4096;
	
	u8 nowBlock = block,nowSector = sector;	//���ڼ�¼��ǰд���ĸ��������������
	
	if(len > 0xFFFFFF)	//����w25q64���Ѱַ
	{
		printf("Buffer Write Size is too large\r\n");
		return;
	}	
	u16 pageNum = len/256,restNum = len%256;	//��д��ҳ���������1ҳҪд�����ֽ�
	for(u16 i = 0; i < pageNum; i++)
	{
		if(i == 0)
			FLASH_SectorErase(nowBlock,nowSector);
		else if(i%16 == 0)
		{
			if(i%256 == 0)	//����һ����
				{
					nowBlock++;
					nowSector = 0;
				}
				else
					nowSector++;
			FLASH_SectorErase(nowBlock,nowSector);
		}
		
		
		FLASH_PageWrite(realAddress,data,256);
		data += 256; realAddress += 256;
	}
	

	if(restNum != 0)	//��ʣ���ֽ�
	{
		if(realAddress % 4096 == 0)	//ʣ���ֽ������������ʱ������������
			FLASH_SectorErase(realAddress/65536,(realAddress-(nowBlock*65536))/4096);		
		for(u16 i = 0; i < restNum; i++)
			FLASH_PageWrite(realAddress,data,restNum);
		realAddress += restNum;	data += restNum;
	}
}




void FLASH_ReadData(u8 block,u8 sector,u8 data[],u16 len)
{
	u32 realAddress = block*65536 + sector*4096;
	SPI2_CS_DOWN;
	SPI_WriteReadData(0x03);	//������
	SPI_WriteReadData(realAddress>>16);
	SPI_WriteReadData(realAddress>>8);
	SPI_WriteReadData(realAddress);	
	for(u16 i = 0; i < len; i++)
		data[i] = SPI_WriteReadData(DUMMY);
	SPI2_CS_UP;
}

void FLASH_FastRead(u8 block,u8 sector,u8 data[],u16 len)
{
	u32 realAddress = block*65536 + sector*4096;
	SPI2_CS_DOWN;
	SPI_WriteReadData(0x0B);	//���ٶ�
	SPI_WriteReadData(realAddress>>16);
	SPI_WriteReadData(realAddress>>8);
	SPI_WriteReadData(realAddress);	
	SPI_WriteReadData(DUMMY);	
	for(u16 i = 0; i < len; i++)
		data[i] = SPI_WriteReadData(DUMMY);
	SPI2_CS_UP;
}

void FLASH_DMAReadData(u8 block,u8 sector,u8 data[],u16 len)
{
	u32 realAddress = block*65536 + sector*4096;
	
	SPI_DeInit(SPI2);
	SPI2DMA_Init(data,len);	//ÿ����������DMA֮ǰ�����SPIʱ�ӹص�����������©һ���ֽڵ�bug
	SPI2_Init();
	
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx,DISABLE);	//����д���ַʱ���ӻ�����DUMMY������DMA
	DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,DISABLE);
	
	SPI2_CS_DOWN;
	SPI_WriteReadData(0x03);	//������
	SPI_WriteReadData(realAddress>>16);
	SPI_WriteReadData(realAddress>>8);
	SPI_WriteReadData(realAddress);	
	SPI2->CR1 |= (1 << 10);	//�ر�ȫ˫�������跢DUMMY���ɻ�ȡ���ݣ�����DMA����
	
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx,ENABLE);	//һ���������ݼĴ����ǿգ���������
	DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,ENABLE);

}

//#define SIZE 4096*15
//u8 readData[SIZE] = {0};
//u8 writeData[SIZE] = {0};
//extern u8 DMA1_COMPLETED;

u8 FLASH_Test(void)	//���øú������ƻ�FLASH�д�õ�ͼƬ���ݣ�����ע�͵����Ǳ�Ҫ������
{
//	/************����ID*************/
//	u8 waitTime = 0;
//	while(FLASH_ReadID()!=FLASHID)
//		if(waitTime++ > 200)
//			return 0;
//	/******************************/
//	
//	/**********����д�����ȡ********/
//	for(u16 i = 0; i < SIZE; i++)
//		writeData[i] = 3;
//	FLASH_WriteData(0,0,writeData,SIZE);
//	for(u16 i = 0; i < SIZE; i++)
//		writeData[i] = 4;
//	FLASH_WriteData(0,15,writeData,SIZE);
//	
//	
//	FLASH_DMAReadData(0,0,readData,SIZE);
//	while(DMA1_COMPLETED==0);	DMA1_COMPLETED = 0;
//	for(u32 i = 0; i < SIZE; i++)
//		if(readData[i] != 3)
//			return 0;
//		
//	FLASH_DMAReadData(0,15,readData,SIZE);		
//	while(DMA1_COMPLETED==0);	DMA1_COMPLETED = 0;
//	for(u32 i = 0; i < SIZE; i++)
//		if(readData[i] != 4)
//			return 0;
//	/******************************/
	return 1;
}

CityWifiInfo_t FLASH_ReadCityWifi(void)
{
	CityWifiInfo_t temp;
	u8 Info[3];
	char readWifiName[200] = {0};
	char readWifiPassWord[200] = {0};
	char cityNameArrPinYin[][10] = {"shenzhen","zhanjiang","guangzhou","ganzhou","nanchang","beijing","shanghai"}; 
	FLASH_ReadData(45,0,Info,3);
	FLASH_ReadData(45,1,(u8*)readWifiName,Info[1]);
	FLASH_ReadData(45,2,(u8*)readWifiPassWord,Info[2]);
	
	/****************��ֵ�ṹ��***************/
	temp.cityNum = Info[0];
	strcpy(temp.cityName,cityNameArrPinYin[temp.cityNum]);
	strcpy(temp.wifiName,readWifiName);
	strcpy(temp.wifiPassword,readWifiPassWord);
	/****************************************/
	
	return temp;
}

u8 sectorReadData[4096];//�ź����ڹ��󣬹ʿ�ȫ��
u8 FLASH_CheckSectorData(u8 block,u8 sector,u8 writeData[],u32 len)
{
	FLASH_FastRead(block,sector,sectorReadData,len);
	for(int i = 0; i < len; i++)
		if(writeData[i] != sectorReadData[i])
			return 0;
	return 1;

}

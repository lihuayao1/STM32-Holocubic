#include "iic.h"
#include "mpu6050.h"
#include "led.h"

void IIC_PinInit(void)	
{
	RCC_AHB1PeriphClockCmd(IIC_RCC_AHB_PORT,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = SCL_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SCL_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SDA_Pin;
	GPIO_Init(SDA_PORT,&GPIO_InitStruct);
	SDA_UP;SCL_UP;
}

void IIC_Start(void)
{
	SDA_UP;
	SCL_UP;
	delay_us(1);	//tSU:STA
	SDA_DOWN;
	delay_us(1);		//tHD:STA
	SCL_DOWN;
	//一进入write或read数据函数就延时2us，此处不延时
}

void IIC_Stop(void)
{
	delay_us(2);	//进入该函数前，已置SCL_DOWN，但未延时
	SDA_DOWN;
	SCL_UP;
	delay_us(1);	//tSU:STO
	SDA_UP;
	delay_us(2);	//tBUF
}

void IIC_ACK(void)
{
	SCL_DOWN;
	delay_us(2);	//SCL为low最低延时1.3us。此处已延时，读完8位数据无需延时
	SDA_DOWN;
	delay_us(1);
	SCL_UP;
	delay_us(1);
	SCL_DOWN;
	SDA_UP;	//一定要释放总线，否则会出bug
	//read数据前延时了一会，此处可以不延时，若应答后跟stop函数，stop函数前方已写好延时
}

void IIC_NOACK(void)
{
	SCL_DOWN;
	delay_us(2);
	SDA_UP;
	delay_us(1);
	SCL_UP;
	delay_us(1);
	SCL_DOWN;
}

void IIC_WaitACK(void)
{
	u8 waitTime = 0;
	//write数据完，最后要延时一会，此处不延时
	SDA_UP;	//拉高SDA，等待从机拉低
	SCL_UP;
	while(GPIO_ReadInputDataBit(SDA_PORT,SDA_Pin))
	{
		waitTime++;
		if(waitTime > 200)
		{
			LED_ON();	//异常则点灯
			IIC_Stop();
			return;
		}
	}
	SCL_DOWN;
	return;
}

void IIC_WriteByte(u8 data)
{
	for(u8 i = 0; i < 8;i++)	//高位先行
	{
		SCL_DOWN;
		delay_us(2);
		if(data&0x80)
			SDA_UP;
		else
			SDA_DOWN;
		data = data << 1;
		SCL_UP;
		delay_us(1);
	}
	SCL_DOWN;
	delay_us(2);	//用于等待应答
}

u8 IIC_ReadByte(void)
{
	u8 data = 0;
	for(u8 i = 0;i < 8; i++)
	{
		SCL_DOWN;
		delay_us(2);
		SCL_UP;
		delay_us(1);
		data = data << 1;
		if(GPIO_ReadInputDataBit(SDA_PORT,SDA_Pin))
			data |= 0x01;
	}
	SCL_DOWN;
	return data;
}

void IIC_WriteDataToIMU(u8 RegAddress,u8 data)
{
	IIC_Start();
	IIC_WriteByte(MPU6050_ADDRESS << 1);
	IIC_WaitACK();
	IIC_WriteByte(RegAddress);
	IIC_WaitACK();
	IIC_WriteByte(data);
	IIC_WaitACK();
	IIC_Stop();
}

void IIC_WriteManyDataToIMU(u8 RegAddress,u16 len,u8 data[])
{
	IIC_Start();
	IIC_WriteByte(MPU6050_ADDRESS << 1);
	IIC_WaitACK();
	IIC_WriteByte(RegAddress);
	IIC_WaitACK();
	for(u16 i = 0; i < len; i++)
	{
		IIC_WriteByte(data[i]);
		IIC_WaitACK();
	}
	IIC_Stop();
}

u8 IIC_ReadDataFromIMU(u8 RegAddress)
{
	u8 data = 0;
	IIC_Start();
	IIC_WriteByte(MPU6050_ADDRESS << 1);
	IIC_WaitACK();
	
	IIC_WriteByte(RegAddress);
	IIC_WaitACK();
	
	IIC_Start();
	IIC_WriteByte((MPU6050_ADDRESS << 1)|0x01);
	IIC_WaitACK();
	
	data = IIC_ReadByte();
	IIC_NOACK();
	IIC_Stop();
	return data;
}


void IIC_ReadManyDataFromIMU(u8 RegAddress,u16 len,u8 data[])
{
	IIC_Start();
	IIC_WriteByte(MPU6050_ADDRESS << 1);
	IIC_WaitACK();
	
	IIC_WriteByte(RegAddress);
	IIC_WaitACK();
	
	IIC_Start();
	IIC_WriteByte((MPU6050_ADDRESS << 1)|0x01);
	IIC_WaitACK();
	
	for(u16 i = 0; i < len - 1; i++)
	{
		data[i] = IIC_ReadByte();
		IIC_ACK();
	}
	data[len - 1] = IIC_ReadByte();
	IIC_NOACK();
	IIC_Stop();
}






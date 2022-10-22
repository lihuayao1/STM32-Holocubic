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
	//һ����write��read���ݺ�������ʱ2us���˴�����ʱ
}

void IIC_Stop(void)
{
	delay_us(2);	//����ú���ǰ������SCL_DOWN����δ��ʱ
	SDA_DOWN;
	SCL_UP;
	delay_us(1);	//tSU:STO
	SDA_UP;
	delay_us(2);	//tBUF
}

void IIC_ACK(void)
{
	SCL_DOWN;
	delay_us(2);	//SCLΪlow�����ʱ1.3us���˴�����ʱ������8λ����������ʱ
	SDA_DOWN;
	delay_us(1);
	SCL_UP;
	delay_us(1);
	SCL_DOWN;
	SDA_UP;	//һ��Ҫ�ͷ����ߣ�������bug
	//read����ǰ��ʱ��һ�ᣬ�˴����Բ���ʱ����Ӧ����stop������stop����ǰ����д����ʱ
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
	//write�����꣬���Ҫ��ʱһ�ᣬ�˴�����ʱ
	SDA_UP;	//����SDA���ȴ��ӻ�����
	SCL_UP;
	while(GPIO_ReadInputDataBit(SDA_PORT,SDA_Pin))
	{
		waitTime++;
		if(waitTime > 200)
		{
			LED_ON();	//�쳣����
			IIC_Stop();
			return;
		}
	}
	SCL_DOWN;
	return;
}

void IIC_WriteByte(u8 data)
{
	for(u8 i = 0; i < 8;i++)	//��λ����
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
	delay_us(2);	//���ڵȴ�Ӧ��
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






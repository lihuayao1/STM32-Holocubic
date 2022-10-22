#include "mpu6050.h"
#include "iic.h"
#include "usart.h"
void MPU6050_Init(void)
{
	//delay_ms(500);
	IIC_PinInit();
	MPU6050_InterruptInit();
	//bit7=1时复位,bit6=1时睡眠,bit5=1时循环睡眠和唤醒,bit3=1时使能温度传感器,bit2~0选择时钟
	IIC_WriteDataToIMU(MPU6050_RA_PWR_MGMT_1, 0x00);	//取消睡眠
	//输出频率分频可得采样率。输出频率为8k,bit7~0取值为a，陀螺仪采样率 = 8k/(1+a)
	IIC_WriteDataToIMU(MPU6050_RA_SMPLRT_DIV , 0x07);	    //陀螺仪采样率，1KHz
	//等于0x00或0x07时，陀螺仪输出频率8K，其它时候1K
	IIC_WriteDataToIMU(MPU6050_RA_CONFIG , 0x06);	        //低通滤波器的设置
	//IIC_WriteDataToIMU(MPU6050_RA_CONFIG , 0x00);	//不确定给0x00还是0x06，野火的示例代码给的是0x06
	//bit7~bit5为1时使能自检，bit4~bit3用于设置陀螺仪范围
	IIC_WriteDataToIMU(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	//bit7~bit5为1时使能自检，bit4~bit3用于设置加速度计范围
	IIC_WriteDataToIMU(MPU6050_RA_ACCEL_CONFIG , 0x00);	  //配置加速度传感器工作在2G模式，不自检
}


void MPU6050_InterruptInit(void)	//MPU6050中断初始化
{
	RCC_AHB1PeriphClockCmd(MPU6050_RCC_AHB_PORT,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//类似F1系列的AFIO时钟
	
	GPIO_InitTypeDef GPIO_InitStruct; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;	//下拉输入
	GPIO_InitStruct.GPIO_Pin = MPU6050_INT_PIN;
	GPIO_Init(MPU6050_INT_PORT,&GPIO_InitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = MPU6050_INT_IRQCHANNEL;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	SYSCFG_EXTILineConfig(MPU6050_INT_SOURCE_PORT,MPU6050_INT_SOURCE_PIN);	//类似F1的GPIO_EXTILineConfig
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = MPU6050_INT_EXTILINE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}


u8 MPU6050_GetAddress(void)
{
	u8 data[1];
	IIC_ReadDataFromIMU(MPU6050_RA_WHO_AM_I,1,data);
	return data[0];
}

void MPU6050_ReadAcc(short accData[])	//读取加速度计
{
	u8 buf[6];
	IIC_ReadDataFromIMU(MPU6050_RA_ACCEL_XOUT_H,6,buf);	//读取到的16位数据其实是有符号数，故存入short型数组
	accData[0] = (buf[0] << 8) | buf[1];
	accData[1] = (buf[2] << 8) | buf[3];
	accData[2] = (buf[4] << 8) | buf[5];
}
void MPU6050_ReadGyro(short gyroData[])	//读取陀螺仪
{
    u8 buf[6];
    IIC_ReadDataFromIMU(MPU6050_RA_GYRO_XOUT_H,6,buf);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}
float MPU6050_ReadTemp()	//读取温度并转换为实际值
{
	short data;	//data必须是short型，因为此处的data可能有负号
	u8 buf[2];
	
	IIC_ReadDataFromIMU(MPU6050_RA_TEMP_OUT_H,2,buf);     //读取温度值
  data= (buf[0] << 8) | buf[1];	
	//return(((float)  data/340.0)+36.53);
	float temp=((double) data/340.0)+36.53;
	return temp;
}

void MPU6050_PrintData(void)	//打印采样数据
{
	short accData[3],gyroData[3];	//此处不能用u16，因为该数据是有符号数
	float temp;
	MPU6050_ReadAcc(accData);
	MPU6050_ReadGyro(gyroData);
	temp = MPU6050_ReadTemp();
	printf("加速度: x:%8d y:%8d z:%8d \r\n",accData[0],accData[1],accData[2]);
	printf("陀螺仪: x:%8d y:%8d z:%8d \r\n",gyroData[0],gyroData[1],gyroData[2]);
	printf("温度: %.2f\r\n",temp);
	printf("\r\n");
}

u8 MPU6050_Test(void)
{
	/***地址测试***/
	u8 waitTime = 0;
	while(MPU6050_GetAddress()!=MPU6050_ADDRESS)
		if(waitTime++ > 200)
			return 0;
	return 1;
	/*************/
}


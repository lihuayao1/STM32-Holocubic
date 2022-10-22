#include "mpu6050.h"
#include "iic.h"
#include "usart.h"
#include "lvgl.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "math.h"
#include "holocubic_function.h"
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
	IIC_ReadManyDataFromIMU(MPU6050_RA_WHO_AM_I,1,data);
	return data[0];
}

void MPU6050_ReadAcc(short accData[])	//读取加速度计
{
	u8 buf[6];
	IIC_ReadManyDataFromIMU(MPU6050_RA_ACCEL_XOUT_H,6,buf);	//读取到的16位数据其实是有符号数，故存入short型数组
	accData[0] = (buf[0] << 8) | buf[1];
	accData[1] = (buf[2] << 8) | buf[3];
	accData[2] = (buf[4] << 8) | buf[5];
}
void MPU6050_ReadGyro(short gyroData[])	//读取陀螺仪
{
    u8 buf[6];
    IIC_ReadManyDataFromIMU(MPU6050_RA_GYRO_XOUT_H,6,buf);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}
float MPU6050_ReadTemp()	//读取温度并转换为实际值
{
	short data;	//data必须是short型，因为此处的data可能有负号
	u8 buf[2];
	
	IIC_ReadManyDataFromIMU(MPU6050_RA_TEMP_OUT_H,2,buf);     //读取温度值
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
	printf("Acce: x:%8d y:%8d z:%8d \r\n",accData[0],accData[1],accData[2]);
	printf("Gyro: x:%8d y:%8d z:%8d \r\n",gyroData[0],gyroData[1],gyroData[2]);
	printf("Temp: %.2f\r\n",temp);
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



float Pitch = 0,Roll = 0,Yaw = 0;
extern u32 msTicks;
u8 functionNum = 1;
u8 isAttitudeRecoveried = 1;
u32 lastMsTicks = 0;
extern int32_t encoder_diff;
extern lv_indev_state_t encoder_state;
extern u8 nowIsDeskop;
extern u8 nowIsSelectFunction;
extern lv_ui_deskop lv_gui_deskop;
extern lv_ui_selectFunction lv_gui_selectFunction;
extern float initPitch,initRoll,initYaw;
void MPU6050_Task(void)	//姿态检测任务
{
	//msTicks溢出后从0开始，相减会为负数。但无影响，例如，无符号数10 - 4294967185(32位全1减10) = 21，多了1也影响不大
	//C语言存储负数：最高位为1，其余位取反再加一。如-1: 10000001除高位取反后为11111110，再加1为11111111，故全1为-1的存储形式
	if(msTicks - lastMsTicks >= MPU6050_TASK_TIME)	
	{
		MPU6050_DMP_Task();
		lastMsTicks = msTicks;
		
		if((Pitch - initPitch) > MPU6050_TURN_ANGLE && isAttitudeRecoveried)
		{
			printf("DOWN!\r\n");	isAttitudeRecoveried = 0;
			if(nowIsSelectFunction == 1)
			{
				printf("Exit select function");
				nowIsSelectFunction = 0;
				nowIsDeskop = 1;
				functionNum = 1;
				setup_ui_deskop(&lv_gui_deskop);
			}
		}		
		else if((Pitch - initPitch) < -MPU6050_TURN_ANGLE && isAttitudeRecoveried)
		{
			printf("UP!\r\n");	isAttitudeRecoveried = 0;
			if(nowIsDeskop == 1)
			{
				nowIsDeskop = 0;
				nowIsSelectFunction = 1;
				setup_ui_selectFunction(&lv_gui_selectFunction);
				functionNum = 1;
			}
			else if(nowIsSelectFunction == 1)
			{
				printf("Enter APP:%d",functionNum);
				nowIsSelectFunction = 0;
				if(functionNum == 1)
					clockFunction();
				else if(functionNum == 2)
					pictureFunction();
				else if(functionNum == 3)
					projectionFunction();
				else if(functionNum == 4)
					setFunction();
			}
		}			
		else if((Roll - initRoll) > MPU6050_TURN_ANGLE && isAttitudeRecoveried)	
		{
			printf("RIGHT!\r\n");	isAttitudeRecoveried = 0;
			if(nowIsSelectFunction == 1)
			{
				functionNum++;
				if(functionNum == 2)
					lv_obj_scroll_to_view(lv_gui_selectFunction.selectFunction_picture_pattern,LV_ANIM_ON);
				else if(functionNum == 3)
					lv_obj_scroll_to_view(lv_gui_selectFunction.selectFunction_projection_pattern,LV_ANIM_ON);
				else if(functionNum == 4)
					lv_obj_scroll_to_view(lv_gui_selectFunction.selectFunction_set_pattern,LV_ANIM_ON);
				else
					functionNum = 4;
			}
		}
		else if((Roll - initRoll) < -MPU6050_TURN_ANGLE && isAttitudeRecoveried)	
		{
			printf("LEFT!\r\n");	isAttitudeRecoveried = 0;
			if(nowIsSelectFunction == 1)
			{
				functionNum--;
				if(functionNum == 1)
					lv_obj_scroll_to_view(lv_gui_selectFunction.selectFunction_clock_pattern,LV_ANIM_ON);
				else if(functionNum == 2)
					lv_obj_scroll_to_view(lv_gui_selectFunction.selectFunction_picture_pattern,LV_ANIM_ON);
				else if(functionNum == 3)
					lv_obj_scroll_to_view(lv_gui_selectFunction.selectFunction_projection_pattern,LV_ANIM_ON);
				else
					functionNum = 1;
			}		
		}
		else if( (fabs(initPitch - Pitch) < MPU6050_RETURN_ANGLE) && (fabs(initRoll - Roll) < MPU6050_RETURN_ANGLE))
			isAttitudeRecoveried = 1;
//		printf("isRecoveried = %d\r\n",isAttitudeRecoveried);
	}
	
		
}

void MPU6050_GetInitAttitude(void)
{
	while(initPitch==0)
	{
		MPU6050_DMP_Task();
		initPitch = Pitch;
		initRoll = Roll;
		initYaw = Yaw;
	}
	
}




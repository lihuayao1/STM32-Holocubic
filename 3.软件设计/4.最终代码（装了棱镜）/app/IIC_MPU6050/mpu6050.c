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
	//bit7=1ʱ��λ,bit6=1ʱ˯��,bit5=1ʱѭ��˯�ߺͻ���,bit3=1ʱʹ���¶ȴ�����,bit2~0ѡ��ʱ��
	IIC_WriteDataToIMU(MPU6050_RA_PWR_MGMT_1, 0x00);	//ȡ��˯��
	//���Ƶ�ʷ�Ƶ�ɵò����ʡ����Ƶ��Ϊ8k,bit7~0ȡֵΪa�������ǲ����� = 8k/(1+a)
	IIC_WriteDataToIMU(MPU6050_RA_SMPLRT_DIV , 0x07);	    //�����ǲ����ʣ�1KHz
	//����0x00��0x07ʱ�����������Ƶ��8K������ʱ��1K
	IIC_WriteDataToIMU(MPU6050_RA_CONFIG , 0x06);	        //��ͨ�˲���������
	//IIC_WriteDataToIMU(MPU6050_RA_CONFIG , 0x00);	//��ȷ����0x00����0x06��Ұ���ʾ�����������0x06
	//bit7~bit5Ϊ1ʱʹ���Լ죬bit4~bit3�������������Ƿ�Χ
	IIC_WriteDataToIMU(MPU6050_RA_GYRO_CONFIG, 0x18);     //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	//bit7~bit5Ϊ1ʱʹ���Լ죬bit4~bit3�������ü��ٶȼƷ�Χ
	IIC_WriteDataToIMU(MPU6050_RA_ACCEL_CONFIG , 0x00);	  //���ü��ٶȴ�����������2Gģʽ�����Լ�
}


void MPU6050_InterruptInit(void)	//MPU6050�жϳ�ʼ��
{
	RCC_AHB1PeriphClockCmd(MPU6050_RCC_AHB_PORT,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//����F1ϵ�е�AFIOʱ��
	
	GPIO_InitTypeDef GPIO_InitStruct; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;	//��������
	GPIO_InitStruct.GPIO_Pin = MPU6050_INT_PIN;
	GPIO_Init(MPU6050_INT_PORT,&GPIO_InitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = MPU6050_INT_IRQCHANNEL;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	SYSCFG_EXTILineConfig(MPU6050_INT_SOURCE_PORT,MPU6050_INT_SOURCE_PIN);	//����F1��GPIO_EXTILineConfig
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

void MPU6050_ReadAcc(short accData[])	//��ȡ���ٶȼ�
{
	u8 buf[6];
	IIC_ReadManyDataFromIMU(MPU6050_RA_ACCEL_XOUT_H,6,buf);	//��ȡ����16λ������ʵ���з��������ʴ���short������
	accData[0] = (buf[0] << 8) | buf[1];
	accData[1] = (buf[2] << 8) | buf[3];
	accData[2] = (buf[4] << 8) | buf[5];
}
void MPU6050_ReadGyro(short gyroData[])	//��ȡ������
{
    u8 buf[6];
    IIC_ReadManyDataFromIMU(MPU6050_RA_GYRO_XOUT_H,6,buf);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}
float MPU6050_ReadTemp()	//��ȡ�¶Ȳ�ת��Ϊʵ��ֵ
{
	short data;	//data������short�ͣ���Ϊ�˴���data�����и���
	u8 buf[2];
	
	IIC_ReadManyDataFromIMU(MPU6050_RA_TEMP_OUT_H,2,buf);     //��ȡ�¶�ֵ
  data= (buf[0] << 8) | buf[1];	
	//return(((float)  data/340.0)+36.53);
	float temp=((double) data/340.0)+36.53;
	return temp;
}

void MPU6050_PrintData(void)	//��ӡ��������
{
	short accData[3],gyroData[3];	//�˴�������u16����Ϊ���������з�����
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
	/***��ַ����***/
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
void MPU6050_Task(void)	//��̬�������
{
	//msTicks������0��ʼ�������Ϊ����������Ӱ�죬���磬�޷�����10 - 4294967185(32λȫ1��10) = 21������1ҲӰ�첻��
	//C���Դ洢���������λΪ1������λȡ���ټ�һ����-1: 10000001����λȡ����Ϊ11111110���ټ�1Ϊ11111111����ȫ1Ϊ-1�Ĵ洢��ʽ
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




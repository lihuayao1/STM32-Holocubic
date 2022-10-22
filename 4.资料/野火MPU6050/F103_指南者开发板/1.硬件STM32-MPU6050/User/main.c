/**
  ******************************************************************************
  * @file    main.c
  * @author  LYC
  * @version V1.0
  * @date    2014-04-22
  * @brief   MPU6050 Ӳ��IIC����
  ******************************************************************************
  * @attention
  * ʵ��ƽ̨:Ұ�� ָ���� STM32 ������ 
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "./systick/bsp_SysTick.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./mpu6050/mpu6050.h"
#include "./i2c/bsp_i2c.h"


/* MPU6050���� */
short Acel[3];
short Gyro[3];
float Temp;

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	/* ����ͨ�ų�ʼ�� */
	USART_Config();

	//I2C��ʼ��
	I2C_Bus_Init();
	//MPU6050��ʼ��
	MPU6050_Init();
//���MPU6050
	if( MPU6050ReadID() == 0 )
	{
		printf("\r\nû�м�⵽MPU6050��������\r\n");
		LED_RED;
		while(1);	//��ⲻ��MPU6050 ������Ȼ����
	}
	
  /* ����SysTick��ʱ�����ж� */
  SysTick_Init(); //���� SysTick Ϊ 1ms �ж�һ�Σ����ж����ȡ����������
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //������ʱ��
  
  
  while(1)
  {
    if( task_readdata_finish ) //task_readdata_finish = 1 ��ʾ��ȡMPU6050�������
    {
      
      printf("���ٶȣ�%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
      
      printf("    ������%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
      
      printf("    �¶�%8.2f\r\n",Temp);
      
      task_readdata_finish = 0; // �����־λ
      
    }
  }
  
}
/*********************************************END OF FILE**********************/

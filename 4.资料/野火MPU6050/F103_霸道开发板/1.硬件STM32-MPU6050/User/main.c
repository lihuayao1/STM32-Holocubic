/**
  ******************************************************************************
  * @file    main.c
  * @author  LYC
  * @version V1.0
  * @date    2014-04-22
  * @brief   MPU6050 硬件IIC测试
  ******************************************************************************
  * @attention
  * 实验平台:野火 霸道 STM32 开发板 
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "./systick/bsp_SysTick.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./mpu6050/mpu6050.h"
#include "./i2c/bsp_i2c.h"


/* MPU6050数据 */
short Acel[3];
short Gyro[3];
float Temp;

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	/* LED 端口初始化 */
	LED_GPIO_Config();
	/* 串口通信初始化 */
	USART_Config();

	//I2C初始化
	I2C_Bus_Init();
	//MPU6050初始化
	MPU6050_Init();
  //检测MPU6050
	if( MPU6050ReadID() == 0 )
	{
		printf("\r\n没有检测到MPU6050传感器！\r\n");
		LED_RED;
		while(1);	//检测不到MPU6050 会红灯亮然后卡死
	}
	
  /* 配置SysTick定时器和中断 */
  SysTick_Init(); //配置 SysTick 为 1ms 中断一次，在中断里读取传感器数据
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //启动定时器
  
  
  while(1)
  {
    if( task_readdata_finish ) //task_readdata_finish = 1 表示读取MPU6050数据完成
    {
      
      printf("加速度：%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
      
      printf("    陀螺仪%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
      
      printf("    温度%8.2f\r\n",Temp);
      
      task_readdata_finish = 0; // 清零标志位
      
    }
  }
  
}
/*********************************************END OF FILE**********************/

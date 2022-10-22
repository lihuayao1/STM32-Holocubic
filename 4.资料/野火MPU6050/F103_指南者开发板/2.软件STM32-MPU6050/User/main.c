/**
  ******************************************************************************
  * @file    main.c
  * @author  LYC
  * @version V1.0
  * @date    2014-04-22
  * @brief   MPU6050 ���IIC����
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


//�����Ƿ�ʹ��LCD������ʾ������Ҫ�Ļ��������ע�͵�����
#define USE_LCD_DISPLAY

#ifdef USE_LCD_DISPLAY
 #include "./lcd/bsp_ili9341_lcd.h"
#endif


/* MPU6050���� */
short Accel[3];
short Gyro[3];
float Temp;


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{

#ifdef USE_LCD_DISPLAY
  char cStr [ 70 ];
  
	ILI9341_Init ();         //LCD ��ʼ��
  ILI9341_GramScan ( 6 );
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);
	
	ILI9341_Clear ( 0, 0, 240, 320);	
  ILI9341_DispString_EN ( 20, 20, "This is a MPU6050 demo" );
#endif
  
  //��ʼ��systick
	SysTick_Init();
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	/* ����1ͨ�ų�ʼ�� */
	USART_Config();

	//I2C��ʼ��
	i2c_GPIO_Config();
  //MPU6050��ʼ��
	MPU6050_Init();
  if (MPU6050ReadID() == 0)
  {
    printf("\r\nû�м�⵽MPU6050��������\r\n");
    LED_RED; 
    #ifdef USE_LCD_DISPLAY			
      /*����������ɫ������ı�����ɫ*/
      LCD_SetColors(BLUE,BLACK);	
      ILI9341_DispStringLine_EN(LINE(4),"No MPU6050 detected! ");			
      ILI9341_DispStringLine_EN(LINE(5),"Please check the hardware connection! ");		
    #endif
		while(1);	
	}
	
	printf("\r\n ��ӭʹ��Ұ��  STM32 �����塣\r\n");		 
	printf("\r\n ����һ��MPU6050�������� \r\n");

  
  /* ����SysTick��ʱ�����ж� */
  SysTick_Init(); //���� SysTick Ϊ 1ms �ж�һ�Σ����ж����ȡ����������
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //������ʱ��
  
  
  while(1)
  {
    if( task_readdata_finish ) //task_readdata_finish = 1 ��ʾ��ȡMPU6050�������
    {
    
      printf("\r\n���ٶȣ� %8d%8d%8d    ",Accel[0],Accel[1],Accel[2]);
      printf("�����ǣ� %8d%8d%8d    ",Gyro[0],Gyro[1],Gyro[2]);
      printf("�¶ȣ� %8.2f",Temp);
      
      #ifdef USE_LCD_DISPLAY	
      ILI9341_DispStringLine_EN(LINE(7),"Acceleration");		
      sprintf ( cStr, "%8d%8d%8d",Accel[0],Accel[1],Accel[2] );	//���ٶ�ԭʼ����
      ILI9341_DispStringLine_EN(LINE(8),cStr);					

      ILI9341_DispStringLine_EN(LINE(11),"Gyro        :");			
      sprintf ( cStr, "%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2] );	//��ԭʼ����
      ILI9341_DispStringLine_EN(LINE(12),cStr);	

      sprintf ( cStr, "Temperture  :%8.2f",Temp );	//�¶�ֵ
      ILI9341_DispStringLine_EN(LINE(15),cStr);			
      #endif
      
      task_readdata_finish = 0; // �����־λ
    }
	}
  
}

/*********************************************END OF FILE**********************/

#include "led.h"
#include "usart.h"
#include "systick.h"
#include "flash.h"
#include "tim.h"
#include "mpu6050.h"
#include "lcd.h"
#include "esp8266.h"
//u8 data1[30000] __attribute__((section("ccmram")));	//额外64kb


extern u32 msTicks;	u32 t1,t2;
extern u8 DMA1_COMPLETED;
int main()
{
	delay_ms(1000);
	printf_Init();
	LED_Init();
	RGB_Init();
	FLASH_Init();
	tickTIM_Init();
	MPU6050_Init();
	ESP8266_Init();
	LCD_Init();
	
//	if(!FLASH_Test())	printf("FLASH TEST ERROR!\r\n");
//	else	printf("FLASH TEST OK!\r\n");
	
	if(!MPU6050_Test())	printf("MPU6050 TEST ERROR!\r\n");
	else	printf("MPU6050 TEST OK!\r\n");

	if(!ESP8266_Test())	printf("ESP8266 TEST ERROR!\r\n");
	else printf("ESP8266 TEST OK!\r\n");
	
	printf("请检查显示屏以及RGB灯是否正在变色！\r\n");
	
	while(1)
	{
		RGB_Test();
		LCD_Test();
	}
	
}

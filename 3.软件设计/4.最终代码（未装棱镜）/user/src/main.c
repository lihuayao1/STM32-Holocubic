#include "init.h"
u8 nowIsDeskop = 1;
u8 nowIsSelectFunction = 0;

int main()
{

	holocubic_init();
	while(1)
	{
		lv_task_handler();
		MPU6050_Task();
		if(nowIsDeskop == 1)
		{
			ESP8266_Task();
			LCD_DeskopGifTask();
			clockRuningTask();
		}
		
	}
}

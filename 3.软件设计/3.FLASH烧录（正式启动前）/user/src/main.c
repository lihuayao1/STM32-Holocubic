/*****************************************
介绍：本代码用于烧录外部flash，将桌面GIF以及天气图像存入其中

使用方法：每次保留一个注释，编译烧录数次，逐次将片内FLASH的内
				  容写入外部FLASH（详见write_flash.c）。每烧录一段，可
					义通过检查屏幕中轮转播放的图片是否变多来确认是否烧录
					成功。全部烧录完成后，天气图像应有39张，GIF应顺畅运
					行，无白色填充帧。

注意：烧录某一部分数据后，桌面中对应的图像可能出现白线，这是由
		 于flash写入时出现bug，部分数据错误。只需重新写入该部分数
		 据即可。
*****************************************/
#include "usart.h"
#include "systick.h"
#include "flash.h"
#include "tim.h"
#include "lcd.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "write_flash.h"
extern u32 msTicks;
lv_ui lv_gui_deskop;
int main()
{
	printf_Init();
	FLASH_Init();
	tickTIM_Init();
	LCD_Init();
	
	
	/****************************************
	烧录结束后，取消两处注释可以测试是否烧录成功。
	此处为第一处注释。第二处注释在底下
	****************************************/
//	lv_init();
//	lv_port_disp_init();

//	setup_ui(&lv_gui_deskop);
//	events_init(&lv_gui_deskop);
	/****************************************
	****************************************/
	
	
	
	
	
	writeFlashWeatherPattern();
	writeFlashDancePattern();
	writeFlashCityWifi();
	writeFlash3DPattern();
	int i = 0;
	int j = 0;
	

	
	u8 Info[3];
	char readWifiName[200] = {0};
	char readWifiPassWord[200] = {0};
	FLASH_ReadData(45,0,Info,3);
	FLASH_ReadData(45,1,(u8*)readWifiName,Info[1]);
	FLASH_ReadData(45,2,(u8*)readWifiPassWord,Info[2]);
	printf("cityNum = %d\r\nwifiName = %s\r\nwifiPassword = %s\r\n",Info[0],readWifiName,readWifiPassWord);
	
	u32 weatherLastMsTicks = msTicks;
	u32 danceLastMsTicks = msTicks;
	while(1)
	{
		
		
		/****************************************
		烧录结束后，取消两处注释可以测试是否烧录成功。
		此处为第二处注释
		****************************************/
		
//		lv_task_handler();
//		
//		if(msTicks - weatherLastMsTicks > 1000)
//		{
//			weatherLastMsTicks = msTicks;
//			updateDeskopWeatherPattern(i++);
//			if(i == 39)	i = 0;
//		}
//		
//		if(msTicks - danceLastMsTicks > 50)
//		{
//			danceLastMsTicks = msTicks;
//			updateDeskopDancePattern(j++);
//			if(j==198)	j = 0;
//		}
	
	/****************************************
	****************************************/	
		
	}
}

#include "init.h"
#include "flash.h"
#include "math.h"
lv_ui_deskop lv_gui_deskop;
lv_ui_selectFunction lv_gui_selectFunction;
lv_ui_init	lv_gui_init;
lv_ui_functionClock lv_gui_functionClock;
TimeStruct time;
float initPitch,initRoll,initYaw;
CityWifiInfo_t cityWifiInfo;
extern float Pitch,Roll;
void holocubic_init(void)
{
	/********LCD及LVGL初始化*********/
	tickTIM_Init();
	delay_ms(1000);	
	LCD_Init();
	lv_init();			  		// lvgl系统初始化
	lv_port_disp_init();  // lvgl显示接口初始化,放在lv_init()的后面
	//lv_port_indev_init();	//不使用输入设备，采用手动模拟
	/******************************/
	setup_ui_init(&lv_gui_init);
	
	/**printf,RGB等基础功能初始化***/
	updateInitLabel("Initializing-basic-function......");
	updateInitBar(20);	
	for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
	{
		lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
	}
	printf_Init(PRINTF_BAUD_RATE);
	LED_Init();
	RGB_Init();
	/******************************/
	
	/*********FLASH初始化**********/
	updateInitLabel("Initializing-memory-device......");
	updateInitBar(40);	
	for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
	{
		lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
	}
	FLASH_Init();
	cityWifiInfo = FLASH_ReadCityWifi();	//获取全局城市编号、城市名、wifi账号、wifi密码
	printf("cityNum = %d\r\ncityName = %s\r\nwifiName = %s\r\nwifiPassword = %s\r\n",cityWifiInfo.cityNum,cityWifiInfo.cityName,cityWifiInfo.wifiName,cityWifiInfo.wifiPassword);
	/******************************/
	
	/*********ESP8266初始化*******/
	updateInitLabel("Connecting-wifi...");
	updateInitBar(60);	
	for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
	{
		lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
	}
	ESP8266_Init();	
	/****************************/
	
	
	/*********MPU6050初始化*******/
	updateInitLabel("Getting-default-attitude......");
	updateInitBar(100);	
	for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
	{
		lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
	}
	MPU6050_Init();
	MPU6050_DMP_Init();
	delay_ms(1000);
	MPU6050_GetInitAttitude();	//上电后获取初始姿态
	setup_ui_deskop(&lv_gui_deskop);	//切换至桌面
	/****************************/
}
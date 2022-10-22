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
	/********LCD��LVGL��ʼ��*********/
	tickTIM_Init();
	delay_ms(1000);	
	LCD_Init();
	lv_init();			  		// lvglϵͳ��ʼ��
	lv_port_disp_init();  // lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ���
	//lv_port_indev_init();	//��ʹ�������豸�������ֶ�ģ��
	/******************************/
	setup_ui_init(&lv_gui_init);
	
	/**printf,RGB�Ȼ������ܳ�ʼ��***/
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
	
	/*********FLASH��ʼ��**********/
	updateInitLabel("Initializing-memory-device......");
	updateInitBar(40);	
	for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
	{
		lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
	}
	FLASH_Init();
	cityWifiInfo = FLASH_ReadCityWifi();	//��ȡȫ�ֳ��б�š���������wifi�˺š�wifi����
	printf("cityNum = %d\r\ncityName = %s\r\nwifiName = %s\r\nwifiPassword = %s\r\n",cityWifiInfo.cityNum,cityWifiInfo.cityName,cityWifiInfo.wifiName,cityWifiInfo.wifiPassword);
	/******************************/
	
	/*********ESP8266��ʼ��*******/
	updateInitLabel("Connecting-wifi...");
	updateInitBar(60);	
	for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
	{
		lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
	}
	ESP8266_Init();	
	/****************************/
	
	
	/*********MPU6050��ʼ��*******/
	updateInitLabel("Getting-default-attitude......");
	updateInitBar(100);	
	for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
	{
		lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
	}
	MPU6050_Init();
	MPU6050_DMP_Init();
	delay_ms(1000);
	MPU6050_GetInitAttitude();	//�ϵ���ȡ��ʼ��̬
	setup_ui_deskop(&lv_gui_deskop);	//�л�������
	/****************************/
}
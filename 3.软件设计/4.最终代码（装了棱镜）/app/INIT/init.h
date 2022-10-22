#ifndef _INIT_H
#define _INIT_H
#include "stm32f4xx.h"
#include "led.h"
#include "usart.h"
#include "systick.h"
#include "tim.h"
#include "mpu6050.h"
#include "lcd.h"
#include "esp8266.h"
#include "picture.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "holocubic_function.h"

typedef struct CityWifiInfo_t{
	u8 cityNum;	//城市数组下标
	char cityName[50];	//城市拼音
	char wifiName[200];	//wifi账号
	char wifiPassword[200];	//wifi密码
}CityWifiInfo_t;


void holocubic_init(void);






#endif


#ifndef _ESP8266_H
#define _ESP8266_H
#include "stm32f4xx.h"
#define WIFI_CONNECTED 1
#define WIFI_NOCONNECT 0

#define ESP8266_PROCESS_RETURN_DATA			1
#define ESP8266_NO_PROCESS_RETURN_DATA	0

typedef struct{
	u8 week;	//星期几
	u16 year;	//年
	u8 month,day,hour,minute,second;	//月日时分秒
}TimeStruct;

typedef struct{
	u8 code;
	u8 temperature;
	u8 highTemperature;
	u8 lowTemperature;
	u8 precipitation;
	u8 humidityPercent;
}WeatherStruct;

void ESP8266_Init(void);
void ESP8266_SendString(char sendStr[150],u32 waitms,u8 needProcessData);	//待发送字符串、接收返回数据的时间
u8 ESP8266_Test(void);
void ESP8266_ConnectWifi(void);
TimeStruct ESP8266_GetTime(void);
void ESP8266_PrintTime(TimeStruct time);
WeatherStruct ESP8266_GetWeather(char *city);
void ESP8266_PrintWeather(WeatherStruct weather);
void ESP8266_Task(void);	//时间，天气获取任务
void ESP8266_UpdateTimeToLCD(void);
#endif

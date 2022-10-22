#ifndef _ESP8266_H
#define _ESP8266_H
#include "stm32f4xx.h"
#define WIFI_CONNECTED 1
#define WIFI_NOCONNECT 0

#define ESP8266_PROCESS_RETURN_DATA			1
#define ESP8266_NO_PROCESS_RETURN_DATA	0

typedef struct{
	u8 week;	//���ڼ�
	u16 year;	//��
	u8 month,day,hour,minute,second;	//����ʱ����
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
void ESP8266_SendString(char sendStr[150],u32 waitms,u8 needProcessData);	//�������ַ��������շ������ݵ�ʱ��
u8 ESP8266_Test(void);
void ESP8266_ConnectWifi(void);
TimeStruct ESP8266_GetTime(void);
void ESP8266_PrintTime(TimeStruct time);
WeatherStruct ESP8266_GetWeather(char *city);
void ESP8266_PrintWeather(WeatherStruct weather);
void ESP8266_Task(void);	//ʱ�䣬������ȡ����
void ESP8266_UpdateTimeToLCD(void);
#endif

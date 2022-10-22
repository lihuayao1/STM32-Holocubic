#ifndef _CUSTOM_H
#define _CUSTOM_H
#include "stm32f4xx.h"

#define CITY_SHENZHEN		0
#define CITY_ZHANJIANG	1
#define CITY_GUANGZHOU	2
#define CITY_GANZHOU		3
#define CITI_NANCHANG		4
#define CITY_BEIJING		5
#define CITY_SHANGHAI		6

#define WEATHER_QING		0
#define WEATHER_DUOYUN	1
#define WEATHER_YIN			2
#define WEATHER_YU			3
#define WEATHER_XUE			4
#define WEATHER_SHACHEN	5
#define WEATHER_WU			6
#define WEATHER_DAFENG	7
#define WEATHER_TAIFENG	8
#define WEATHER_LENG		9
#define WEATHER_RE			10

void updateDeskopDate(u8 month,u8 day,u8 week);
void updateDeskopCity(u8 cityName);
void updateDeskopWeatherText(u8 weather);
void updateDeskopTemperature(int temperature);
void updateDeskopWeatherInfo(int temperatureHigh,int temperatureLow,u8 rainPercent,u8 humidityPercent);
void updateDeskopWeatherPattern(u8 weatherCode);
void updateDeskopDancePattern(u8 num);
#endif

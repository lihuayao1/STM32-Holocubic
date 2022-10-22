/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "string.h"
#include "lcd.h"
#include "flash.h"
#include "systick.h"
#include "stdlib.h"
#include "esp8266.h"
extern TimeStruct time;
extern WeatherStruct nowWeather;
extern CityWifiInfo_t cityWifiInfo;
void setup_scr_deskop(lv_ui_deskop *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_gif
	ui->screen_gif = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_gif, 180, 180);
	lv_obj_set_size(ui->screen_gif, 60, 60);

	//Write style state: LV_STATE_DEFAULT for style_screen_gif_main_main_default
	static lv_style_t style_screen_gif_main_main_default;
	lv_style_reset(&style_screen_gif_main_main_default);
	lv_style_set_img_recolor(&style_screen_gif_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gif_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gif_main_main_default, 255);
	lv_obj_add_style(ui->screen_gif, &style_screen_gif_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_gif, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_gif,&dancePatternDefault);
	lv_img_set_pivot(ui->screen_gif, 0,0);
	lv_img_set_angle(ui->screen_gif, 0);

	//Write codes screen_hour
	ui->screen_hour = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_hour, 0, 50);
	lv_obj_set_size(ui->screen_hour, 100, 70);
	char tempStr[15];	numToString(time.hour,tempStr);
	lv_label_set_text(ui->screen_hour, tempStr);
	lv_label_set_long_mode(ui->screen_hour, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_hour, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_hour_main_main_default
	static lv_style_t style_screen_hour_main_main_default;
	lv_style_reset(&style_screen_hour_main_main_default);
	lv_style_set_radius(&style_screen_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_hour_main_main_default, 0);
	lv_style_set_text_color(&style_screen_hour_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_hour_main_main_default, &lv_font_montserratMedium_70);
	lv_style_set_text_letter_space(&style_screen_hour_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_hour_main_main_default, 0);
	lv_obj_add_style(ui->screen_hour, &style_screen_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_min
	ui->screen_min = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_min, 90, 50);
	lv_obj_set_size(ui->screen_min, 100, 70);
	numToString(time.minute,tempStr);
	lv_label_set_text(ui->screen_min, tempStr);
	lv_label_set_long_mode(ui->screen_min, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_min, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_min_main_main_default
	static lv_style_t style_screen_min_main_main_default;
	lv_style_reset(&style_screen_min_main_main_default);
	lv_style_set_radius(&style_screen_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_min_main_main_default, lv_color_make(0xff, 0xd5, 0x00));
	lv_style_set_text_font(&style_screen_min_main_main_default, &lv_font_montserratMedium_70);
	lv_style_set_text_letter_space(&style_screen_min_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_min, &style_screen_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_second
	ui->screen_second = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_second, 190, 75);
	lv_obj_set_size(ui->screen_second, 50, 40);
	numToString(time.second,tempStr);
	lv_label_set_text(ui->screen_second, tempStr);
	lv_label_set_long_mode(ui->screen_second, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_second, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_second_main_main_default
	static lv_style_t style_screen_second_main_main_default;
	lv_style_reset(&style_screen_second_main_main_default);
	lv_style_set_radius(&style_screen_second_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_second_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_second_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_second_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_second_main_main_default, 0);
	lv_style_set_text_color(&style_screen_second_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_second_main_main_default, &lv_font_simsun_40);
	lv_style_set_text_letter_space(&style_screen_second_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_second_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_second_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_second_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_second_main_main_default, 0);
	lv_obj_add_style(ui->screen_second, &style_screen_second_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather
	ui->screen_weather = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_weather, 180, 5);
	lv_obj_set_size(ui->screen_weather, 48, 48);

	//Write style state: LV_STATE_DEFAULT for style_screen_weather_main_main_default
	static lv_style_t style_screen_weather_main_main_default;
	lv_style_reset(&style_screen_weather_main_main_default);
	lv_style_set_img_recolor(&style_screen_weather_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_weather_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_weather_main_main_default, 255);
	lv_obj_add_style(ui->screen_weather, &style_screen_weather_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_weather, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_weather,&weatherPatternDefault);
	updateDeskopWeatherPattern(nowWeather.code);
	lv_img_set_pivot(ui->screen_weather, 0,0);
	lv_img_set_angle(ui->screen_weather, 0);

	//Write codes screen_weather_info
	ui->screen_weather_info = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_weather_info, 80, 211);
	lv_obj_set_size(ui->screen_weather_info, 80, 20);
	//lv_label_set_text(ui->screen_weather_info, "最高气温：35度，最低气温：20度，降水：50mm，相对湿度20%。");
	updateDeskopWeatherInfo(nowWeather.highTemperature,nowWeather.lowTemperature,nowWeather.precipitation,nowWeather.humidityPercent);
	lv_label_set_long_mode(ui->screen_weather_info, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_style_text_align(ui->screen_weather_info, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_weather_info_main_main_default
	static lv_style_t style_screen_weather_info_main_main_default;
	lv_style_reset(&style_screen_weather_info_main_main_default);
	lv_style_set_radius(&style_screen_weather_info_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_weather_info_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_weather_info_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_weather_info_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_weather_info_main_main_default, 0);
	lv_style_set_text_color(&style_screen_weather_info_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_weather_info_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_letter_space(&style_screen_weather_info_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_weather_info_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_weather_info_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_weather_info_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_weather_info_main_main_default, 0);
	lv_obj_add_style(ui->screen_weather_info, &style_screen_weather_info_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_date
	ui->screen_date = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_date, 28, 125);
	lv_obj_set_size(ui->screen_date, 100, 20);
	//lv_label_set_text(ui->screen_date, "08月27日");	//在下一处调用updateDeskopDate,这里调用会出现weeklabel未创建的bug
	lv_label_set_long_mode(ui->screen_date, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_date, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_main_main_default
	static lv_style_t style_screen_date_main_main_default;
	lv_style_reset(&style_screen_date_main_main_default);
	lv_style_set_radius(&style_screen_date_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_date_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_date_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_date_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_main_main_default, 0);
	lv_style_set_text_color(&style_screen_date_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_date_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_letter_space(&style_screen_date_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_date_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_date_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_date_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_date_main_main_default, 0);
	lv_obj_add_style(ui->screen_date, &style_screen_date_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_week
	ui->screen_week = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_week, 130, 125);
	lv_obj_set_size(ui->screen_week, 75, 20);
//	lv_label_set_text(ui->screen_week, "星期六");
	updateDeskopDate(time.month,time.day,time.week);
	lv_label_set_long_mode(ui->screen_week, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_week, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_week_main_main_default
	static lv_style_t style_screen_week_main_main_default;
	lv_style_reset(&style_screen_week_main_main_default);
	lv_style_set_radius(&style_screen_week_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_week_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_week_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_week_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_week_main_main_default, 0);
	lv_style_set_text_color(&style_screen_week_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_week_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_letter_space(&style_screen_week_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_week_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_week_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_week_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_week_main_main_default, 0);
	lv_obj_add_style(ui->screen_week, &style_screen_week_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_text
	ui->screen_weather_text = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_weather_text, 55, 155);
	lv_obj_set_size(ui->screen_weather_text, 130, 20);
	//lv_label_set_text(ui->screen_weather_text, "天气：晴");
	updateDeskopWeatherText(nowWeather.code);
	lv_label_set_long_mode(ui->screen_weather_text, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_weather_text, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_weather_text_main_main_default
	static lv_style_t style_screen_weather_text_main_main_default;
	lv_style_reset(&style_screen_weather_text_main_main_default);
	lv_style_set_radius(&style_screen_weather_text_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_weather_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_weather_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_weather_text_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_weather_text_main_main_default, 0);
	lv_style_set_text_color(&style_screen_weather_text_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_weather_text_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_letter_space(&style_screen_weather_text_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_weather_text_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_weather_text_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_weather_text_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_weather_text_main_main_default, 0);
	lv_obj_add_style(ui->screen_weather_text, &style_screen_weather_text_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_temperature
	ui->screen_temperature = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_temperature, 55, 180);
	lv_obj_set_size(ui->screen_temperature, 130, 20);
	//lv_label_set_text(ui->screen_temperature, "气温：35度");
	updateDeskopTemperature(nowWeather.temperature);
	lv_label_set_long_mode(ui->screen_temperature, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_temperature, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_temperature_main_main_default
	static lv_style_t style_screen_temperature_main_main_default;
	lv_style_reset(&style_screen_temperature_main_main_default);
	lv_style_set_radius(&style_screen_temperature_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_temperature_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_temperature_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_temperature_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_temperature_main_main_default, 0);
	lv_style_set_text_color(&style_screen_temperature_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_temperature_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_letter_space(&style_screen_temperature_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_temperature_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_temperature_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_temperature_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_temperature_main_main_default, 0);
	lv_obj_add_style(ui->screen_temperature, &style_screen_temperature_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_city
	ui->screen_city = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_city, 70, 7);
	lv_obj_set_size(ui->screen_city, 100, 40);
	//lv_label_set_text(ui->screen_city, "深圳");
	updateDeskopCity(cityWifiInfo.cityName);
	lv_label_set_long_mode(ui->screen_city, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_city, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_city_main_main_default
	static lv_style_t style_screen_city_main_main_default;
	lv_style_reset(&style_screen_city_main_main_default);
	lv_style_set_radius(&style_screen_city_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_city_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_city_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_city_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_city_main_main_default, 0);
	lv_style_set_text_color(&style_screen_city_main_main_default, lv_color_make(0x00, 0xbf, 0xff));
	lv_style_set_text_font(&style_screen_city_main_main_default, &lv_font_simsun_40);
	lv_style_set_text_letter_space(&style_screen_city_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_city_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_city_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_city_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_city_main_main_default, 0);
	lv_obj_add_style(ui->screen_city, &style_screen_city_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}
void numToString(int num,char *str)
{
	u8 stack[40];int top = -1;
	memset(str,0,sizeof(str));
	if(num < 0)
	{
		*(str++) = '-';
		num *= (-1);
	}
	if(num<10)	
	{
		str[0] = '0';
		str[1] = num + '0';
		return;
	}
	while(num!=0)
	{
		stack[++top] = num%10;
		num /= 10;
	}
	while(top>=0)
	{
		*str = (stack[top--] + '0');
		str++;
	}
}

int stringToNum(char *str)
{
	int i = 0;
	int ret = 0;
	while(str[i] != '\0')
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	return ret;
}







extern lv_ui_deskop lv_gui_deskop;
//调用lv_labelset_text必须在该文件内，否则会有中文显示bug。原因未知
/*疑似原因：该文件定义的中文数组内容格式与其它文件定义的会不一样，一定要用本文件的数组格
  式才能正常调用lv_labelset_text*/
void updateDeskopDate(u8 month,u8 day,u8 week)
{
	char dateStr[15];
	char weekStr[15];
	char temp[10];
	
	memset(dateStr,0,sizeof(dateStr));
	numToString(month,temp);	strcat(dateStr,temp);
	strcat(dateStr,"月");	numToString(day,temp);
	strcat(dateStr,temp);strcat(dateStr,"日");
	lv_label_set_text(lv_gui_deskop.screen_date, dateStr);
	
	memset(weekStr,0,sizeof(weekStr));
	strcat(weekStr,"星期");
	char weekChinese[8][5]={" ","一","二","三","四","五","六","日"};
	strcat(weekStr,weekChinese[week]);
	lv_label_set_text(lv_gui_deskop.screen_week,weekStr);
}

//无法直接传中文字符串进来，原因同上
void updateDeskopCity(char cityName[])	//采用传入拼音的方式更新城市
{
	char cityNameArrPinYin[][10] = {"shenzhen","zhanjiang","guangzhou","ganzhou","nanchang","beijing","shanghai"}; 
	u8 pos = 0;
	char cityNameArr[][10] = {"深圳","湛江","广州","赣州","南昌","北京","上海"};
	for(u8 i = 0; i < 10; i++)
		if(strcmp(cityName,cityNameArrPinYin[i])==0)
			pos = i;
	
	
	lv_label_set_text(lv_gui_deskop.screen_city,cityNameArr[pos]);
}

void updateDeskopWeatherText(u8 weatherCode)
{
	u8 weatherArrPos = 0;
	char weatherArr[][15] = {"晴","多云","阴","雨","雪","沙尘","雾","大风","台风","冷","热"};
	char str[25];	memset(str,0,sizeof(str));
	if(weatherCode<=3)
		weatherArrPos = 0;
	else if(weatherCode>=4&&weatherCode<=8)
		weatherArrPos = 1;
	else if(weatherCode == 9)
		weatherArrPos = 2;
	else if(weatherCode>=10&&weatherCode<=19)
		weatherArrPos = 3;
	else if(weatherCode>=20&&weatherCode<=25)
		weatherArrPos = 4;
	else if(weatherCode>=26&&weatherCode<=29)
		weatherArrPos = 5;
	else if(weatherCode==30||weatherCode==31)
		weatherArrPos = 6;
	else if(weatherCode==32||weatherCode==33)
		weatherArrPos = 7;
	else if(weatherCode>=34&&weatherCode<=36)
		weatherArrPos = 8;
	else if(weatherCode == 37)
		weatherArrPos = 9;
	else
		weatherArrPos = 10;
	strcat(str,"天气：");	strcat(str,weatherArr[weatherArrPos]);
	lv_label_set_text(lv_gui_deskop.screen_weather_text,str);
}

void updateDeskopTemperature(int temperature)
{
	char str[25];memset(str,0,sizeof(str));
	char temp[10];
	strcat(str,"气温：");
	numToString(temperature,temp);	strcat(str,temp);
	strcat(str,"度");
	lv_label_set_text(lv_gui_deskop.screen_temperature,str);
}

//"最高气温：35度，最低气温：20度，降水概率50%，相对湿度20%。"
void updateDeskopWeatherInfo(int temperatureHigh,int temperatureLow,u8 precipitation,u8 humidityPercent)
{
	char str[150];	memset(str,0,sizeof(str));
	char temp[10];
	strcat(str,"最高气温：");	
	numToString(temperatureHigh,temp);	strcat(str,temp);	
	strcat(str,"度，最低气温：");
	numToString(temperatureLow,temp);	strcat(str,temp);	
	strcat(str,"度，降水：");
	numToString(precipitation,temp);	strcat(str,temp);	
	strcat(str,"mm，相对湿度");
	numToString(humidityPercent,temp);	strcat(str,temp);	
	strcat(str,"%。");
	lv_label_set_text(lv_gui_deskop.screen_weather_info,str);
}

extern u8 weatherPatternBmp[7200];
extern u8 DMA1_COMPLETED;
void updateDeskopWeatherPattern(u8 weatherCode)
{
	//每个BLOCK存放8张图片
	u8 block = (weatherCode/8),sector = (weatherCode%8)*2;
	FLASH_DMAReadData(block,sector,weatherPatternBmp,6912);
	while(DMA1_COMPLETED == 0);	DMA1_COMPLETED = 0;
	lv_img_set_src(lv_gui_deskop.screen_weather,&weatherPatternRead);
}

extern u8 dancePatternBmp[10800];
void updateDeskopDancePattern(u8 num)
{
	u8 block = (num/5)+5,sector = (num%5)*3;
	FLASH_DMAReadData(block,sector,dancePatternBmp,10800);
	while(DMA1_COMPLETED == 0);	DMA1_COMPLETED = 0;
	lv_img_set_src(lv_gui_deskop.screen_gif,&dancePatternRead);
}



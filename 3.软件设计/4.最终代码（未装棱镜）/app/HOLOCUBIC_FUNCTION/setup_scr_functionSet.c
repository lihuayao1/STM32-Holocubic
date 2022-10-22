/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


static lv_obj_t * g_kb;
static void kb_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}
static void ta_event_cb(lv_event_t *e)
{

	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = lv_event_get_target(e);
	lv_obj_t *kb = lv_event_get_user_data(e);
	if (code == LV_EVENT_FOCUSED)
	{
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
	if (code == LV_EVENT_DEFOCUSED)
	{
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}

void setup_scr_functionSet(lv_ui_functionSet *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_cityNameLabel
	ui->screen_cityNameLabel = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_cityNameLabel, 70, 25);
	lv_obj_set_size(ui->screen_cityNameLabel, 100, 40);
	lv_label_set_text(ui->screen_cityNameLabel, "赣州");
	lv_label_set_long_mode(ui->screen_cityNameLabel, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_cityNameLabel, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_citynamelabel_main_main_default
	static lv_style_t style_screen_citynamelabel_main_main_default;
	lv_style_reset(&style_screen_citynamelabel_main_main_default);
	lv_style_set_radius(&style_screen_citynamelabel_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_citynamelabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_citynamelabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_citynamelabel_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_citynamelabel_main_main_default, 0);
	lv_style_set_text_color(&style_screen_citynamelabel_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_citynamelabel_main_main_default, &lv_font_simsun_40);
	lv_style_set_text_letter_space(&style_screen_citynamelabel_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_citynamelabel_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_citynamelabel_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_citynamelabel_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_citynamelabel_main_main_default, 0);
	lv_obj_add_style(ui->screen_cityNameLabel, &style_screen_citynamelabel_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wifiNameLabel
	ui->screen_wifiNameLabel = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_wifiNameLabel, 10, 80);
	lv_obj_set_size(ui->screen_wifiNameLabel, 130, 24);
	lv_label_set_text(ui->screen_wifiNameLabel, "wifiName:");
	lv_label_set_long_mode(ui->screen_wifiNameLabel, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_wifiNameLabel, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_wifinamelabel_main_main_default
	static lv_style_t style_screen_wifinamelabel_main_main_default;
	lv_style_reset(&style_screen_wifinamelabel_main_main_default);
	lv_style_set_radius(&style_screen_wifinamelabel_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_wifinamelabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_wifinamelabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_wifinamelabel_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_wifinamelabel_main_main_default, 0);
	lv_style_set_text_color(&style_screen_wifinamelabel_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_wifinamelabel_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_screen_wifinamelabel_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_wifinamelabel_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_wifinamelabel_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_wifinamelabel_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_wifinamelabel_main_main_default, 0);
	lv_obj_add_style(ui->screen_wifiNameLabel, &style_screen_wifinamelabel_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passwordLabel
	ui->screen_passwordLabel = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_passwordLabel, 10, 150);
	lv_obj_set_size(ui->screen_passwordLabel, 130, 32);
	lv_label_set_text(ui->screen_passwordLabel, "password:");
	lv_label_set_long_mode(ui->screen_passwordLabel, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_passwordLabel, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passwordlabel_main_main_default
	static lv_style_t style_screen_passwordlabel_main_main_default;
	lv_style_reset(&style_screen_passwordlabel_main_main_default);
	lv_style_set_radius(&style_screen_passwordlabel_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passwordlabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passwordlabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passwordlabel_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passwordlabel_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passwordlabel_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_passwordlabel_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_screen_passwordlabel_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_passwordlabel_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passwordlabel_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passwordlabel_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passwordlabel_main_main_default, 0);
	lv_obj_add_style(ui->screen_passwordLabel, &style_screen_passwordlabel_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wifiNameText
	ui->screen_wifiNameText = lv_textarea_create(ui->screen);
	lv_obj_set_pos(ui->screen_wifiNameText, 15, 110);
	lv_obj_set_size(ui->screen_wifiNameText, 200, 25);

	//Write style state: LV_STATE_DEFAULT for style_screen_wifinametext_main_main_default
	static lv_style_t style_screen_wifinametext_main_main_default;
	lv_style_reset(&style_screen_wifinametext_main_main_default);
	lv_style_set_radius(&style_screen_wifinametext_main_main_default, 4);
	lv_style_set_bg_color(&style_screen_wifinametext_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_wifinametext_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_wifinametext_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_wifinametext_main_main_default, 255);
	lv_style_set_border_color(&style_screen_wifinametext_main_main_default, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_border_width(&style_screen_wifinametext_main_main_default, 2);
	lv_style_set_text_color(&style_screen_wifinametext_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_wifinametext_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_wifinametext_main_main_default, 2);
	lv_style_set_text_align(&style_screen_wifinametext_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_wifinametext_main_main_default, 2);
	lv_style_set_pad_right(&style_screen_wifinametext_main_main_default, 2);
	lv_style_set_pad_top(&style_screen_wifinametext_main_main_default, 2);
	lv_style_set_pad_bottom(&style_screen_wifinametext_main_main_default, 2);
	lv_obj_add_style(ui->screen_wifiNameText, &style_screen_wifinametext_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_wifinametext_main_scrollbar_default
	static lv_style_t style_screen_wifinametext_main_scrollbar_default;
	lv_style_reset(&style_screen_wifinametext_main_scrollbar_default);
	lv_style_set_radius(&style_screen_wifinametext_main_scrollbar_default, 0);
	lv_style_set_bg_color(&style_screen_wifinametext_main_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_wifinametext_main_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_wifinametext_main_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_wifinametext_main_scrollbar_default, 255);
	lv_obj_add_style(ui->screen_wifiNameText, &style_screen_wifinametext_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_textarea_set_text(ui->screen_wifiNameText,"...");
	if (g_kb == NULL)
	{
		g_kb = lv_keyboard_create(ui->screen);
		lv_obj_add_event_cb(g_kb, kb_event_cb, LV_EVENT_ALL, NULL);
		lv_obj_add_flag(g_kb, LV_OBJ_FLAG_HIDDEN);
		lv_keyboard_set_textarea(g_kb, ui->screen_wifiNameText);
		lv_obj_add_event_cb(ui->screen_wifiNameText, ta_event_cb, LV_EVENT_ALL, g_kb);
	}
//	lv_keyboard_set_textarea(g_kb, ui->screen_wifiNameText);
//	lv_obj_add_event_cb(ui->screen_wifiNameText, ta_event_cb, LV_EVENT_ALL, g_kb);

	//Write codes screen_passwordText
	ui->screen_passwordText = lv_textarea_create(ui->screen);
	lv_obj_set_pos(ui->screen_passwordText, 15, 180);
	lv_obj_set_size(ui->screen_passwordText, 200, 25);

	//Write style state: LV_STATE_DEFAULT for style_screen_passwordtext_main_main_default
	static lv_style_t style_screen_passwordtext_main_main_default;
	lv_style_reset(&style_screen_passwordtext_main_main_default);
	lv_style_set_radius(&style_screen_passwordtext_main_main_default, 4);
	lv_style_set_bg_color(&style_screen_passwordtext_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_passwordtext_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_passwordtext_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passwordtext_main_main_default, 255);
	lv_style_set_border_color(&style_screen_passwordtext_main_main_default, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_border_width(&style_screen_passwordtext_main_main_default, 2);
	lv_style_set_text_color(&style_screen_passwordtext_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_passwordtext_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_passwordtext_main_main_default, 2);
	lv_style_set_text_align(&style_screen_passwordtext_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_passwordtext_main_main_default, 2);
	lv_style_set_pad_right(&style_screen_passwordtext_main_main_default, 2);
	lv_style_set_pad_top(&style_screen_passwordtext_main_main_default, 2);
	lv_style_set_pad_bottom(&style_screen_passwordtext_main_main_default, 2);
	lv_obj_add_style(ui->screen_passwordText, &style_screen_passwordtext_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_passwordtext_main_scrollbar_default
	static lv_style_t style_screen_passwordtext_main_scrollbar_default;
	lv_style_reset(&style_screen_passwordtext_main_scrollbar_default);
	lv_style_set_radius(&style_screen_passwordtext_main_scrollbar_default, 0);
	lv_style_set_bg_color(&style_screen_passwordtext_main_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passwordtext_main_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passwordtext_main_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passwordtext_main_scrollbar_default, 255);
	lv_obj_add_style(ui->screen_passwordText, &style_screen_passwordtext_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_textarea_set_text(ui->screen_passwordText,"...");
	if (g_kb == NULL)
	{
		g_kb = lv_keyboard_create(ui->screen);
		lv_obj_add_event_cb(g_kb, kb_event_cb, LV_EVENT_ALL, NULL);
		lv_obj_add_flag(g_kb, LV_OBJ_FLAG_HIDDEN);
		lv_keyboard_set_textarea(g_kb, ui->screen_passwordText);
		lv_obj_add_event_cb(ui->screen_passwordText, ta_event_cb, LV_EVENT_ALL, g_kb);
	}
//	lv_keyboard_set_textarea(g_kb, ui->screen_passwordText);
//	lv_obj_add_event_cb(ui->screen_passwordText, ta_event_cb, LV_EVENT_ALL, g_kb);

	//Write codes screen_cityLabel
	ui->screen_cityLabel = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_cityLabel, 10, 10);
	lv_obj_set_size(ui->screen_cityLabel, 60, 25);
	lv_label_set_text(ui->screen_cityLabel, "city:");
	lv_label_set_long_mode(ui->screen_cityLabel, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_cityLabel, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_citynamlabel_main_main_default
	static lv_style_t style_screen_citynamlabel_main_main_default;
	lv_style_reset(&style_screen_citynamlabel_main_main_default);
	lv_style_set_radius(&style_screen_citynamlabel_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_citynamlabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_citynamlabel_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_citynamlabel_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_citynamlabel_main_main_default, 0);
	lv_style_set_text_color(&style_screen_citynamlabel_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_citynamlabel_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_screen_citynamlabel_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_citynamlabel_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_citynamlabel_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_citynamlabel_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_citynamlabel_main_main_default, 0);
	lv_obj_add_style(ui->screen_cityLabel, &style_screen_citynamlabel_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}


extern lv_ui_functionSet lv_gui_functionSet;
void updateSetFunctionCity(char cityName[])
{
	char cityNameArr[][10] = {"深圳","湛江","广州","赣州","南昌","北京","上海"};
	char cityNameArrPinYin[][10] = {"shenzhen","zhanjiang","guangzhou","ganzhou","nanchang","beijing","shanghai"}; 
	u8 pos = 0;
	for(u8 i = 0; i < 10; i++)
		if(strcmp(cityName,cityNameArrPinYin[i])==0)
			pos = i;
	lv_label_set_text(lv_gui_functionSet.screen_cityNameLabel,cityNameArr[pos]);
}

void updateSetFunctionWifiName(char wifiName[])
{
	lv_textarea_set_text(lv_gui_functionSet.screen_wifiNameText,wifiName);
}

void updateSetFunctionWifiPassword(char wifiPassword[])
{
	lv_textarea_set_text(lv_gui_functionSet.screen_passwordText,wifiPassword);
}

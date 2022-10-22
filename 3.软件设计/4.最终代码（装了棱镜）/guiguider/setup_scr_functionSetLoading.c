/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_functionSetLoading(lv_ui_functionSetLoading *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_loading_bar
	ui->screen_loading_bar = lv_bar_create(ui->screen);
	lv_obj_set_pos(ui->screen_loading_bar, 20, 80);
	lv_obj_set_size(ui->screen_loading_bar, 200, 20);

	//Write style state: LV_STATE_DEFAULT for style_screen_loading_bar_main_main_default
	static lv_style_t style_screen_loading_bar_main_main_default;
	lv_style_reset(&style_screen_loading_bar_main_main_default);
	lv_style_set_radius(&style_screen_loading_bar_main_main_default, 10);
	lv_style_set_bg_color(&style_screen_loading_bar_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_loading_bar_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_loading_bar_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_loading_bar_main_main_default, 218);
	lv_style_set_pad_left(&style_screen_loading_bar_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_loading_bar_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_loading_bar_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_loading_bar_main_main_default, 0);
	lv_obj_add_style(ui->screen_loading_bar, &style_screen_loading_bar_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_loading_bar_main_indicator_default
	static lv_style_t style_screen_loading_bar_main_indicator_default;
	lv_style_reset(&style_screen_loading_bar_main_indicator_default);
	lv_style_set_radius(&style_screen_loading_bar_main_indicator_default, 10);
	lv_style_set_bg_color(&style_screen_loading_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_loading_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_loading_bar_main_indicator_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_loading_bar_main_indicator_default, 255);
	lv_obj_add_style(ui->screen_loading_bar, &style_screen_loading_bar_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->screen_loading_bar, 1000, 0);
	lv_bar_set_mode(ui->screen_loading_bar, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_loading_bar, 50, LV_ANIM_OFF);

	//Write codes screen_saving_label
	ui->screen_saving_label = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_saving_label, 40, 130);
	lv_obj_set_size(ui->screen_saving_label, 180, 30);
	lv_label_set_text(ui->screen_saving_label, "Saving......");
	lv_label_set_long_mode(ui->screen_saving_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_saving_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_saving_label_main_main_default
	static lv_style_t style_screen_saving_label_main_main_default;
	lv_style_reset(&style_screen_saving_label_main_main_default);
	lv_style_set_radius(&style_screen_saving_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_saving_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_saving_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_saving_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_saving_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_saving_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_saving_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_screen_saving_label_main_main_default, 5);
	lv_style_set_pad_left(&style_screen_saving_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_saving_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_saving_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_saving_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_saving_label, &style_screen_saving_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}

extern lv_ui_functionSetLoading lv_gui_functionSetLoading;
void updateSetLoadingBar(u8 num)
{
	lv_bar_set_value(lv_gui_functionSetLoading.screen_loading_bar,num,LV_ANIM_ON);
}

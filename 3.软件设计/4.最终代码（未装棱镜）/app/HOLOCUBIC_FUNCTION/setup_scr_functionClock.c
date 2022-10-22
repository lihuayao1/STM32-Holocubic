/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "holocubic_function.h"
extern u16 clockFunctionYear;
extern u8 clockFunctionMonth,clockFunctionDay;
extern u8 clockFunctionIsAm,clockFunctionHour,clockFunctionMin;
extern u8 clockFunctionOffOn;
static void _screen_date_year_dropdown_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_year_dropdown_extra_list_selected_default
	static lv_style_t style_screen_date_year_dropdown_extra_list_selected_default;
	lv_style_reset(&style_screen_date_year_dropdown_extra_list_selected_default);
	lv_style_set_radius(&style_screen_date_year_dropdown_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_screen_date_year_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_date_year_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen_date_year_dropdown_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_year_dropdown_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_screen_date_year_dropdown_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_year_dropdown_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_screen_date_year_dropdown_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_date_year_dropdown_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_year_dropdown_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_year_dropdown_extra_list_main_default
	static lv_style_t style_screen_date_year_dropdown_extra_list_main_default;
	lv_style_reset(&style_screen_date_year_dropdown_extra_list_main_default);
	lv_style_set_radius(&style_screen_date_year_dropdown_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_screen_date_year_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_year_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_year_dropdown_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_year_dropdown_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_date_year_dropdown_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_year_dropdown_extra_list_main_default, 1);
	lv_style_set_text_color(&style_screen_date_year_dropdown_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_date_year_dropdown_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_screen_date_year_dropdown_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_year_dropdown_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_year_dropdown_extra_list_scrollbar_default
	static lv_style_t style_screen_date_year_dropdown_extra_list_scrollbar_default;
	lv_style_reset(&style_screen_date_year_dropdown_extra_list_scrollbar_default);
	lv_style_set_radius(&style_screen_date_year_dropdown_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_screen_date_year_dropdown_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_date_year_dropdown_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_year_dropdown_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_year_dropdown_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_year_dropdown_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}
static void _screen_date_month_dropdown_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_month_dropdown_extra_list_selected_default
	static lv_style_t style_screen_date_month_dropdown_extra_list_selected_default;
	lv_style_reset(&style_screen_date_month_dropdown_extra_list_selected_default);
	lv_style_set_radius(&style_screen_date_month_dropdown_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_screen_date_month_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_date_month_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen_date_month_dropdown_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_month_dropdown_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_screen_date_month_dropdown_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_month_dropdown_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_screen_date_month_dropdown_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_date_month_dropdown_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_month_dropdown_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_month_dropdown_extra_list_main_default
	static lv_style_t style_screen_date_month_dropdown_extra_list_main_default;
	lv_style_reset(&style_screen_date_month_dropdown_extra_list_main_default);
	lv_style_set_radius(&style_screen_date_month_dropdown_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_screen_date_month_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_month_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_month_dropdown_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_month_dropdown_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_date_month_dropdown_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_month_dropdown_extra_list_main_default, 1);
	lv_style_set_text_color(&style_screen_date_month_dropdown_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_date_month_dropdown_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_screen_date_month_dropdown_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_month_dropdown_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_month_dropdown_extra_list_scrollbar_default
	static lv_style_t style_screen_date_month_dropdown_extra_list_scrollbar_default;
	lv_style_reset(&style_screen_date_month_dropdown_extra_list_scrollbar_default);
	lv_style_set_radius(&style_screen_date_month_dropdown_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_screen_date_month_dropdown_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_date_month_dropdown_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_month_dropdown_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_month_dropdown_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_month_dropdown_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}
static void _screen_date_day_dropdown_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_day_dropdown_extra_list_selected_default
	static lv_style_t style_screen_date_day_dropdown_extra_list_selected_default;
	lv_style_reset(&style_screen_date_day_dropdown_extra_list_selected_default);
	lv_style_set_radius(&style_screen_date_day_dropdown_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_screen_date_day_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_date_day_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen_date_day_dropdown_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_day_dropdown_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_screen_date_day_dropdown_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_day_dropdown_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_screen_date_day_dropdown_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_date_day_dropdown_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_day_dropdown_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_day_dropdown_extra_list_main_default
	static lv_style_t style_screen_date_day_dropdown_extra_list_main_default;
	lv_style_reset(&style_screen_date_day_dropdown_extra_list_main_default);
	lv_style_set_radius(&style_screen_date_day_dropdown_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_screen_date_day_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_day_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_day_dropdown_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_day_dropdown_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_date_day_dropdown_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_day_dropdown_extra_list_main_default, 1);
	lv_style_set_text_color(&style_screen_date_day_dropdown_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_date_day_dropdown_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_screen_date_day_dropdown_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_day_dropdown_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_day_dropdown_extra_list_scrollbar_default
	static lv_style_t style_screen_date_day_dropdown_extra_list_scrollbar_default;
	lv_style_reset(&style_screen_date_day_dropdown_extra_list_scrollbar_default);
	lv_style_set_radius(&style_screen_date_day_dropdown_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_screen_date_day_dropdown_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_date_day_dropdown_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_day_dropdown_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_day_dropdown_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_date_day_dropdown_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}
static void _screen_am_pm_dropdown_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_screen_am_pm_dropdown_extra_list_selected_default
	static lv_style_t style_screen_am_pm_dropdown_extra_list_selected_default;
	lv_style_reset(&style_screen_am_pm_dropdown_extra_list_selected_default);
	lv_style_set_radius(&style_screen_am_pm_dropdown_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_screen_am_pm_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_am_pm_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen_am_pm_dropdown_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_am_pm_dropdown_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_screen_am_pm_dropdown_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_am_pm_dropdown_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_screen_am_pm_dropdown_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_am_pm_dropdown_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_am_pm_dropdown_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_am_pm_dropdown_extra_list_main_default
	static lv_style_t style_screen_am_pm_dropdown_extra_list_main_default;
	lv_style_reset(&style_screen_am_pm_dropdown_extra_list_main_default);
	lv_style_set_radius(&style_screen_am_pm_dropdown_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_screen_am_pm_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_am_pm_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_am_pm_dropdown_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_am_pm_dropdown_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_am_pm_dropdown_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_am_pm_dropdown_extra_list_main_default, 1);
	lv_style_set_text_color(&style_screen_am_pm_dropdown_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_am_pm_dropdown_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_screen_am_pm_dropdown_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_am_pm_dropdown_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_am_pm_dropdown_extra_list_scrollbar_default
	static lv_style_t style_screen_am_pm_dropdown_extra_list_scrollbar_default;
	lv_style_reset(&style_screen_am_pm_dropdown_extra_list_scrollbar_default);
	lv_style_set_radius(&style_screen_am_pm_dropdown_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_screen_am_pm_dropdown_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_am_pm_dropdown_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_am_pm_dropdown_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_am_pm_dropdown_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_am_pm_dropdown_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}
static void _screen_hour_dropdown_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_screen_hour_dropdown_extra_list_selected_default
	static lv_style_t style_screen_hour_dropdown_extra_list_selected_default;
	lv_style_reset(&style_screen_hour_dropdown_extra_list_selected_default);
	lv_style_set_radius(&style_screen_hour_dropdown_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_screen_hour_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_hour_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen_hour_dropdown_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_hour_dropdown_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_screen_hour_dropdown_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_hour_dropdown_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_screen_hour_dropdown_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_hour_dropdown_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_hour_dropdown_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_hour_dropdown_extra_list_main_default
	static lv_style_t style_screen_hour_dropdown_extra_list_main_default;
	lv_style_reset(&style_screen_hour_dropdown_extra_list_main_default);
	lv_style_set_radius(&style_screen_hour_dropdown_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_screen_hour_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_hour_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_hour_dropdown_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_hour_dropdown_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_hour_dropdown_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_hour_dropdown_extra_list_main_default, 1);
	lv_style_set_text_color(&style_screen_hour_dropdown_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_hour_dropdown_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_screen_hour_dropdown_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_hour_dropdown_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_hour_dropdown_extra_list_scrollbar_default
	static lv_style_t style_screen_hour_dropdown_extra_list_scrollbar_default;
	lv_style_reset(&style_screen_hour_dropdown_extra_list_scrollbar_default);
	lv_style_set_radius(&style_screen_hour_dropdown_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_screen_hour_dropdown_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_hour_dropdown_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_hour_dropdown_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_hour_dropdown_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_hour_dropdown_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}
static void _screen_min_dropdown_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);

	//Write style state: LV_STATE_DEFAULT for style_screen_min_dropdown_extra_list_selected_default
	static lv_style_t style_screen_min_dropdown_extra_list_selected_default;
	lv_style_reset(&style_screen_min_dropdown_extra_list_selected_default);
	lv_style_set_radius(&style_screen_min_dropdown_extra_list_selected_default, 3);
	lv_style_set_bg_color(&style_screen_min_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_min_dropdown_extra_list_selected_default, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen_min_dropdown_extra_list_selected_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_min_dropdown_extra_list_selected_default, 255);
	lv_style_set_border_color(&style_screen_min_dropdown_extra_list_selected_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_min_dropdown_extra_list_selected_default, 1);
	lv_style_set_text_color(&style_screen_min_dropdown_extra_list_selected_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_min_dropdown_extra_list_selected_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_min_dropdown_extra_list_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_min_dropdown_extra_list_main_default
	static lv_style_t style_screen_min_dropdown_extra_list_main_default;
	lv_style_reset(&style_screen_min_dropdown_extra_list_main_default);
	lv_style_set_radius(&style_screen_min_dropdown_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_screen_min_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_min_dropdown_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_min_dropdown_extra_list_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_min_dropdown_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_min_dropdown_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_min_dropdown_extra_list_main_default, 1);
	lv_style_set_text_color(&style_screen_min_dropdown_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_min_dropdown_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_screen_min_dropdown_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_min_dropdown_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_min_dropdown_extra_list_scrollbar_default
	static lv_style_t style_screen_min_dropdown_extra_list_scrollbar_default;
	lv_style_reset(&style_screen_min_dropdown_extra_list_scrollbar_default);
	lv_style_set_radius(&style_screen_min_dropdown_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_screen_min_dropdown_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_min_dropdown_extra_list_scrollbar_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_min_dropdown_extra_list_scrollbar_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_min_dropdown_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(obj), &style_screen_min_dropdown_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
}

void setup_scr_functionClock(lv_ui_functionClock *ui){


	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_date_label
	ui->screen_date_label = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_date_label, 10, 10);
	lv_obj_set_size(ui->screen_date_label, 80, 20);
	lv_label_set_text(ui->screen_date_label, "DATE:");
	lv_label_set_long_mode(ui->screen_date_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_date_label, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_label_main_main_default
	static lv_style_t style_screen_date_label_main_main_default;
	lv_style_reset(&style_screen_date_label_main_main_default);
	lv_style_set_radius(&style_screen_date_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_date_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_date_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_date_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_date_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_date_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_screen_date_label_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_date_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_date_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_date_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_date_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_date_label, &style_screen_date_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_date_year_dropdown
	ui->screen_date_year_dropdown = lv_dropdown_create(ui->screen);
	lv_obj_set_pos(ui->screen_date_year_dropdown, 10, 40);
	lv_obj_set_width(ui->screen_date_year_dropdown, 80);
	lv_dropdown_set_options(ui->screen_date_year_dropdown, "2022\n2023\n2024\n2025");
	lv_obj_add_event_cb(ui->screen_date_year_dropdown, _screen_date_year_dropdown_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_year_dropdown_main_main_default
	static lv_style_t style_screen_date_year_dropdown_main_main_default;
	lv_style_reset(&style_screen_date_year_dropdown_main_main_default);
	lv_style_set_radius(&style_screen_date_year_dropdown_main_main_default, 3);
	lv_style_set_bg_color(&style_screen_date_year_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_year_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_year_dropdown_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_year_dropdown_main_main_default, 255);
	lv_style_set_border_color(&style_screen_date_year_dropdown_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_year_dropdown_main_main_default, 1);
	lv_style_set_text_color(&style_screen_date_year_dropdown_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_date_year_dropdown_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_line_space(&style_screen_date_year_dropdown_main_main_default, 20);
	lv_obj_add_style(ui->screen_date_year_dropdown, &style_screen_date_year_dropdown_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_date_month_dropdown
	ui->screen_date_month_dropdown = lv_dropdown_create(ui->screen);
	lv_obj_set_pos(ui->screen_date_month_dropdown, 100, 40);
	lv_obj_set_width(ui->screen_date_month_dropdown, 60);
	lv_dropdown_set_options(ui->screen_date_month_dropdown, "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12");
	lv_obj_add_event_cb(ui->screen_date_month_dropdown, _screen_date_month_dropdown_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_month_dropdown_main_main_default
	static lv_style_t style_screen_date_month_dropdown_main_main_default;
	lv_style_reset(&style_screen_date_month_dropdown_main_main_default);
	lv_style_set_radius(&style_screen_date_month_dropdown_main_main_default, 3);
	lv_style_set_bg_color(&style_screen_date_month_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_month_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_month_dropdown_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_month_dropdown_main_main_default, 255);
	lv_style_set_border_color(&style_screen_date_month_dropdown_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_month_dropdown_main_main_default, 1);
	lv_style_set_text_color(&style_screen_date_month_dropdown_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_date_month_dropdown_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_line_space(&style_screen_date_month_dropdown_main_main_default, 20);
	lv_obj_add_style(ui->screen_date_month_dropdown, &style_screen_date_month_dropdown_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_date_day_dropdown
	ui->screen_date_day_dropdown = lv_dropdown_create(ui->screen);
	lv_obj_set_pos(ui->screen_date_day_dropdown, 170, 40);
	lv_obj_set_width(ui->screen_date_day_dropdown, 60);
	lv_dropdown_set_options(ui->screen_date_day_dropdown, "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31");
	lv_obj_add_event_cb(ui->screen_date_day_dropdown, _screen_date_day_dropdown_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_day_dropdown_main_main_default
	static lv_style_t style_screen_date_day_dropdown_main_main_default;
	lv_style_reset(&style_screen_date_day_dropdown_main_main_default);
	lv_style_set_radius(&style_screen_date_day_dropdown_main_main_default, 3);
	lv_style_set_bg_color(&style_screen_date_day_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_day_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_day_dropdown_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_day_dropdown_main_main_default, 255);
	lv_style_set_border_color(&style_screen_date_day_dropdown_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_date_day_dropdown_main_main_default, 1);
	lv_style_set_text_color(&style_screen_date_day_dropdown_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_date_day_dropdown_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_line_space(&style_screen_date_day_dropdown_main_main_default, 20);
	lv_obj_add_style(ui->screen_date_day_dropdown, &style_screen_date_day_dropdown_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label
	ui->screen_time_label = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_time_label, 10, 85);
	lv_obj_set_size(ui->screen_time_label, 220, 20);
	lv_label_set_text(ui->screen_time_label, "SPECIFIC-TIME:");
	lv_label_set_long_mode(ui->screen_time_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_time_label, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_time_label_main_main_default
	static lv_style_t style_screen_time_label_main_main_default;
	lv_style_reset(&style_screen_time_label_main_main_default);
	lv_style_set_radius(&style_screen_time_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_time_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_time_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_time_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_time_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_time_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_time_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_screen_time_label_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_time_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_time_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_time_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_time_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_time_label, &style_screen_time_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_am_pm_dropdown
	ui->screen_am_pm_dropdown = lv_dropdown_create(ui->screen);
	lv_obj_set_pos(ui->screen_am_pm_dropdown, 10, 115);
	lv_obj_set_width(ui->screen_am_pm_dropdown, 70);
	lv_dropdown_set_options(ui->screen_am_pm_dropdown, "AM\nPM");
	lv_obj_add_event_cb(ui->screen_am_pm_dropdown, _screen_am_pm_dropdown_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_am_pm_dropdown_main_main_default
	static lv_style_t style_screen_am_pm_dropdown_main_main_default;
	lv_style_reset(&style_screen_am_pm_dropdown_main_main_default);
	lv_style_set_radius(&style_screen_am_pm_dropdown_main_main_default, 3);
	lv_style_set_bg_color(&style_screen_am_pm_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_am_pm_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_am_pm_dropdown_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_am_pm_dropdown_main_main_default, 255);
	lv_style_set_border_color(&style_screen_am_pm_dropdown_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_am_pm_dropdown_main_main_default, 1);
	lv_style_set_text_color(&style_screen_am_pm_dropdown_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_am_pm_dropdown_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_line_space(&style_screen_am_pm_dropdown_main_main_default, 20);
	lv_obj_add_style(ui->screen_am_pm_dropdown, &style_screen_am_pm_dropdown_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_hour_dropdown
	ui->screen_hour_dropdown = lv_dropdown_create(ui->screen);
	lv_obj_set_pos(ui->screen_hour_dropdown, 90, 115);
	lv_obj_set_width(ui->screen_hour_dropdown, 60);
	lv_dropdown_set_options(ui->screen_hour_dropdown, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11");
	lv_obj_add_event_cb(ui->screen_hour_dropdown, _screen_hour_dropdown_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_hour_dropdown_main_main_default
	static lv_style_t style_screen_hour_dropdown_main_main_default;
	lv_style_reset(&style_screen_hour_dropdown_main_main_default);
	lv_style_set_radius(&style_screen_hour_dropdown_main_main_default, 3);
	lv_style_set_bg_color(&style_screen_hour_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_hour_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_hour_dropdown_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_hour_dropdown_main_main_default, 255);
	lv_style_set_border_color(&style_screen_hour_dropdown_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_hour_dropdown_main_main_default, 1);
	lv_style_set_text_color(&style_screen_hour_dropdown_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_hour_dropdown_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_line_space(&style_screen_hour_dropdown_main_main_default, 20);
	lv_obj_add_style(ui->screen_hour_dropdown, &style_screen_hour_dropdown_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_min_dropdown
	ui->screen_min_dropdown = lv_dropdown_create(ui->screen);
	lv_obj_set_pos(ui->screen_min_dropdown, 160, 115);
	lv_obj_set_width(ui->screen_min_dropdown, 60);
	lv_dropdown_set_options(ui->screen_min_dropdown, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59");
	lv_obj_add_event_cb(ui->screen_min_dropdown, _screen_min_dropdown_event_cb, LV_EVENT_READY, NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_min_dropdown_main_main_default
	static lv_style_t style_screen_min_dropdown_main_main_default;
	lv_style_reset(&style_screen_min_dropdown_main_main_default);
	lv_style_set_radius(&style_screen_min_dropdown_main_main_default, 3);
	lv_style_set_bg_color(&style_screen_min_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_min_dropdown_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_min_dropdown_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_min_dropdown_main_main_default, 255);
	lv_style_set_border_color(&style_screen_min_dropdown_main_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_min_dropdown_main_main_default, 1);
	lv_style_set_text_color(&style_screen_min_dropdown_main_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_min_dropdown_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_line_space(&style_screen_min_dropdown_main_main_default, 20);
	lv_obj_add_style(ui->screen_min_dropdown, &style_screen_min_dropdown_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_switch_on_off
	ui->screen_switch_on_off = lv_switch_create(ui->screen);
	lv_obj_set_pos(ui->screen_switch_on_off, 10, 185);
	lv_obj_set_size(ui->screen_switch_on_off, 60, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_switch_on_off_main_main_default
	static lv_style_t style_screen_switch_on_off_main_main_default;
	lv_style_reset(&style_screen_switch_on_off_main_main_default);
	lv_style_set_radius(&style_screen_switch_on_off_main_main_default, 100);
	lv_style_set_bg_color(&style_screen_switch_on_off_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_switch_on_off_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_switch_on_off_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_switch_on_off_main_main_default, 124);
	lv_obj_add_style(ui->screen_switch_on_off, &style_screen_switch_on_off_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for style_screen_switch_on_off_main_indicator_checked
	static lv_style_t style_screen_switch_on_off_main_indicator_checked;
	lv_style_reset(&style_screen_switch_on_off_main_indicator_checked);
	lv_style_set_radius(&style_screen_switch_on_off_main_indicator_checked, 100);
	lv_style_set_bg_color(&style_screen_switch_on_off_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_switch_on_off_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_switch_on_off_main_indicator_checked, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_switch_on_off_main_indicator_checked, 255);
	lv_obj_add_style(ui->screen_switch_on_off, &style_screen_switch_on_off_main_indicator_checked, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for style_screen_switch_on_off_main_knob_default
	static lv_style_t style_screen_switch_on_off_main_knob_default;
	lv_style_reset(&style_screen_switch_on_off_main_knob_default);
	lv_style_set_radius(&style_screen_switch_on_off_main_knob_default, 100);
	lv_style_set_bg_color(&style_screen_switch_on_off_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_switch_on_off_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_switch_on_off_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_switch_on_off_main_knob_default, 255);
	lv_obj_add_style(ui->screen_switch_on_off, &style_screen_switch_on_off_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_switch_label
	ui->screen_switch_label = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_switch_label, 10, 160);
	lv_obj_set_size(ui->screen_switch_label, 120, 20);
	lv_label_set_text(ui->screen_switch_label, "OFF/ON:");
	lv_label_set_long_mode(ui->screen_switch_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_switch_label, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_switch_label_main_main_default
	static lv_style_t style_screen_switch_label_main_main_default;
	lv_style_reset(&style_screen_switch_label_main_main_default);
	lv_style_set_radius(&style_screen_switch_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_switch_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_switch_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_switch_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_switch_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_switch_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_switch_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_screen_switch_label_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_switch_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_switch_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_switch_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_switch_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_switch_label, &style_screen_switch_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	
	lv_dropdown_set_selected(ui->screen_date_year_dropdown,clockFunctionYear-2022);
	lv_dropdown_set_selected(ui->screen_date_month_dropdown,clockFunctionMonth - 1);
	lv_dropdown_set_selected(ui->screen_date_day_dropdown,clockFunctionDay - 1);
	if(clockFunctionIsAm == CLOCK_AM)
		lv_dropdown_set_selected(ui->screen_am_pm_dropdown,0);
	else
		lv_dropdown_set_selected(ui->screen_am_pm_dropdown,1);
	lv_dropdown_set_selected(ui->screen_hour_dropdown,clockFunctionHour);
	lv_dropdown_set_selected(ui->screen_min_dropdown,clockFunctionMin);
	if(clockFunctionOffOn == SWITCH_ON)
		lv_obj_add_state(ui->screen_switch_on_off, LV_STATE_CHECKED);
	else
		lv_obj_clear_state(ui->screen_switch_on_off, LV_STATE_CHECKED);

	
//	static u8 flag = 1;	//样式只设置一次，否则容易出现bug。原因未知
//	if(flag)
//	{
		lv_obj_set_style_outline_color(ui->screen_date_year_dropdown,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(ui->screen_date_year_dropdown,255,LV_STATE_FOCUS_KEY);

		lv_obj_set_style_outline_color(ui->screen_date_month_dropdown,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(ui->screen_date_month_dropdown,255,LV_STATE_FOCUS_KEY);
		
		lv_obj_set_style_outline_color(ui->screen_date_day_dropdown,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(ui->screen_date_day_dropdown,255,LV_STATE_FOCUS_KEY);
		
		lv_obj_set_style_outline_color(ui->screen_am_pm_dropdown,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(ui->screen_am_pm_dropdown,255,LV_STATE_FOCUS_KEY);
		
		lv_obj_set_style_outline_color(ui->screen_hour_dropdown,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(ui->screen_hour_dropdown,255,LV_STATE_FOCUS_KEY);
		
		lv_obj_set_style_outline_color(ui->screen_min_dropdown,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(ui->screen_min_dropdown,255,LV_STATE_FOCUS_KEY);
		
		lv_obj_set_style_outline_color(ui->screen_switch_on_off,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(ui->screen_switch_on_off,255,LV_STATE_FOCUS_KEY);
		
//		flag = 0;
//	}
	
}
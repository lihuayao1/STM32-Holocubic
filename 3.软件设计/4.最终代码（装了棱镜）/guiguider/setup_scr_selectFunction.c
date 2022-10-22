/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

extern lv_indev_t * indev_encoder;

void setup_scr_selectFunction(lv_ui_selectFunction *ui){

	//Write codes selectFunction
	ui->selectFunction = lv_obj_create(NULL);
	
	//Write style state: LV_STATE_DEFAULT for style_selectfunction_main_main_default
	static lv_style_t style_selectfunction_main_main_default;
	lv_style_reset(&style_selectfunction_main_main_default);
	lv_style_set_bg_color(&style_selectfunction_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_selectfunction_main_main_default, 255);
	lv_obj_add_style(ui->selectFunction, &style_selectfunction_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes selectFunction_clock_pattern
	ui->selectFunction_clock_pattern = lv_img_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_clock_pattern, 80, 70);
	lv_obj_set_size(ui->selectFunction_clock_pattern, 80, 78);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_clock_pattern_main_main_default
	static lv_style_t style_selectfunction_clock_pattern_main_main_default;
	lv_style_reset(&style_selectfunction_clock_pattern_main_main_default);
	lv_style_set_img_recolor(&style_selectfunction_clock_pattern_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_selectfunction_clock_pattern_main_main_default, 0);
	lv_style_set_img_opa(&style_selectfunction_clock_pattern_main_main_default, 255);
	lv_obj_add_style(ui->selectFunction_clock_pattern, &style_selectfunction_clock_pattern_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->selectFunction_clock_pattern, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->selectFunction_clock_pattern,&clockFuntionPattern);
	lv_img_set_pivot(ui->selectFunction_clock_pattern, 0,0);
	lv_img_set_angle(ui->selectFunction_clock_pattern, 0);

	//Write codes selectFunction_picture_pattern
	ui->selectFunction_picture_pattern = lv_img_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_picture_pattern, 320, 70);
	lv_obj_set_size(ui->selectFunction_picture_pattern, 80, 70);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_picture_pattern_main_main_default
	static lv_style_t style_selectfunction_picture_pattern_main_main_default;
	lv_style_reset(&style_selectfunction_picture_pattern_main_main_default);
	lv_style_set_img_recolor(&style_selectfunction_picture_pattern_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_selectfunction_picture_pattern_main_main_default, 0);
	lv_style_set_img_opa(&style_selectfunction_picture_pattern_main_main_default, 255);
	lv_obj_add_style(ui->selectFunction_picture_pattern, &style_selectfunction_picture_pattern_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->selectFunction_picture_pattern, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->selectFunction_picture_pattern,&pictureFuntionPattern);
	lv_img_set_pivot(ui->selectFunction_picture_pattern, 0,0);
	lv_img_set_angle(ui->selectFunction_picture_pattern, 0);

	//Write codes selectFunction_projection_pattern
	ui->selectFunction_projection_pattern = lv_img_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_projection_pattern, 572, 70);
	lv_obj_set_size(ui->selectFunction_projection_pattern, 56, 76);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_projection_pattern_main_main_default
	static lv_style_t style_selectfunction_projection_pattern_main_main_default;
	lv_style_reset(&style_selectfunction_projection_pattern_main_main_default);
	lv_style_set_img_recolor(&style_selectfunction_projection_pattern_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_selectfunction_projection_pattern_main_main_default, 0);
	lv_style_set_img_opa(&style_selectfunction_projection_pattern_main_main_default, 255);
	lv_obj_add_style(ui->selectFunction_projection_pattern, &style_selectfunction_projection_pattern_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->selectFunction_projection_pattern, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->selectFunction_projection_pattern,&projectionFuntionPattern);
	lv_img_set_pivot(ui->selectFunction_projection_pattern, 0,0);
	lv_img_set_angle(ui->selectFunction_projection_pattern, 0);

	//Write codes selectFunction_set_pattern
	ui->selectFunction_set_pattern = lv_img_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_set_pattern, 807, 90);
	lv_obj_set_size(ui->selectFunction_set_pattern, 65, 51);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_set_pattern_main_main_default
	static lv_style_t style_selectfunction_set_pattern_main_main_default;
	lv_style_reset(&style_selectfunction_set_pattern_main_main_default);
	lv_style_set_img_recolor(&style_selectfunction_set_pattern_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_selectfunction_set_pattern_main_main_default, 0);
	lv_style_set_img_opa(&style_selectfunction_set_pattern_main_main_default, 255);
	lv_obj_add_style(ui->selectFunction_set_pattern, &style_selectfunction_set_pattern_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->selectFunction_set_pattern, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->selectFunction_set_pattern,&setFuntionPattern);
	lv_img_set_pivot(ui->selectFunction_set_pattern, 0,0);
	lv_img_set_angle(ui->selectFunction_set_pattern, 0);

	//Write codes selectFunction_clock_label
	ui->selectFunction_clock_label = lv_label_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_clock_label, 70, 190);
	lv_obj_set_size(ui->selectFunction_clock_label, 100, 32);
	lv_label_set_text(ui->selectFunction_clock_label, "clock");
	lv_label_set_long_mode(ui->selectFunction_clock_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->selectFunction_clock_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_clock_label_main_main_default
	static lv_style_t style_selectfunction_clock_label_main_main_default;
	lv_style_reset(&style_selectfunction_clock_label_main_main_default);
	lv_style_set_radius(&style_selectfunction_clock_label_main_main_default, 0);
	lv_style_set_bg_color(&style_selectfunction_clock_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_selectfunction_clock_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_selectfunction_clock_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_selectfunction_clock_label_main_main_default, 0);
	lv_style_set_text_color(&style_selectfunction_clock_label_main_main_default, lv_color_make(0x00, 0xd9, 0xff));
	lv_style_set_text_font(&style_selectfunction_clock_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_selectfunction_clock_label_main_main_default, 2);
	lv_style_set_pad_left(&style_selectfunction_clock_label_main_main_default, 0);
	lv_style_set_pad_right(&style_selectfunction_clock_label_main_main_default, 0);
	lv_style_set_pad_top(&style_selectfunction_clock_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_selectfunction_clock_label_main_main_default, 0);
	lv_obj_add_style(ui->selectFunction_clock_label, &style_selectfunction_clock_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes selectFunction_picture_label
	ui->selectFunction_picture_label = lv_label_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_picture_label, 310, 190);
	lv_obj_set_size(ui->selectFunction_picture_label, 100, 32);
	lv_label_set_text(ui->selectFunction_picture_label, "picture");
	lv_label_set_long_mode(ui->selectFunction_picture_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->selectFunction_picture_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_picture_label_main_main_default
	static lv_style_t style_selectfunction_picture_label_main_main_default;
	lv_style_reset(&style_selectfunction_picture_label_main_main_default);
	lv_style_set_radius(&style_selectfunction_picture_label_main_main_default, 0);
	lv_style_set_bg_color(&style_selectfunction_picture_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_selectfunction_picture_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_selectfunction_picture_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_selectfunction_picture_label_main_main_default, 0);
	lv_style_set_text_color(&style_selectfunction_picture_label_main_main_default, lv_color_make(0x00, 0xd9, 0xff));
	lv_style_set_text_font(&style_selectfunction_picture_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_selectfunction_picture_label_main_main_default, 2);
	lv_style_set_pad_left(&style_selectfunction_picture_label_main_main_default, 0);
	lv_style_set_pad_right(&style_selectfunction_picture_label_main_main_default, 0);
	lv_style_set_pad_top(&style_selectfunction_picture_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_selectfunction_picture_label_main_main_default, 0);
	lv_obj_add_style(ui->selectFunction_picture_label, &style_selectfunction_picture_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes selectFunction_projection_label
	ui->selectFunction_projection_label = lv_label_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_projection_label, 535, 190);
	lv_obj_set_size(ui->selectFunction_projection_label, 130, 32);
	lv_label_set_text(ui->selectFunction_projection_label, "projection");
	lv_label_set_long_mode(ui->selectFunction_projection_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->selectFunction_projection_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_projection_label_main_main_default
	static lv_style_t style_selectfunction_projection_label_main_main_default;
	lv_style_reset(&style_selectfunction_projection_label_main_main_default);
	lv_style_set_radius(&style_selectfunction_projection_label_main_main_default, 0);
	lv_style_set_bg_color(&style_selectfunction_projection_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_selectfunction_projection_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_selectfunction_projection_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_selectfunction_projection_label_main_main_default, 0);
	lv_style_set_text_color(&style_selectfunction_projection_label_main_main_default, lv_color_make(0x00, 0xd9, 0xff));
	lv_style_set_text_font(&style_selectfunction_projection_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_selectfunction_projection_label_main_main_default, 2);
	lv_style_set_pad_left(&style_selectfunction_projection_label_main_main_default, 0);
	lv_style_set_pad_right(&style_selectfunction_projection_label_main_main_default, 0);
	lv_style_set_pad_top(&style_selectfunction_projection_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_selectfunction_projection_label_main_main_default, 0);
	lv_obj_add_style(ui->selectFunction_projection_label, &style_selectfunction_projection_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes selectFunction_set_label
	ui->selectFunction_set_label = lv_label_create(ui->selectFunction);
	lv_obj_set_pos(ui->selectFunction_set_label, 790, 190);
	lv_obj_set_size(ui->selectFunction_set_label, 100, 32);
	lv_label_set_text(ui->selectFunction_set_label, "set");
	lv_label_set_long_mode(ui->selectFunction_set_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->selectFunction_set_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_selectfunction_set_label_main_main_default
	static lv_style_t style_selectfunction_set_label_main_main_default;
	lv_style_reset(&style_selectfunction_set_label_main_main_default);
	lv_style_set_radius(&style_selectfunction_set_label_main_main_default, 0);
	lv_style_set_bg_color(&style_selectfunction_set_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_selectfunction_set_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_selectfunction_set_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_selectfunction_set_label_main_main_default, 0);
	lv_style_set_text_color(&style_selectfunction_set_label_main_main_default, lv_color_make(0x00, 0xd9, 0xff));
	lv_style_set_text_font(&style_selectfunction_set_label_main_main_default, &lv_font_montserratMedium_20);
	lv_style_set_text_letter_space(&style_selectfunction_set_label_main_main_default, 2);
	lv_style_set_pad_left(&style_selectfunction_set_label_main_main_default, 0);
	lv_style_set_pad_right(&style_selectfunction_set_label_main_main_default, 0);
	lv_style_set_pad_top(&style_selectfunction_set_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_selectfunction_set_label_main_main_default, 0);
	lv_obj_add_style(ui->selectFunction_set_label, &style_selectfunction_set_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_group_t *group = lv_group_create();		//将组件凑成组
	lv_group_set_default(group);
	lv_group_remove_all_objs(group);
	lv_group_add_obj(group,ui->selectFunction_clock_pattern);
	lv_group_add_obj(group,ui->selectFunction_picture_pattern);
	lv_group_add_obj(group,ui->selectFunction_projection_pattern);
	lv_group_add_obj(group,ui->selectFunction_set_pattern);
	lv_indev_set_group(indev_encoder, group);	//设备与组绑定

	lv_obj_set_scroll_snap_x(ui->selectFunction, LV_SCROLL_SNAP_CENTER);	//滚动时，中心自动对齐
	lv_obj_update_snap(ui->selectFunction, LV_ANIM_ON);

}
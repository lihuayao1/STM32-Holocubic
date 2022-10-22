/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "gui_guider.h"


void setup_ui_deskop(lv_ui_deskop *ui){
	setup_scr_deskop(ui);
	lv_scr_load_anim(ui->screen,LV_SCR_LOAD_ANIM_FADE_ON,500,0,true);
}


extern u8 functionNum;
void setup_ui_selectFunction(lv_ui_selectFunction *ui){
	setup_scr_selectFunction(ui);
	if(functionNum == 1)
		lv_obj_scroll_to_view(ui->selectFunction_clock_pattern,LV_ANIM_OFF);
	else if(functionNum == 2)
		lv_obj_scroll_to_view(ui->selectFunction_picture_pattern,LV_ANIM_OFF);
	else if(functionNum == 3)
		lv_obj_scroll_to_view(ui->selectFunction_projection_pattern,LV_ANIM_OFF);
	else if(functionNum == 4)
		lv_obj_scroll_to_view(ui->selectFunction_set_pattern,LV_ANIM_OFF);
	lv_scr_load_anim(ui->selectFunction,LV_SCR_LOAD_ANIM_FADE_ON,500,0,true);
}

void setup_ui_init(lv_ui_init *ui){
	setup_scr_init(ui);
	lv_scr_load(ui->screen);	//初始化界面不需要删除旧界面
}

void setup_ui_functionClock(lv_ui_functionClock *ui){
	setup_scr_functionClock(ui);
	lv_scr_load_anim(ui->screen,LV_SCR_LOAD_ANIM_FADE_ON,500,0,true);
}

void setup_ui_functionSet(lv_ui_functionSet *ui){
	setup_scr_functionSet(ui);
	lv_scr_load_anim(ui->screen,LV_SCR_LOAD_ANIM_FADE_ON,500,0,true);
}

void setup_ui_functionSetLoading(lv_ui_functionSetLoading *ui){
	setup_scr_functionSetLoading(ui);
	lv_scr_load_anim(ui->screen,LV_SCR_LOAD_ANIM_FADE_ON,500,0,true);
}




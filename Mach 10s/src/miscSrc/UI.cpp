// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: UI.cpp

#include "main.h"
#include "pros/apix.h"
#include "display/lvgl.h"
#include "display/lv_conf.h"

lv_obj_t *myButton;
lv_obj_t *myButtonLabel;
lv_obj_t *myLabel;
lv_obj_t *temperatureLabel;

lv_style_t myButtonStyleREL; //relesed style
lv_style_t myButtonStylePR; //pressed style
lv_style_t style;

lv_obj_t * gauge1;
lv_obj_t * bar1;

void lv_ex_gauge_1(void);
void lv_ex_bar_1(void);

void run_display(void)
{
     lv_ex_gauge_1();
     lv_ex_bar_1();
     lv_style_copy(&myButtonStyleREL, &lv_style_plain);
	myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
	myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
	myButtonStyleREL.body.radius = 0;
	myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

	lv_style_copy(&myButtonStylePR, &lv_style_plain);
	myButtonStylePR.body.main_color = LV_COLOR_MAKE(255, 0, 0);
	myButtonStylePR.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
	myButtonStylePR.body.radius = 0;
	myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);

	myButton = lv_btn_create(lv_scr_act(), NULL); //create button
	lv_obj_set_free_num(myButton, 0); //set button is to 0
	lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action);
	lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL);
	lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR);
	lv_obj_set_size(myButton, 200, 50); //set the button size
	lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); // set the pos

	myButtonLabel = lv_label_create(myButton, NULL); // create label
	lv_label_set_text(myButtonLabel, "Click the Button?"); //sets label text
	myLabel = lv_label_create(lv_scr_act(), NULL); // puts it on the screen
     lv_label_set_recolor(myLabel, true);
     std::string tmp = "#00ff00 Lift\n#ffbf00 Chassis \n#00ffff Intake\n\n#2222ff Battery";
     lv_label_set_text(myLabel, tmp); //sets label text
	lv_obj_align(myLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 20); //set the position to center

     temperatureLabel = lv_label_create(lv_scr_act(), NULL); //create label
     lv_label_set_recolor(temperatureLabel, true);
     lv_label_set_text(temperatureLabel, "#ff00cc Temp °C"); //sets label text
	lv_obj_align(temperatureLabel, NULL, LV_ALIGN_CENTER, 100, 70); //set the pos
}

static lv_res_t btn_click_action(lv_obj_t * btn)
{
     uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

     if(id == 0)
     {
          char buffer[100];
          sprintf(buffer, "OH NOO");
          lv_label_set_text(myLabel, buffer);
     }

     return LV_RES_OK;
}

void lv_ex_gauge_1(void)
{

    static lv_style_t style;
    lv_style_copy(&style, &lv_style_pretty_color);
    style.body.padding.inner = 8 ;
    style.body.border.color = LV_COLOR_WHITE;
    style.line.width = 3;
    style.line.color = LV_COLOR_RED;

    // Describe the color for the needles.
    static lv_color_t needle_colors[] = {LV_COLOR_AQUA, LV_COLOR_ORANGE, LV_COLOR_LIME};

    // Create a gauge.
    gauge1 = lv_gauge_create(lv_scr_act(), NULL);
    lv_gauge_set_style(gauge1, &style);

    lv_gauge_set_needle_count(gauge1, 3, needle_colors);
    lv_obj_set_size(gauge1, 200, 200);
    lv_gauge_set_range(gauge1, 20, 70);
    lv_gauge_set_critical_value(gauge1, 55);
    lv_gauge_set_scale(gauge1, 270 , 26, 6);
    lv_obj_align(gauge1, NULL, LV_ALIGN_CENTER, 100, 0);

    // Set the values.
    lv_gauge_set_value(gauge1, 0, 10);
    lv_gauge_set_value(gauge1, 1, 20);
    lv_gauge_set_value(gauge1, 2, 30);
}

void lv_ex_bar_1(void)
{
     static lv_style_t style1;
     lv_style_copy(&style1, &lv_style_plain);
     style1.body.main_color = LV_COLOR_WHITE;
     style1.body.grad_color = LV_COLOR_LIME;
     style1.body.radius = 10;
     style1.body.border.color = LV_COLOR_GRAY;
     style1.body.border.width = 2;
     style1.body.border.opa = LV_OPA_50;
     style1.text.color = LV_COLOR_RED;

     bar1 = lv_bar_create(lv_scr_act(), NULL);
     lv_obj_set_size(bar1, 200, 30);
     lv_obj_align(bar1, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);
     //lv_bar_set_anim_time(bar1, 1000);
     lv_bar_set_style(bar1, LV_BAR_STYLE_INDIC, &style1);
     lv_bar_set_value(bar1, 100);
}

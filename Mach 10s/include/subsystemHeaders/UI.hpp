// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

extern lv_obj_t * myButton;
extern lv_obj_t * myButtonLabel;
extern lv_obj_t * myLabel;

extern lv_style_t myButtonStyleREL; //relesed style
extern lv_style_t myButtonStylePR; //pressed style

static lv_res_t btn_click_action(lv_obj_t * btn);

void run_display();

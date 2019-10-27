// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol(void)
{
	lift::was_moving = -1;
	while (1)
	{ 	// Make into threads if the code requires it.
		if (controller_digital(DOWN))
               blue();
		chassis::assign();
		lift::assign();
		intake::assign();
		lv_bar_set_value(bar1, pros::battery::get_capacity());
		pros::delay(20);
	}

}

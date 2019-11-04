// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize(void)
{    // Initializes motors and sensors.
     run_display();
     chassis::initialize();
	back_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	front_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	back_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	front_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lift_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lift_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intake_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
     make_first_path();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled(void) {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize(void) {}
